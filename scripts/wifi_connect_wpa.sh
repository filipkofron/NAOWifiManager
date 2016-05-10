#!/bin/bash

SSID=$1
PASSWORD=$2

NET=`wpa_cli add_network | tail -1`
IF=`wpa_cli set_network $NET ssid \"$SSID\" | head -1 | cut -d\' -f2`
wpa_cli set_network $NET key_mgmt WPA-PSK
wpa_cli set_network $NET psk \"$PASSWORD\"
wpa_cli select_network $NET
dhcpcd $IF 2>/dev/null
dhclient $IF 2>/dev/null
