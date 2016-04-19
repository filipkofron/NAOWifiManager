#pragma once

#include <alcommon/almodule.h>
#include <alproxies/alconnectionmanagerproxy.h>
#include <alproxies/almemoryproxy.h>
#include "wifimanager.h"

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable within NAOqi
 */
class WifiModule : public AL::ALModule
{
protected:
  std::shared_ptr<AL::ALConnectionManagerProxy> _connectionManagerProxy;
  AL::ALMemoryProxy _memoryProxy;
  std::vector<IInputEventHandler*> _inputSubscribers;
  std::vector<INetworkEventHandler*> _networkSubscribers;
public:
  WifiModule(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

  virtual ~WifiModule();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

  virtual void OnFrontTactilTouched();
  virtual void OnMiddleTactilTouched();
  virtual void OnRearTactilTouched();
  virtual void OnChestSimpleClick();
  virtual void OnChestTripleClick();
  virtual void OnNetworkServiceInputRequired(const AL::ALValue& inputRequest);
  virtual void OnNetworkConnectStatus(const AL::ALValue& status);
};
