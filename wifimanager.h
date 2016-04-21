#pragma once

#include <vector>
#include "wifiservice.h"
#include "eventhandler.h"

class WifiManager : public INetworkEventHandler
{
private:
  std::vector<WifiService> _services;
  std::string _selectedSSID;
  void Disconnect();
  void Connect();
  bool IsSelectedNetworkAvailable() const;
  bool IsConnectedToSelected() const;
  bool IsConnectedToAny() const;
  std::string GetConnectedToAnyId() const;
  std::string GetSelectedId() const;

public:
  WifiManager();
  virtual void OnNetworkConnectStatus(const std::string& status);
  virtual void OnNetworkStatusChanged(const std::string& status);
  virtual void OnNetworkServiceInputRequired();
  void UpdateList();

  const std::vector<WifiService>& Services() { return _services; }

  void ChooseWifi(const std::string& name);
};
