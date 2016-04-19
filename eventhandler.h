#pragma once

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
  virtual void OnNetworkStatusChanged() = 0;
  virtual void OnNetworkServiceInputRequired() = 0;
};
