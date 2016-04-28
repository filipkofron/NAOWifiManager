#pragma once

#include "scriptcommand.h"

class WifiConnectToOpen : public ScriptCommand
{
private:
  std::string _ssid;
public:
  WifiConnectToOpen(const std::string& ssid)
    : _ssid(ssid)
  {

  }
  virtual std::string GetCommandString() override;
};

class WifiConnectToWPA : public ScriptCommand
{
private:
  std::string _ssid;
  std::string _password;
public:
  WifiConnectToWPA(const std::string& ssid, const std::string password)
    : _ssid(ssid), _password(password)
  {

  }
  virtual std::string GetCommandString() override;
};


class WifiConnectToEnterprise : public ScriptCommand
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
  virtual std::string GetCommandString() override;
};
