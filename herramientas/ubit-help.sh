# Author: Noe Ruano Gutierrez

#!/bin/bash

MSJ_AYUDA=( ""
            "#####################"
            "# Micro:bit Toolkit #"
            "#####################"
            ""
            "1. Compilación:"
            "   $ ubit-build <fuente.c>"
            ""
            "2. Carga del ejecutable en la placa:"
            "   $ ubit-load <ejecutable.hex>"
            ""
            "3. Depuración:"
            "   3.1 GDB:"
            "   3.2 UART:"
            "       $ ubit-serial-debug"
            "")

printf '%s\n' "${MSJ_AYUDA[@]}"