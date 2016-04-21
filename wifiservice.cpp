#include "wifiservice.h"
#include "globals.h"

void WifiService::FindConfig()
{
  for (auto& servicePtr : GetConfig().Entries())
  {
    auto service = *servicePtr;
    if (service.Contains("name") && service["name"] == _name)
    {
      auto config = std::shared_ptr<WifiConfig>(new WifiConfig);
      config->_username = service["username"];
      config->_password = service["password"];
      config->_enterprise = config->_password.length() > 0;
      config->_passphrase = service["passphrase"];
      config->_default = service["default"] == "true";
      _knownConfig = config;
      break;
    }
  }
}
