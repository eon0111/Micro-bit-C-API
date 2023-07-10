#!/bin/bash

# El script debe ejecutar con privilegios de root
if [ $(id -u) -ne 0 ]
then
	printf "$MSJ_NO_ROOT"
	exit
fi

apt install -y gcc-arm-none-eabi
apt install -y libpng-dev
dpkg -i ubit-1.0-1-amd64.deb