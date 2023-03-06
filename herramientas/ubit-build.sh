# Autor: Noé Ruano Gutiérrez

#!/bin/bash

MSJ_ERR_FICH="ubit-build: error: $1 no es un fichero de código fuente C válido\n"
MSJ_AYUDA=( "Uso"
            "   ubit-build <fichero.c>"
            ""
            "opciones:"
            "   -h      muestra esta ayuda")

while getopts 'h' flag
do
    case ${flag} in
        h)  printf '%s\n' "${MSJ_AYUDA[@]}"
		    exit
            ;;
        *)  exit
            ;;
    esac
done

# Comprueba que el fichero es un .C válido
if [ -z "$(file $1 | grep "C source")" ]
then
    printf "$MSJ_ERR_FICH"
    exit
fi

fuente=$(echo $1 | awk -F "." '{print $1}')

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -I ../microbian -c $fuente.c -o tmp.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -T ../microbian/nRF52833.ld tmp.o ../microbian/microbian.a ../microbian/startup.o -nostdlib -lgcc -lc -o tmp.elf -Wl,-Map,tmp.map
arm-none-eabi-objcopy -O ihex tmp.elf $fuente.hex
rm -f tmp*