#!/bin/bash

SSID=$1
PASSWORD=$2

wpa_cli add_network
wpa_cli set_network 0 ssid $SSID
wpa_cli set_network 0 key_mgmt WPA-PSK
wpa_cli set_network 0 psk $PASSWORD
