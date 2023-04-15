# Author: Noe Ruano Gutierrez

#!/bin/bash

MSJ_ESPERA="microtools: esperando conexión con Micro:bit\n"

# Espera a que se conecte el Micro:bit (lectura de etiquetas en los sistemas de ficheros detectados)
if [ -z "$(lsblk -f | grep MICROBIT)" ]
then
    printf "$MSJ_ESPERA"
    while [ -z "$(lsblk -f | grep MICROBIT)" ]
    do
        sleep 1
    done
fi

# FIXME: realmente con hacer $ cat /dev/ttyACM0 haces lo mismo, a no ser que quieras enviar algo a la placa

screen /dev/ttyACM0 9600