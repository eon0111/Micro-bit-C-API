#!/bin/bash

# TODO: esto hay que meterlo en un Make

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -I ./ -c ../ubit/display.c -o ../ubit/display.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -I ./ -c ../ubit/botones.c -o ../ubit/botones.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -I ./ -c ../ubit/acelerometro.c -o ../ubit/acelerometro.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -I ./ -c ../ubit/buzzer.c -o ../ubit/buzzer.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding -I ./ -c ../ubit/misc.c -o ../ubit/misc.o
arm-none-eabi-ar cr ../ubit/ubit.a ../microbian/*.o ../ubit/display.o ../ubit/botones.o ../ubit/acelerometro.o ../ubit/buzzer.o ../ubit/misc.o