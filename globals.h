#pragma once

#include "wifimanager.h"
#include "menucontrol.h"

extern std::shared_ptr<ParamEntry> _glob_config;
extern WifiManager _glob_WifiManager;
extern MenuController _glob_GMenuController;
extern std::shared_ptr<AL::ALConnectionManagerProxy> _glob_connectionManagerProxy;

extern ParamEntry& GetConfig() { return *_glob_config; }
WifiManager& GetWifiManager() { return _glob_WifiManager; }
MenuController& GetMenuController() { return _glob_GMenuController; }
AL::ALConnectionManagerProxy& GetConnectionProxy() { return *_glob_connectionManagerProxy; }
