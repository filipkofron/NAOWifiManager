#include "wifi.h"
#include "config.h"
#include "globals.h"

#include <iostream>
#include <alcommon/albroker.h>

namespace AL
{
  void Say(const std::string& message)
  {
#if LOCAL_TEST || 1
    std::cout << "Would say: " << message << std::endl;
#else // LOCAL_TEST
    std::cout << "Would say: " << message << std::endl;
    GetTextToSpeechProxy().setLanguage("Czech");
    GetTextToSpeechProxy().say(message);
#endif // LOCAL_TEST


    // std::cout << GetTextToSpeechProxy().getAvailableLanguages() << std::endl;
  }

  void SayEverytime(const std::string& message)
  {
    std::cout << "Would say: " << message << std::endl;
    GetTextToSpeechProxy().setLanguage("Czech");
    GetTextToSpeechProxy().say(message);
  }
}

template <typename Proxy>
boost::shared_ptr<Proxy> InitProxy()
{
  return boost::shared_ptr<Proxy>(new Proxy(NAO_IP, NAO_PORT));
}

WifiModule::WifiModule(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name),
    _memoryProxy(NAO_IP, NAO_PORT),
    _ending(false),
    _updateThread(&WifiModule::UpdateThread, this)
{
#if !WIFI_LOCAL_TEST
  _globs->_glob_connectionManagerProxy = InitProxy<AL::ALConnectionManagerProxy>();
#endif // !LOCAL_TEST
  _globs->_glob_textToSpeechProxy = InitProxy<AL::ALTextToSpeechProxy>();
  // Describe the module here. This will appear on the webpage
  setModuleDescription("My own custom module.");
  _scrollPosUp = -1;
  _scrollPosDown = -1;

  functionName("OnFrontTactilTouched", getName(), "React to OnFrontTactilTouched.");
  BIND_METHOD(WifiModule::OnFrontTactilTouched);
  functionName("OnMiddleTactilTouched", getName(), "React to OnMiddleTactilTouched.");
  BIND_METHOD(WifiModule::OnMiddleTactilTouched);
  functionName("OnRearTactilTouched", getName(), "React to OnRearTactilTouched.");
  BIND_METHOD(WifiModule::OnRearTactilTouched);
  functionName("OnChestSimpleClick", getName(), "React to OnChestSimpleClick.");
  BIND_METHOD(WifiModule::OnChestSimpleClick);
  functionName("OnChestTripleClick", getName(), "React to OnChestTripleClick.");
  BIND_METHOD(WifiModule::OnChestTripleClick);
  functionName("OnNetworkServiceInputRequired", getName(), "React to OnNetworkServiceInputRequired.");
  BIND_METHOD(WifiModule::OnNetworkServiceInputRequired);
  functionName("OnNetworkConnectStatus", getName(), "React to OnNetworkConnectStatus.");
  BIND_METHOD(WifiModule::OnNetworkConnectStatus);
  functionName("OnNetworkStatusChanged", getName(), "React to OnNetworkStatusChanged.");
  BIND_METHOD(WifiModule::OnNetworkStatusChanged);
}

WifiModule::~WifiModule()
{
  _ending = true;
  _updateThread.join();
}

void WifiModule::init()
{
  _inputSubscribers.push_back(&GetMenuController());
  _networkSubscribers.push_back(&GetWifiManager());

  /**
   * Init is called just after construction.
   * Do something or not
   */
  //std::cout << returnTrue() << std::endl;
  std::cout << "Wifi module initializing.." << std::endl;
  ParamEntry::Reload();
  _memoryProxy.subscribeToEvent("FrontTactilTouched", "WifiModule", "OnFrontTactilTouched");
  _memoryProxy.subscribeToEvent("MiddleTactilTouched", "WifiModule", "OnMiddleTactilTouched");
  _memoryProxy.subscribeToEvent("RearTactilTouched", "WifiModule", "OnRearTactilTouched");
  _memoryProxy.subscribeToEvent("ALChestButton/SimpleClickOccured", "WifiModule", "OnChestSimpleClick");
  _memoryProxy.subscribeToEvent("ALChestButton/TripleClickOccured", "WifiModule", "OnChestTripleClick");
  _memoryProxy.subscribeToEvent("NetworkServiceInputRequired", "WifiModule", "OnNetworkServiceInputRequired");
  _memoryProxy.subscribeToEvent("NetworkConnectStatus", "WifiModule", "OnNetworkConnectStatus");
  _memoryProxy.subscribeToEvent("NetworkServiceStateChanged", "WifiModule", "OnNetworkStatusChanged");

  // THIS MUST BE ENABLED
  AL::ALValue status = "test";
  /*status.arraySetSize(2);
  status[1] = "idle";*/
  OnNetworkStatusChanged(AL::ALValue(), status);

  //TODO: REMOVE

  // OnChestTripleClick();
  // OnChestSimpleClick();
/*
  for (int i = 0; i < GetWifiManager().Services().size(); i++)
  {
    if (GetWifiManager().Services()[i].Name() == "eduroam")
      break;
    OnRearTactilTouched();
    OnMiddleTactilTouched();
    OnFrontTactilTouched();
  }

  OnChestSimpleClick();*/

#if LOCAL_TEST
  OnChestTripleClick();
  OnChestSimpleClick();

  for (int i = 0; i < 2; i++)
  {
    OnRearTactilTouched();
    OnMiddleTactilTouched();
    OnFrontTactilTouched();
  }

  OnChestSimpleClick();

  //OnChestSimpleClick();
#endif // LOCAL_TEST
}

