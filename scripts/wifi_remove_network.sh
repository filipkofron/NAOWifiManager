#!/bin/bash

NET=$1
LOG='/tmp/wifi-script.log'
wpa_cli remove_network $NET 2>&1 >> $LOG
