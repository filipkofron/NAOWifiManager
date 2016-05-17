#!/bin/bash

SSID=$1
PASSWORD=$2
LOG='/tmp/wifi-script.log'
NET=`wpa_cli add_network | tail -1`
IF=`wpa_cli set_network $NET ssid \"$SSID\" | head -1 | cut -d\' -f2`
wpa_cli set_network $NET key_mgmt WPA-PSK >&1 >> $LOG
wpa_cli set_network $NET psk \"$PASSWORD\" >&1 >> $LOG
wpa_cli select_network $NET >&1 >> $LOG
dhcpcd $IF >&1 >> $LOG
dhclient $IF >&1 >> $LOG
echo $NET
