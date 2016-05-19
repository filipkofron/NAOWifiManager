#!/bin/bash

rm -f ../distr.tar.gz
mkdir -p ../distr
rm -rf ../distr/*

cp /home/kofi/ownCloud/School/MI-IVS/data/projects/sem-build/build-robot/wifi/sdk/lib/naoqi/libwifi.so ../distr/
mkdir -p ../distr/etc
cp /etc/wifilist ../distr/etc/
cp -rv scripts ../distr/

cd ..
tar czvf distr.tar.gz distr
scp distr.tar.gz kofi@halt.cz:/mnt/nas/public/pub/
