#pragma once

#include "wifistate.h"
#include <memory>

struct WifiConfig
{
  bool _default;
  std::string _username;
  std::string _password;
};

struct WifiService
{
  std::string _name;
  std::string _id;
  WifiState _state;
  std::shared_ptr<WifiConfig> _knownConfig;

  void FindConfig();

  std::string& Name() { return _name; }
  std::string& Id() { return _id; }
  WifiState& State() { return _state; }

  const std::string& Name() const { return _name; }
  const std::string& Id() const { return _id; }
  const WifiState& State() const { return _state; }
};
