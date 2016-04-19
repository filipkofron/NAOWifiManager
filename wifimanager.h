#pragma once

#include <vector>
#include "wifiservice.h"
#include "eventhandler.h"

class WifiManager : public INetworkEventHandler
{
private:
  std::vector<WifiService> _services;
  std::string _selectedSSID;

public:
  WifiManager();
  virtual void OnNetworkStatusChanged();
  virtual void OnNetworkServiceInputRequired();

  const std::vector<WifiService>& Services() { return _services; }

  virtual void TestListWifi();
};
