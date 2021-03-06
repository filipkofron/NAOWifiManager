#include "menucontrol.h"
#include "globals.h"
#include "wifi.h"
#include <iostream>

boost::shared_ptr<MenuItem> MakeItem(const std::string& name, IMenuHandler* handler)
{
  boost::shared_ptr<MenuItem> menuItem(new MenuItem);
  menuItem->Name() = name;
  menuItem->Handler() = boost::shared_ptr<IMenuHandler>(handler);
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

  virtual void Handle()
  {
    AL::Say("Zvolena síť " + _name);
    GetWifiManager().ChooseWifi(_name);
  }
};

class EndChooseWifiMenuHandler : public IMenuHandler
{
public:
  virtual void Handle()
  {
    GetMenu().ClearItems();

    AL::Say("Ukončuji vybrání wifi");

    GetMenuController().OnStart();
  }
};

class ChooseWifiMenuEnterHandler : public IMenuHandler
{
public:
  virtual void Handle()
  {
    GetMenu().ClearItems();

    GetWifiManager().UpdateList();

    for (std::vector<WifiService>::const_iterator it = GetWifiManager().Services().begin(); it != GetWifiManager().Services().end(); it++)
      GetMenu().AddItem(MakeItem(it->Name(), new ChooseWifiMenuHandler(it->Name())));

    GetMenu().AddItem(MakeItem("Ukončit vybráni wifi", new EndChooseWifiMenuHandler()));
  }
};

class DisableWifi : public IMenuHandler
{
public:
  virtual void Handle()
  {
    GetWifiManager().SetDisabled(true);
  }
};

class EnableWifi : public IMenuHandler
{
public:
  virtual void Handle()
  {
    GetWifiManager().SetDisabled(false);
    GetMenuController().OnStart();
  }
};

class EndMenuHandler : public IMenuHandler
{
public:
  virtual void Handle()
  {
    GetMenu().ClearItems();

    AL::Say("Ukončuji nastavení sítě.");
  }
};

void MenuController::OnStart()
{
  GetMenu().ClearItems();

  GetMenu().AddItem(MakeItem("Zvolte síť", new ChooseWifiMenuEnterHandler));
  if (GetWifiManager().IsDisabled())
    GetMenu().AddItem(MakeItem("Zapnout síť", new EnableWifi));
  else
    GetMenu().AddItem(MakeItem("Vypnout síť", new DisableWifi));
  GetMenu().AddItem(MakeItem("Ukončit nastavení sítě", new EndMenuHandler));
}
