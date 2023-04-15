# Author: Noe Ruano Gutierrez

#!/bin/bash

MSJ_AYUDA=( ""
            "#####################"
            "# Micro:bit Toolkit #"
            "#####################"
            ""
            "1. Compilación:"
            "   $ ubit-build -o <nombre_ejecutable> <fuente.c> {librerías}"
            ""
            "2. Carga del ejecutable en la placa:"
            "   $ ubit-load <ejecutable.hex>"
            ""
            "3. Depuración:"
            "   3.1 GDB:"
            "   3.2 UART:"
            "       $ ubit-serial-debug ó $ cat /dev/ttyACM0"
            "")

printf '%s\n' "${MSJ_AYUDA[@]}"