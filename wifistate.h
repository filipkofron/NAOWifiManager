#pragma once

#include <string>

namespace WifiState
{
  enum WifiState
  {
    Idle,
    Online,
    Unknown,
  };
}

class WifiStateUtils
{
public:
  static WifiState::WifiState StringToWifiState(const std::string& stateStr);
  static std::string WifiStateToString(const WifiState::WifiState& state);
};
