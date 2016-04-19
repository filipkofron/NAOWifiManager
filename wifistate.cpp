#include "wifistate.h"

WifiState WifiStateUtils::StringToWifiState(const std::string& stateStr)
{
  if (stateStr == "idle")
    return WifiState::Idle;

  if (stateStr == "online")
    return WifiState::Idle;

  return WifiState::Unknown;
}

std::string WifiStateUtils::WifiStateToString(const WifiState& state)
{
  switch(state)
  {
  case WifiState::Idle:
    return "idle";
  case WifiState::Online:
    return "online";
  default:
    return "unknown";
  }
}
