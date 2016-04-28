#!/bin/bash

SSID=$1

wpa_cli add_network
wpa_cli set_network 0 ssid $SSID
