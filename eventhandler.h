#pragma once

class IInputEventHandler
{
public:
  virtual void OnUp() = 0;
  virtual void OnDown() = 0;
  virtual void OnEnter() = 0;
};

class INetworkEventHandler
{
public:
  virtual void OnNetworkStatusChanged() = 0;
};
