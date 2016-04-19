#pragma once

#include "wifistate.h"

struct WifiService
{
  std::string _name;
  std::string _id;
  WifiState _state;

  std::string& Name() { return _name; }
  std::string& Id() { return _id; }
  WifiState& State() { return _state; }

  const std::string& Name() const { return _name; }
  const std::string& Id() const { return _id; }
  const WifiState& State() const { return _state; }
};
