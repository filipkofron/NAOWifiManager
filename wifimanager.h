#pragma once

#include <vector>
#include "wifiservice.h"
#include "eventhandler.h"
#include "scriptcommand.h"

class WifiManager : public INetworkEventHandler
{
private:
  bool _wasConnecting;
  bool _disabled;
  std::vector<WifiService> _services;
  std::vector<boost::shared_ptr<ScriptCommand> > _networkCleanups;
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

  const std::string& SelectedSSID() const { return _selectedSSID; }
  const std::vector<WifiService>& Services() { return _services; }

  void AddNetworkCleanup(const boost::shared_ptr<ScriptCommand> &scriptCommand) { _networkCleanups.push_back(scriptCommand); }

  void ChooseWifi(const std::string& name);
  void SetDisabled(bool disabled);
  bool IsDisabled() const { return _disabled; }
};
