# Autor: Noé Ruano Gutiérrez

#!/bin/bash

MSJ_ERR_NO_PARAM="microtools: error: No se inidicó ninguna acción\n"
MSJ_AYUDA=(	""
			"Este comando debe ser invocado con privilegios de superusuario"
			""
			"Uso:"
			"  microtools -l fich.hex"
			"  microtools -l fich.hex -d"
			"  microtools -d"
			"  microtools -h"
			""
			"Opciones:"
			"  -l <ejecutable>   carga un ejecutable en la placa"
			"  -d                abre la ventana de depuración a través de la interfaz serie"
			"  -h                muestra la ayuda"
			"")
MSJ_IDK_PARAM="microtools: $param: Parámetro desconocido\n"
MSJ_NO_ROOT="microtools: error: debe ser superusuario para utilizar las herramientas\n"
MSJ_ERR_NO_HEX="microtools: error: no se indicó un nombre de fichero (.hex) válido\n"
MSJ_ESPERA="microtools: esperando conexión con Micro:bit\n"
MSJ_CARGANDO="microtools: cargando ejecutable\n"
MSJ_FIN="microtools: carga completada!!\n"

TMP_DIR="/tmp/microbit"

# Espera a que se conecte el Micro:bit (lectura de etiquetas en los sistemas de ficheros detectados)
function espera_mbit() {
	if [ -n "$(lsblk -f | grep MICROBIT)" ]
	then
		exit
	fi
	printf "$MSJ_ESPERA"
	while [ -z "$(lsblk -f | grep MICROBIT)" ]
	do
		sleep 1
	done
}

# El script debe ejecutar con privilegios de root para que funcione el montaje de la partición más adelante
if [ $(id -u) -ne 0 ]
then
	printf "$MSJ_NO_ROOT"
	exit
fi

# Comprueba que se pasa al menos un flag, si no no hace nada
if [ -z "$@" ]
then
	printf "$MSJ_ERR_NO_PARAM"
	exit
fi

for param in $@
do
	case $param in
	-f) # Compila y carga el código

		## TODO ##

		exit
		;;

	-l)	# Cargar .hex
		if [ -z "$2" ] ## TODO ## Comprobar extensión del fichero y, si se puede, el tipo de fichero real, no en base a la extensión
		then
			printf "$MSJ_ERR_NO_HEX"
			exit
		fi
		espera_mbit

		# Obtiene el nombre que le ha dado el SO a la partición (/dev/sdX)
		fs_name=$(lsblk -f | grep MICROBIT | awk '{print $1}')

		pm=""

		# Comprueba que está montado el FS de la placa
		if [ -z "$(df | grep $fs_name)" ]
		then
			mkdir $TMP_DIR
			mount /dev/$fs_name $TMP_DIR
			pm=$TMP_DIR
		else
			pm=$(df | grep $fs_name | awk '{print $6}')	# Obtiene el punto de montaje de la placa
		fi

		# Carga el código en la placa y la desmonta
		printf "$MSJ_CARGANDO"
		cp $2 $pm
		umount $pm

		if [ -d "$TMP_DIR" ]
		then
			rmdir $TMP_DIR
		fi

		printf "$MSJ_FIN"
		exit
		;;

	-d) # Abrir ventana de depuración por interfaz serie
		espera_mbit
		screen /dev/ttyACM0
		exit
		;;

	-h) # Mostrar ayuda
		printf '%s\n' "${MSJ_AYUDA[@]}"
		exit
		;;

	*)	# Flag desconocido
		printf "$MSJ_IDK_PARAM"
		exit
		;;
	esac
done