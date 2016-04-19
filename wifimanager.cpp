#include "wifimanager.h"
#include "globals.h"

WifiManager::WifiManager()
{
}

void WifiManager::ChooseWifi(const std::string& name)
{
  _selectedSSID = name;
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

void WifiManager::OnNetworkServiceInputRequired()
{
  AL::ALValue input;
  input.arraySetSize(2);

  AL::ALValue user;
  user.arraySetSize(2);
  user[0] = "Username";
  user[1] = "kofrofil@fit.cvut.cz";

  AL::ALValue pass;
  pass.arraySetSize(2);
  pass[0] = "Password";
  pass[1] = "BysChtelVedet";

  input[0] = user;
  input[1] = pass;
  GetConnectionProxy().setServiceInput(input);
}

void WifiManager::OnNetworkStatusChanged()
{

}
