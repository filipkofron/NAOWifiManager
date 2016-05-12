#include "wifimanager.h"
#include "globals.h"
#include "wifi.h"
#include "wifiscript.h"

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
  for (std::vector<WifiService>::const_iterator it = GetWifiManager().Services().begin(); it != GetWifiManager().Services().end(); it++)
  {
    if (it->_state == WifiState::Online || it->_state == WifiState::Idle)
      return it->Id();
  }
  return "";
}

std::string WifiManager::GetSelectedId() const
{
  for (std::vector<WifiService>::const_iterator it = GetWifiManager().Services().begin(); it != GetWifiManager().Services().end(); it++)
  {
    if (it->_name == _selectedSSID)
      return it->Id();
  }
  return "";
}

void WifiManager::Disconnect()
{
  if (IsConnectedToAny())
  {
    AL::Say("Odpojuji se");
    // GetConnectionProxy().disconnect(GetConnectedToAnyId());
  }
}

void WifiManager::Connect()
{
  if (IsSelectedNetworkAvailable())
  {
    AL::Say("Připojuji se k " + _selectedSSID);

    boost::shared_ptr<WifiConfig> config;
    for (std::vector<WifiService>::const_iterator it = GetWifiManager().Services().begin(); it != GetWifiManager().Services().end(); it++)
    {
      if (it->_name == _selectedSSID)
        config = it->_knownConfig;
    }
    if (!config)
      return;

    boost::shared_ptr<ScriptCommand> wifi;

    if (config->_enterprise)
    {
      wifi = boost::shared_ptr<ScriptCommand>(new WifiConnectToEnterprise(_selectedSSID, config->_username, config->_password));
    }
    else if (config->_passphrase.empty())
    {
      wifi = boost::shared_ptr<ScriptCommand>(new WifiConnectToOpen(_selectedSSID));
    }
    else
    {
      wifi = boost::shared_ptr<ScriptCommand>(new WifiConnectToWPA(_selectedSSID, config->_passphrase));
    }

    std::string output;
    wifi->Execute(output);
    std::cout << "ScriptCommand to connect to wifi, output: '" << output << "'" << std::endl;
  }
}

void WifiManager::OnNetworkServiceInputRequired()
{
}

void WifiManager::UpdateList()
{
  // reload config
  ParamEntry::Reload();

  std::string serviceOff;
  std::string serviceOn;
#if !WIFI_LOCAL_TEST
  GetConnectionProxy().scan();
  AL::ALValue serviceList = GetConnectionProxy().services();
  // std::cout << serviceList << std::endl;
#else // !LOCAL_TEST
  AL::ALValue serviceList;
#endif // !LOCAL_TEST
  _services.clear();
  for (int i = 0; i < serviceList.getSize(); i++)
  {
    // std::cout << "item[" << i << "]: " << serviceList[i] << std::endl;
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

#if WIFI_LOCAL_TEST


  WifiService service;
  service._id = "whatever";
  service._name = "YETTI";
  service._state = WifiStateUtils::StringToWifiState("Idle");
  service.FindConfig();
  _services.push_back(service);

  if (service._knownConfig && service._knownConfig->_default && _selectedSSID.empty())
    _selectedSSID = service._name;

#endif // WIFI_LOCAL_TEST
}

bool WifiManager::IsSelectedNetworkAvailable() const
{
  for (std::vector<WifiService>::const_iterator it = GetWifiManager().Services().begin(); it != GetWifiManager().Services().end(); it++)
  {
    if (it->_name == _selectedSSID)
      return true;
  }
  return false;
}

bool WifiManager::IsConnectedToSelected() const
{
  for (std::vector<WifiService>::const_iterator it = GetWifiManager().Services().begin(); it != GetWifiManager().Services().end(); it++)
  {
    if (it->_name == _selectedSSID && (it->_state == WifiState::Online))
      return true;
  }
  return false;
}


bool WifiManager::IsConnectedToAny() const
{
  for (std::vector<WifiService>::const_iterator it = GetWifiManager().Services().begin(); it != GetWifiManager().Services().end(); it++)
  {
    if (it->_state == WifiState::Online)
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
