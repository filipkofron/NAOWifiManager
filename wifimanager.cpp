#include "wifimanager.h"
#include "globals.h"
#include "wifi.h"

WifiManager::WifiManager()
{
}

void WifiManager::ChooseWifi(const std::string& name)
{
  _selectedSSID = name;
  Disconnect();
  Connect();
}

std::string WifiManager::GetConnectedToAnyId() const
{
  for (const auto& service : _services)
  {
    if (service._state == WifiState::Online || service._state == WifiState::Idle)
      return service.Id();
  }
  return "";
}

std::string WifiManager::GetSelectedId() const
{
  for (const auto& service : _services)
  {
    if (service._name == _selectedSSID)
      return service.Id();
  }
  return "";
}

void WifiManager::Disconnect()
{
  if (IsConnectedToAny())
  {
    AL::Say("Odpojuji se");
    //GetConnectionProxy().disconnect(GetConnectedToAnyId());
  }
}

void WifiManager::Connect()
{
  if (IsSelectedNetworkAvailable())
  {
    AL::Say("Připojuji se k " + _selectedSSID);
    GetConnectionProxy().connect(GetSelectedId());
  }
}

void WifiManager::OnNetworkServiceInputRequired()
{
  std::shared_ptr<WifiConfig> config;
  for (auto& service : _services)
  {
    if (service._name == _selectedSSID)
      config = service._knownConfig;
  }
  if (!config)
    return;

  AL::ALValue input;

  if (config->_enterprise)
  {
    input.arraySetSize(2);

    AL::ALValue identity;
    identity.arraySetSize(2);
    identity[0] = "Identity";
    identity[1] = config->_username;

    /*AL::ALValue user;
    user.arraySetSize(2);
    user[0] = "Username";
    user[1] = config->_username;*/

    AL::ALValue pass;
    pass.arraySetSize(2);
    pass[0] = "Password";
    pass[1] = config->_password;

    input[0] = identity;
    input[1] = pass;

    //input[0] = user;
    //input[1] = identity;
    //input[2] = pass;
  }
  else
  {
    input.arraySetSize(1);
    AL::ALValue pass;
    pass.arraySetSize(2);
    pass[0] = "Passphrase";
    pass[1] = config->_passphrase;
    input[0] = pass;
  }

  std::cout << "Setting requested input to: " << input << std::endl;

  GetConnectionProxy().setServiceInput(input);
}

void WifiManager::UpdateList()
{
  std::string serviceOff;
  std::string serviceOn;
  GetConnectionProxy().scan();
  auto serviceList = GetConnectionProxy().services();
  _services.clear();
  for (int i = 0; i < serviceList.getSize(); i++)
  {
    //std::cout << "item[" << i << "]: " << serviceList[i] << std::endl;
    std::map<std::string, std::string> details;
    for (int j = 0; j < serviceList[i].getSize(); j++)
    {
      //std::cout << " -- " << serviceList[i][j] << std::endl;
      std::string name = serviceList[i][j][0];
      std::string val;
      if (serviceList[i][j][1].isString())
        val = (std::string) serviceList[i][j][1];
      else
        val = serviceList[i][j][1].toString();
      details[name] = val;
    }
    /*for (auto& item : details)
    {
      std::cout << item.first << ": " << item.second << std::endl;
    }*/

    WifiService service;
    service._id = details["ServiceId"];
    service._name = details["Name"];
    service._state = WifiStateUtils::StringToWifiState(details["State"]);
    service.FindConfig();
    _services.push_back(service);

    if (service._knownConfig && service._knownConfig->_default && _selectedSSID.empty())
      _selectedSSID = service._name;
  }
}

bool WifiManager::IsSelectedNetworkAvailable() const
{
  for (const auto& service : _services)
  {
    if (service._name == _selectedSSID)
      return true;
  }
  return false;
}

bool WifiManager::IsConnectedToSelected() const
{
  for (const auto& service : _services)
  {
    if (service._name == _selectedSSID && (service._state == WifiState::Online|| service._state == WifiState::Idle))
      return true;
  }
  return false;
}


bool WifiManager::IsConnectedToAny() const
{
  for (const auto& service : _services)
  {
    if (service._state == WifiState::Online || service._state == WifiState::Idle)
      return true;
  }
  return false;
}

void WifiManager::OnNetworkConnectStatus(const std::string& status)
{
  if (status == "true")
    AL::Say("Připojen k " + _selectedSSID);
  else
    AL::Say("Připojení k " + _selectedSSID + " selhalo");
}

void WifiManager::OnNetworkStatusChanged(const std::string& status)
{
  UpdateList();

  if (!IsConnectedToSelected())
  {
    if (IsSelectedNetworkAvailable())
    {
      Disconnect();
      Connect();
    }
  }
}
