#!/bin/bash

# Autor: Noé Ruano Gutiérrez

if [[ "$@" != *".c"* ]]
then
    echo "ubit-build: error: no indicó ningún fichero de código fuente (.c)"
    exit 22 # 22 = argumento no válido
fi

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

        if [[ $tmp != *".a"* && $tmp != *".c"* ]]
        then
            nombre_elf=$tmp
            nombre_hex=$tmp.hex
            break
        else
            echo "ubit-build: error: no indicó el nombre del ejecutable"
            exit 22
        fi
    fi
done

flags="-mcpu=cortex-m4 -mthumb -O2 -ffreestanding -I /usr/local/include -T /usr/share/ubit/nRF52833.ld"
libs="/usr/share/ubit/libubit.a -nostdlib -lgcc -lc "

if arm-none-eabi-gcc $flags $@ $libs
then
    arm-none-eabi-objcopy -O ihex $nombre_elf $nombre_hex
    rm $nombre_elf
fi
