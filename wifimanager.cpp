#include "wifimanager.h"
#include "globals.h"

WifiManager::WifiManager()
{
  TestListWifi();
}


void WifiManager::TestListWifi()
{
  std::string serviceOff;
  std::string serviceOn;
  GetConnectionProxy().scan();
  auto services = GetConnectionProxy().services();
  //std::cout << "state: " << _connectionManagerProxy.state() << std::endl;
  //std::cout << "list wifi: " << _connectionManagerProxy.services() << std::endl;
  for (int i = 0; i < services.getSize(); i++)
  {
    std::cout << "item[" << i << "]: " << services[i] << std::endl;
    std::map<std::string, std::string> details;
    for (int j = 0; j < services[i].getSize(); j++)
    {
      std::cout << " -- " << services[i][j] << std::endl;
      std::string name = services[i][j][0];
      std::string val;
      if (services[i][j][1].isString())
        val = (std::string) services[i][j][1];
      else
        val = services[i][j][1].toString();
      details[name] = val;
    }
    for (auto& item : details)
    {
      std::cout << item.first << ": " << item.second << std::endl;
    }

    if (details["State"] == "online")
    {
      serviceOff = details["ServiceId"];
    }

    if (details["Name"] == "eduroam")
    {
      std::cout << "Connecting to service Id: " << details["ServiceId"] << std::endl;
      serviceOn = details["ServiceId"];
    }
  }
  GetConnectionProxy().disconnect(serviceOff);
  GetConnectionProxy().connect(serviceOn);
}

virtual WifiManager::OnNetworkStatusChanged()
{

}
