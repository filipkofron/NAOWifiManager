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
  #define NAO_IP "10.10.48.252"
  // #define NAO_IP "192.168.0.100"
  // #define NAO_IP "192.168.0.114"
  // #define NAO_IP "192.168.1.147"
  #define NAO_PORT 9559
#else // MYMODULE_IS_REMOTE
  #define NAO_IP "127.0.0.1"
  #define NAO_PORT 9559
#endif // MYMODULE_IS_REMOTE

#define LOCAL_TEST_ENABLE 0
#if LOCAL_TEST_ENABLE && defined(MYMODULE_IS_REMOTE)
  #define LOCAL_TEST 1
#endif

#if LOCAL_TEST
// #define WIFI_LOCAL_TEST 1
#else
#define WIFI_LOCAL_TEST 0
#endif


struct Globs
{
  boost::shared_ptr<ParamEntry> _glob_config;
  Menu _glob_menu;
  WifiManager _glob_WifiManager;
  MenuController _glob_GMenuController;
  boost::shared_ptr<AL::ALConnectionManagerProxy> _glob_connectionManagerProxy;
  boost::shared_ptr<AL::ALTextToSpeechProxy> _glob_textToSpeechProxy;
};

extern boost::shared_ptr<Globs> _globs;

inline ParamEntry& GetConfig() { return *_globs->_glob_config; }
inline Menu& GetMenu() { return _globs->_glob_menu; }
inline WifiManager& GetWifiManager() { return _globs->_glob_WifiManager; }
inline MenuController& GetMenuController() { return _globs->_glob_GMenuController; }
inline AL::ALConnectionManagerProxy& GetConnectionProxy() { return *_globs->_glob_connectionManagerProxy; }
inline AL::ALTextToSpeechProxy& GetTextToSpeechProxy() { return *_globs->_glob_textToSpeechProxy; }
