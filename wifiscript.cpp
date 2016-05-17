#include "wifiscript.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

void WifiNetworkAdder::OnOutput(const std::string& out)
{
  _netId = out;
  _netId = trim(_netId);
}

std::string WifiRemoveNetwork::GetCommandString()
{
  return "sudo \"PATH=$PATH\" bash wifi_remove_network.sh \"" + _netId + "\"";
}

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
