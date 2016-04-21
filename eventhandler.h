#pragma once

#include <string>

class IInputEventHandler
{
public:
  virtual ~IInputEventHandler() { }
  virtual void OnUp() = 0;
  virtual void OnDown() = 0;
  virtual void OnEnter() = 0;
  virtual void OnStart() = 0;
};

class INetworkEventHandler
{
public:
  virtual ~INetworkEventHandler() { }
  virtual void OnNetworkConnectStatus(const std::string& status) = 0;
  virtual void OnNetworkStatusChanged(const std::string& status) = 0;
  virtual void OnNetworkServiceInputRequired() = 0;
};
