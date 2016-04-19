#pragma once

#include <vector>
#include <alproxies/alconnectionmanagerproxy.h>
#include "wifiservice.h"
#include "eventhandler.h"

class WifiManager : public INetworkEventHandler
{
private:
  std::vector<WifiService> _services;

public:
  WifiManager();
  virtual void OnNetworkStatusChanged();


  virtual void TestListWifi();
};
