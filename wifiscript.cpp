#include "wifiscript.h"

std::string WifiConnectToOpen::GetCommandString()
{
  return "sudo \"PATH=$PATH\" bash wifi_connect_open.sh \"" + _ssid + "\"";
}

std::string WifiConnectToWPA::GetCommandString()
{
  return "sudo \"PATH=$PATH\" bash wifi_connect_wpa.sh \"" + _ssid + "\" \"" + _password + "\"";
}

std::string WifiConnectToEnterprise::GetCommandString()
{
  return "sudo \"PATH=$PATH\" bash wifi_connect_enterprise.sh \"" + _ssid + "\" \"" + _username + "\" \"" + _password + "\"";
}
