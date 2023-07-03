#!/bin/bash

# Autor: Noé Ruano Gutiérrez

MSJ_NO_ROOT="ubit-load: error: debe ejecutar la herramienta con privilegios de superusuario\n"
MSJ_ERR_NO_HEX="ubit-load: error: no se indicó el fichero a cargar\n"
MSJ_ERR_BAD_EXT="ubit-load: error: el ejecutable no tiene la extensión adecuada (.hex)\n"
MSJ_ESPERA="ubit-load: esperando conexión con Micro:bit\n"
MSJ_FIN="ubit-load: carga completada!!\n"

TMP_DIR="/mnt/microbit"

# El script debe ejecutar con privilegios de root para que funcione el montaje de la partición más adelante
if [ $(id -u) -ne 0 ]
then
	printf "$MSJ_NO_ROOT"
	exit
fi

# Cargar .hex
if [ -z "$1" ]
then
    printf "$MSJ_ERR_NO_HEX"
    exit
elif [ -z "$(echo $1 | grep .hex)" ]
then
    printf "$MSJ_ERR_BAD_EXT"
    exit
fi

# Espera a que se conecte el Micro:bit (lectura de etiquetas en los sistemas de ficheros detectados)
if [ -z "$(lsblk -f | grep MICROBIT)" ]
then
    printf "$MSJ_ESPERA"
    while [ -z "$(lsblk -f | grep MICROBIT)" ]
    do
        sleep 1
    done
fi

# Obtiene el nombre que le ha dado el SO a la partición (/dev/sdX)
nombre_fs=$(lsblk -f | grep MICROBIT | awk '{print $1}')

# Comprueba si está montado el FS de la placa
punto_montaje=""
if [ -z "$(df | grep $nombre_fs)" ]
then
    if ! [ -d $TMP_DIR ]
    then
        mkdir $TMP_DIR
    fi
    mount /dev/$nombre_fs $TMP_DIR
    punto_montaje=$TMP_DIR
else
    punto_montaje=$(df | grep $nombre_fs | awk '{print $6}')	# Obtiene el punto de montaje de la placa
fi

# Carga el código en la placa
printf "$MSJ_CARGANDO"
cp $1 $punto_montaje
umount $punto_montaje   # Si no se desmonta el FS no se flashea el ejecutable
printf "$MSJ_FIN"
