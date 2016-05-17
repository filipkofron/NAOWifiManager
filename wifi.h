#pragma once

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING
#include <alcommon/almodule.h>
#include <alproxies/alconnectionmanagerproxy.h>
#include <alproxies/almemoryproxy.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "wifimanager.h"

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
  void Say(const std::string& message);
  void SayEverytime(const std::string& message);
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable within NAOqi
 */
class WifiModule : public AL::ALModule
{
protected:
  int _scrollPosUp;
  int _scrollPosDown;
  bool _ending;
  boost::thread _updateThread;
  boost::mutex _updateMutex;

  AL::ALMemoryProxy _memoryProxy;
  std::vector<IInputEventHandler*> _inputSubscribers;
  std::vector<INetworkEventHandler*> _networkSubscribers;

  void UpdateSleep();
  void UpdateThread();
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
  virtual void OnNetworkServiceInputRequired(const std::string& eventName, const AL::ALValue& inputRequest);
  virtual void OnNetworkConnectStatus(const std::string& eventName, const AL::ALValue& status);
  virtual void OnNetworkStatusChanged(const std::string& eventName, const AL::ALValue& status);
};
