#!/bin/bash

SSID=$1
USERNAME=$2
PASSWORD=$3

NET=`wpa_cli add_network | tail -1`
IF=`wpa_cli set_network $NET ssid \"$SSID\" | head -1 | cut -d\' -f2`
# wpa_cli set_network $NET scan_ssid 1
wpa_cli set_network $NET proto WPA2
wpa_cli set_network $NET priority 1
wpa_cli set_network $NET key_mgmt WPA-EAP
wpa_cli set_network $NET eap PEAP
# wpa_cli set_network $NET pairwise CCMP
wpa_cli set_network $NET group TKIP #CCMP
wpa_cli set_network $NET identity \"$USERNAME\"
wpa_cli set_network $NET password \"$PASSWORD\"
wpa_cli set_network $NET phase2 \"auth=MSCHAPV2\"
wpa_cli select_network $NET
dhcpcd $IF 2>/dev/null
dhclient $IF 2>/dev/null

