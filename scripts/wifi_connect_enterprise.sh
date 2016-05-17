#!/bin/bash

SSID=$1
USERNAME=$2
PASSWORD=$3
LOG='/tmp/wifi-script.log'
NET=`wpa_cli add_network | tail -1`
IF=`wpa_cli set_network $NET ssid \"$SSID\" | head -1 | cut -d\' -f2`
# wpa_cli set_network $NET scan_ssid 1
wpa_cli set_network $NET proto WPA2 >&1 >> $LOG
wpa_cli set_network $NET priority 1 >&1 >> $LOG
wpa_cli set_network $NET key_mgmt WPA-EAP >&1 >> $LOG
wpa_cli set_network $NET eap PEAP >&1 >> $LOG
# wpa_cli set_network $NET pairwise CCMP
wpa_cli set_network $NET group TKIP #CCMP >&1 >> $LOG
wpa_cli set_network $NET identity \"$USERNAME\" >&1 >> $LOG
wpa_cli set_network $NET password \"$PASSWORD\" >&1 >> $LOG
wpa_cli set_network $NET phase2 \"auth=MSCHAPV2\" >&1 >> $LOG
wpa_cli select_network $NET >&1 >> $LOG
dhcpcd $IF >&1 >> $LOG
dhclient $IF >&1 >> $LOG
echo $NET
