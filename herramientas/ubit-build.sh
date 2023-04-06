# Autor: Noé Ruano Gutiérrez

#!/bin/bash

nombre_elf="a.out"
nombre_hex="a.hex"
num_palabras=$(echo $@ | wc -w)

# Busca el nombre del ejecutable para generar un ejecutable (.hex) con ese
# nombre, porque si el fichero no es .hex salta el error 504 en la placa
for ((i = 1; i <= $num_palabras; i++))
do
    tmp=$(echo $@ | awk -v indice=$i '{print $indice}')

    if [ $tmp == "-o" ]
    then
        tmp=$(echo $@ | awk -v indice=$(($i+1)) '{print $indice}')

        if [ ! -z $tmp ]
        then
            nombre_elf=$tmp
            nombre_hex=$tmp.hex
            break
        fi
    fi
done

flags="-mcpu=cortex-m4 -mthumb -O2 -ffreestanding -T ../microbian/nRF52833.ld"
libs="-nostdlib -lgcc -lc"

if arm-none-eabi-gcc $flags $@ ../ubit/ubit.a $libs # TODO: conseguir que funcione con -lubit
then
    arm-none-eabi-objcopy -O ihex $nombre_elf $nombre_elf.hex
    rm $nombre_elf
fi