#include "wifi.h"
#include "config.h"
#include "globals.h"

#include <iostream>
#include <alcommon/albroker.h>

namespace AL
{
  void Say(const std::string& message)
  {
    GetTextToSpeechProxy().say("Hello world from c plus plus");
  }
}

template <typename Proxy>
std::shared_ptr<Proxy> InitProxy()
{
  return std::shared_ptr<Proxy>(new Proxy(NAO_IP, NAO_PORT));
}

WifiModule::WifiModule(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name),
    _memoryProxy(NAO_IP, NAO_PORT)
{
  _glob_connectionManagerProxy = InitProxy<AL::ALConnectionManagerProxy>();
  _glob_textToSpeechProxy = InitProxy<AL::ALTextToSpeechProxy>();
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
}

WifiModule::~WifiModule()
{
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

  GetWifiManager().TestListWifi();
}

void WifiModule::OnFrontTactilTouched()
{
  std::cout << "You touched meeah on front" << std::endl;

  _scrollPosUp = 0;
  if (_scrollPosDown == 1)
  {
    for (auto& subscriber : _inputSubscribers)
      subscriber->OnDown();
  }
  _scrollPosDown = -1;
}

void WifiModule::OnMiddleTactilTouched()
{
  std::cout << "You touched meeah on center" << std::endl;

  if (_scrollPosDown == 0)
    _scrollPosDown = 1;

  if (_scrollPosUp == 0)
    _scrollPosUp = 1;
}

void WifiModule::OnRearTactilTouched()
{
  std::cout << "You touched meeah on rear" << std::endl;

  _scrollPosDown = 0;
  if (_scrollPosUp == 1)
  {
    for (auto& subscriber : _inputSubscribers)
      subscriber->OnUp();
  }

  _scrollPosUp = -1;
}

void WifiModule::OnChestSimpleClick()
{
  std::cout << "You chest simple clicked me" << std::endl;

  for (auto& subscriber : _inputSubscribers)
    subscriber->OnEnter();
}

void WifiModule::OnChestTripleClick()
{
  std::cout << "You chest triple clicked me" << std::endl;

  for (auto& subscriber : _inputSubscribers)
    subscriber->OnStart();
}

void WifiModule::OnNetworkServiceInputRequired(const AL::ALValue& inputRequest)
{
  std::cout << "OnNetworkServiceInputRequired: " << inputRequest << std::endl;

  for (auto& subscriber : _networkSubscribers)
    subscriber->OnNetworkServiceInputRequired();
}

void WifiModule::OnNetworkConnectStatus(const AL::ALValue& status)
{
  std::cout << "OnNetworkConnectStatus: " << status << std::endl;

  for (auto& subscriber : _networkSubscribers)
    subscriber->OnNetworkStatusChanged();
}
