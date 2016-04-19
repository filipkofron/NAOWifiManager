#include "wifi.h"
#include "config.h"
#include "globals.h"

#include <iostream>
#include <alcommon/albroker.h>

// #define LOCAL_IP "127.0.0.1"
// #define LOCAL_IP "10.10.48.252"
#define LOCAL_IP "192.168.0.100"
#define LOCAL_PORT 9559

WifiModule::WifiModule(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name),
    _connectionManagerProxy(new AL::ALConnectionManagerProxy(LOCAL_IP, LOCAL_PORT)),
    _memoryProxy(LOCAL_IP, LOCAL_PORT)
{
  _glob_connectionManagerProxy = _connectionManagerProxy;
  // Describe the module here. This will appear on the webpage
  setModuleDescription("My own custom module.");

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
}

void WifiModule::OnFrontTactilTouched()
{
  std::cout << "You touched meeah on front" << std::endl;
}

void WifiModule::OnMiddleTactilTouched()
{
  std::cout << "You touched meeah on center" << std::endl;
}

void WifiModule::OnRearTactilTouched()
{
  std::cout << "You touched meeah on rear" << std::endl;
}

void WifiModule::OnChestSimpleClick()
{
  std::cout << "You chest simple clicked me" << std::endl;
}

void WifiModule::OnChestTripleClick()
{
  std::cout << "You chest triple clicked me" << std::endl;
}

void WifiModule::OnNetworkServiceInputRequired(const AL::ALValue& inputRequest)
{
  std::cout << "OnNetworkServiceInputRequired: " << inputRequest << std::endl;
  AL::ALValue input;
  input.arraySetSize(2);

  AL::ALValue user;
  user.arraySetSize(2);
  user[0] = "Username";
  user[1] = "kofrofil@fit.cvut.cz";

  AL::ALValue pass;
  pass.arraySetSize(2);
  pass[0] = "Password";
  pass[1] = "BysChtelVedet";

  input[0] = user;
  input[1] = pass;
  GetConnectionProxy().setServiceInput(input);
}

void WifiModule::OnNetworkConnectStatus(const AL::ALValue& status)
{
  std::cout << "OnNetworkConnectStatus: " << status << std::endl;
}
