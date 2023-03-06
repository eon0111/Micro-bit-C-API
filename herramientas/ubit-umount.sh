# Autor: Noé Ruano Gutiérrez

#!/bin/bash

MSJ_NO_MONTADO="ubit-umount: info.: el sistema de ficheros de la placa no está montado"

nombre_fs=$(lsblk -f | grep MICROBIT | awk '{print $1}')    # obtiene el sdX en /dev
punto_montaje=$(df | grep $nombre_fs | awk '{print $6}')

if [ -z "$punto_montaje" ]
then
    printf "$MSJ_NO_MONTADO"
    exit
fi

umount $punto_montaje