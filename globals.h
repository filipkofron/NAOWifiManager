#pragma once

#include "wifimanager.h"
#include "menucontrol.h"
#include "config.h"
#include "menu.h"
#define BOOST_SIGNALS_NO_DEPRECATION_WARNING
#include <alproxies/alconnectionmanagerproxy.h>
#include <alproxies/altexttospeechproxy.h>

#ifdef MYMODULE_IS_REMOTE
  // #define NAO_IP "127.0.0.1"
  // #define NAO_IP "10.10.48.252"
  #define NAO_IP "192.168.0.100"
  #define NAO_PORT 9559
#else // MYMODULE_IS_REMOTE
  #define NAO_IP "127.0.0.1"
  #define NAO_PORT 9559
#endif // MYMODULE_IS_REMOTE

extern std::shared_ptr<ParamEntry> _glob_config;
extern Menu _glob_menu;
extern WifiManager _glob_WifiManager;
extern MenuController _glob_GMenuController;
extern std::shared_ptr<AL::ALConnectionManagerProxy> _glob_connectionManagerProxy;
extern std::shared_ptr<AL::ALTextToSpeechProxy> _glob_textToSpeechProxy;

inline ParamEntry& GetConfig() { return *_glob_config; }
inline Menu& GetMenu() { _glob_menu; }
inline WifiManager& GetWifiManager() { return _glob_WifiManager; }
inline MenuController& GetMenuController() { return _glob_GMenuController; }
inline AL::ALConnectionManagerProxy& GetConnectionProxy() { return *_glob_connectionManagerProxy; }
inline AL::ALTextToSpeechProxy& GetTextToSpeechProxy() { return *_glob_textToSpeechProxy; }
