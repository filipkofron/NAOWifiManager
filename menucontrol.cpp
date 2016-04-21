#include "menucontrol.h"
#include "globals.h"
#include "wifi.h"
#include <iostream>

std::shared_ptr<MenuItem> MakeItem(const std::string& name, IMenuHandler* handler)
{
  std::shared_ptr<MenuItem> menuItem(new MenuItem);
  menuItem->Name() = name;
  menuItem->Handler() = std::shared_ptr<IMenuHandler>(handler);
  return menuItem;
}

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
    AL::Say("Zvolena síť " + _name);
    GetWifiManager().ChooseWifi(_name);
  }
};

class EndChooseWifiMenuHandler : public IMenuHandler
{
public:
  virtual void Handle() override
  {
    GetMenu().ClearItems();

    AL::Say("Ukončuji vybrání wifi");

    GetMenuController().OnStart();
  }
};

class ChooseWifiMenuEnterHandler : public IMenuHandler
{
public:
  virtual void Handle() override
  {
    GetMenu().ClearItems();

    GetWifiManager().UpdateList();

    for (auto& service : GetWifiManager().Services())
      GetMenu().AddItem(MakeItem(service.Name(), new ChooseWifiMenuHandler(service.Name())));

    GetMenu().AddItem(MakeItem("Ukončit vybráni wifi", new EndChooseWifiMenuHandler()));
  }
};

class EndMenuHandler : public IMenuHandler
{
public:
  virtual void Handle() override
  {
    GetMenu().ClearItems();

    AL::Say("Ukončuji nastavení sítě.");
  }
};

void MenuController::OnStart()
{
  GetMenu().ClearItems();

  GetMenu().AddItem(MakeItem("Zvolte síť", new ChooseWifiMenuEnterHandler));
  GetMenu().AddItem(MakeItem("Ukončit nastavení sítě", new EndMenuHandler));
}
