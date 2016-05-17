#pragma once

#include "scriptcommand.h"

class WifiRemoveNetwork : public ScriptCommand
{
private:
  std::string _netId;
public:
  WifiRemoveNetwork(const std::string& netId)
    : _netId(netId)
  {

  }
  virtual std::string GetCommandString();
};

class WifiNetworkAdder : public ScriptCommand
{
protected:
  std::string _netId;
public:
  virtual void OnOutput(const std::string& out);
  std::string GetNetworkId() { return _netId; }
};


class WifiConnectToOpen : public WifiNetworkAdder
{
private:
  std::string _ssid;
public:
  WifiConnectToOpen(const std::string& ssid)
    : _ssid(ssid)
  {

  }
  virtual std::string GetCommandString();
};

class WifiConnectToWPA : public WifiNetworkAdder
{
private:
  std::string _ssid;
  std::string _password;
public:
  WifiConnectToWPA(const std::string& ssid, const std::string password)
    : _ssid(ssid), _password(password)
  {

  }
  virtual std::string GetCommandString();
};


class WifiConnectToEnterprise : public WifiNetworkAdder
{
private:
  std::string _ssid;
  std::string _username;
  std::string _password;
public:
  WifiConnectToEnterprise(const std::string& ssid, const std::string& username, const std::string& password)
    : _ssid(ssid), _username(username), _password(password)
  {

  }
  virtual std::string GetCommandString();
};
