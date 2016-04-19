#pragma once

#include <string>

enum class WifiState
{
  Idle,
  Online,
  Unknown,
};

class WifiStateUtils
{
public:
  static WifiState StringToWifiState(const std::string& stateStr);
  static std::string WifiStateToString(const WifiState& state);
};
