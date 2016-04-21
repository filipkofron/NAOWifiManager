/*
 * Copyright (c) 2012-2015 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */
#include <iostream>
#define BOOST_SIGNALS_NO_DEPRECATION_WARNING
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include "wifi.h"
#include "config.h"
#include "globals.h"

std::unique_ptr<Globs> _globs = std::unique_ptr<Globs>(new Globs);

#ifdef MYMODULE_IS_REMOTE
# define ALCALL
#else
// when not remote, we're in a dll, so export the entry point
# ifdef _WIN32
#  define ALCALL __declspec(dllexport)
# else
#  define ALCALL
# endif
#endif

extern "C"
{
  ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> broker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker);
    // create module instances
    AL::ALModule::createModule<WifiModule>(broker, "WifiModule");
    return 0;
  }

  ALCALL int _closeModule(  )
  {
    return 0;
  }
} // extern "C"


#ifdef MYMODULE_IS_REMOTE
int main()
{
  ParamEntry::Reload();
  std::cout << "Config:" << std::endl;
  GetConfig().PrintOn(std::cout);
  int pport = NAO_PORT;
  std::string pip = NAO_IP;

  // Need this to for SOAP serialization of floats to work
  setlocale(LC_NUMERIC, "C");

  // A broker needs a name, an IP and a port:
  const std::string brokerName = "mybroker";
  // FIXME: would be a good idea to look for a free port first
  int brokerPort = 54000;
  // listen port of the broker (here an anything)
  const std::string brokerIp = "0.0.0.0";


  // Create your own broker
  boost::shared_ptr<AL::ALBroker> broker;
  try
  {
    broker = AL::ALBroker::createBroker(
    brokerName,
    brokerIp,
    brokerPort,
    pip,
    pport,
    0    // you can pass various options for the broker creation,
    // but default is fine
    );
  }
  catch(...)
  {
    std::cerr << "Fail to connect broker to: "
              << pip
              << ":"
              << pport
              << std::endl;

    AL::ALBrokerManager::getInstance()->killAllBroker();
    AL::ALBrokerManager::kill();
    return 1;
  }

  // Deal with ALBrokerManager singleton (add your borker into NAOqi)
  AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
  AL::ALBrokerManager::getInstance()->addBroker(broker);

  // Now it's time to load your module with
  // AL::ALModule::createModule<your_module>(<broker_create>, <your_module>);
  AL::ALModule::createModule<WifiModule>(broker, "WifiModule");

 // while (true)

  for (int i = 0; i < 60; i++)
  {
    std::cout << "will sleep for: " << (20 - i) << " seconds." << std::endl;
    qi::os::sleep(1);
  }
  return 0;
}
#endif
