#include "menu.h"
#include "wifi.h"

std::unique_ptr<Menu> Menu::_instance;

void MenuItem::Announce()
{
  AL::Say(_name);
}

Menu& Menu::Instance()
{
  if (!_instance)
    _instance = std::unique_ptr<Menu>(new Menu);
  return *_instance;
}

void Menu::ClearItems()
{
  _index = 0;
  _items.clear();
}

void Menu::AddItem(const std::shared_ptr<MenuItem>& item)
{
  _items.push_back(item);
}

void Menu::OnUp()
{
  if (_items.size() == 0)
    return;

  if (_index == 0)
    _index = _items.size() - 1;
  else
    _index--;

  _items[_index]->Announce();
}

void Menu::OnDown()
{
  if (_items.size() == 0)
    return;

  if (_index == _items.size() - 1)
    _index = 0;
  else
    _index++;

  _items[_index]->Announce();
}

void Menu::OnEnter()
{
  if (_items.size() == 0)
    return;

  AL::Say("Zvoleno");
  _items[_index]->Announce();

  if (_items[_index]->Handler())
    _items[_index]->Handler()->Handle();
}
