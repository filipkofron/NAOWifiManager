#include "wifiservice.h"
#include "globals.h"

void WifiService::FindConfig()
{
  for (std::vector<boost::shared_ptr<ParamEntry> >::iterator wifi = GetConfig().Entries().begin(); wifi != GetConfig().Entries().end(); wifi++)
  {
    if ((*wifi)->Contains("section") && (**wifi)["section"] == "Wifi")
    {
      for (std::vector<boost::shared_ptr<ParamEntry> >::iterator servicePtr = (*wifi)->Entries().begin(); servicePtr != (*wifi)->Entries().end(); servicePtr++)
      {
        if ((*servicePtr)->Contains("name") && (**servicePtr)["name"] == _name)
        {
          boost::shared_ptr<WifiConfig> config = boost::shared_ptr<WifiConfig>(new WifiConfig);
          config->_username = (**servicePtr)["username"];
          config->_password = (**servicePtr)["password"];
          config->_enterprise = config->_password.length() > 0;
          config->_passphrase = (**servicePtr)["passphrase"];
          config->_default = (**servicePtr)["default"] == "true";
          _knownConfig = config;
          break;
        }
      }
    }
  }
}
