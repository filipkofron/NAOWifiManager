#include "menu.h"

std::unique_ptr<Menu> Menu::_instance;

Menu& Menu::Instance()
{
  if (!_instance)
    _instance = std::unique_ptr<Menu>(new Menu);
  return *_instance;
}

void Menu::ClearItems()
{

}

void Menu::AddItem(const std::shared_ptr<MenuItem>& item)
{

}

void Menu::OnUp()
{

}

void Menu::OnDown()
{

}

void Menu::OnEnter()
{

}
