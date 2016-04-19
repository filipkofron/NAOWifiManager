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
      config->_username = service["password"];
      config->_default = service["password"] == "true";
      _knownConfig = config;
      break;
    }
  }
}
