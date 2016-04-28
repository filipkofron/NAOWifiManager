#!/bin/bash

SSID=$1
USERNAME=$2
PASSWORD=$3

wpa_cli add_network
wpa_cli set_network 0 ssid $SSID
wpa_cli set_network 0 scan_ssid 1
wpa_cli set_network 0 proto WPA2
wpa_cli set_network 0 priority 1
wpa_cli set_network 0 key_mgmt WPA-EAP
wpa_cli set_network 0 eap PEAP
wpa_cli set_network 0 pairwise CCMP
wpa_cli set_network 0 group CCMP
wpa_cli identity 0 $USERNAME
wpa_cli password 0 $PASSWORD
wpa_cli set_network 0 phase2 \"auth=MSCHAPV2\"
wpa_cli select_network 0
