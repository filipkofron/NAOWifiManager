#include "menucontrol.h"
#include "globals.h"
#include <iostream>

void MenuController::OnUp()
{
  GetMenu().OnUp();
}

void MenuController::OnDown()
{
  GetMenu().OnDown();
}

void MenuController::OnEnter()
{
  GetMenu().OnEnter();
}

class ChooseWifiMenuHandler : public IMenuHandler
{
private:
  std::string _name;
public:
  ChooseWifiMenuHandler(const std::string& name)
    : _name(name)
  {
  }

  virtual void Handle() override
  {
    AL::Say("Vybiram wifi " + _name);
    GetWifiManager().ChooseWifi(_name);
  }
};


class ChooseWifiMenuEnterHandler : public IMenuHandler
{
public:
  virtual void Handle() override
  {
    GetMenu().ClearItems();

    for (auto& service : GetWifiManager().Services())
      GetMenu().AddItem(MakeItem(service.Name(), new ChooseWifiMenuHandler(service.Name())));
  }
};

std::shared_ptr<MenuItem> MakeItem(const std::string& name, IMenuHandler* handler)
{
  std::shared_ptr<MenuItem> menuItem(new MenuItem);
  menuItem->Name() = name;
  menuItem->Handler() = std::shared_ptr<IMenuHandler>(handler);
  return menuItem;
}

void MenuController::OnStart()
{
  GetMenu().ClearItems();

  GetMenu().AddItem(MakeItem("Vybrat Wifi", new ChooseWifiMenuEnterHandler));
}
