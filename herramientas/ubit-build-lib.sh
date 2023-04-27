#!/bin/bash

# TODO: esto hay que meterlo en un Make...

flags="-mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -I ./"

arm-none-eabi-gcc $flags -c ../ubit/display.c -o ../ubit/display.o
arm-none-eabi-gcc $flags -c ../ubit/botones.c -o ../ubit/botones.o
arm-none-eabi-gcc $flags -c ../ubit/acelerometro.c -o ../ubit/acelerometro.o
arm-none-eabi-gcc $flags -c ../ubit/buzzer.c -o ../ubit/buzzer.o
arm-none-eabi-gcc $flags -c ../ubit/misc.c -o ../ubit/misc.o
arm-none-eabi-ar cr ../ubit/ubit.a ../microbian/*.o ../ubit/*.o