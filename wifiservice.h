#pragma once

#include "wifistate.h"
#include <boost/shared_ptr.hpp>

struct WifiConfig
{
  bool _default;
  bool _enterprise;
  std::string _username;
  std::string _password;
  std::string _passphrase;
};

struct WifiService
{
  std::string _name;
  std::string _id;
  WifiState::WifiState _state;
  boost::shared_ptr<WifiConfig> _knownConfig;

  void FindConfig();

  std::string& Name() { return _name; }
  std::string& Id() { return _id; }
  WifiState::WifiState& State() { return _state; }

  const std::string& Name() const { return _name; }
  const std::string& Id() const { return _id; }
  const WifiState::WifiState& State() const { return _state; }
};