void WifiModule::UpdateSleep()
{
  boost::this_thread::sleep_for(boost::chrono::seconds(15));
}

void WifiModule::UpdateThread()
{
  while (!_ending)
  {
    UpdateSleep();
    OnNetworkStatusChanged(AL::ALValue(), "");
  }
}

void WifiModule::OnFrontTactilTouched()
{
  // std::cout << "You touched meeah on front" << std::endl;

  _scrollPosUp = 0;
  if (_scrollPosDown == 1)
  {
    for (std::vector<IInputEventHandler*>::iterator it = _inputSubscribers.begin(); it != _inputSubscribers.end(); it++)
      (*it)->OnDown();
  }
  _scrollPosDown = -1;
}

void WifiModule::OnMiddleTactilTouched()
{
  // std::cout << "You touched meeah on center" << std::endl;

  if (_scrollPosDown == 0)
    _scrollPosDown = 1;

  if (_scrollPosUp == 0)
    _scrollPosUp = 1;
}

void WifiModule::OnRearTactilTouched()
{
  // std::cout << "You touched meeah on rear" << std::endl;

  _scrollPosDown = 0;
  if (_scrollPosUp == 1)
  {
    for (std::vector<IInputEventHandler*>::iterator it = _inputSubscribers.begin(); it != _inputSubscribers.end(); it++)
      (*it)->OnUp();
  }

  _scrollPosUp = -1;
}

void WifiModule::OnChestSimpleClick()
{
  // std::cout << "You chest simple clicked me" << std::endl;

  for (std::vector<IInputEventHandler*>::iterator it = _inputSubscribers.begin(); it != _inputSubscribers.end(); it++)
    (*it)->OnEnter();
}

void WifiModule::OnChestTripleClick()
{
  // std::cout << "You chest triple clicked me" << std::endl;

  for (std::vector<IInputEventHandler*>::iterator it = _inputSubscribers.begin(); it != _inputSubscribers.end(); it++)
    (*it)->OnStart();
}

void WifiModule::OnNetworkServiceInputRequired(const std::string& eventName, const AL::ALValue& inputRequest)
{
  // std::cout << "OnNetworkServiceInputRequired: " << inputRequest << std::endl;

  for (std::vector<INetworkEventHandler*>::iterator it = _networkSubscribers.begin(); it != _networkSubscribers.end(); it++)
    (*it)->OnNetworkServiceInputRequired();
}

void WifiModule::OnNetworkConnectStatus(const std::string& eventName, const AL::ALValue& status)
{
  // std::cout << "OnNetworkConnectStatus: " << status << std::endl;

  for (std::vector<INetworkEventHandler*>::iterator it = _networkSubscribers.begin(); it != _networkSubscribers.end(); it++)
    (*it)->OnNetworkConnectStatus(status[1].toString());
}

void WifiModule::OnNetworkStatusChanged(const std::string& eventName, const AL::ALValue& status)
{
 // std::cout << "OnNetworkStatusChanged: " << status << std::endl;

  for (std::vector<INetworkEventHandler*>::iterator it = _networkSubscribers.begin(); it != _networkSubscribers.end(); it++)
    (*it)->OnNetworkStatusChanged((std::string) status);
}
