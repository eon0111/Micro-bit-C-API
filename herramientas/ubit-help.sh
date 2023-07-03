#!/bin/bash

# Autor: Noé Ruano Gutiérrez

MSJ_AYUDA=( ""
            "- Micro:bit Toolkit -"
            ""
            "1. Compilación:"
            ""
            "   $ ubit-gcc -o <nombre_ejecutable> <fuente>.c {librerías}"
            ""
            "2. Carga del ejecutable en la placa:"
            ""
            "   $ ubit-load <ejecutable (.hex)>"
            ""
            "3. Depuración:"
            ""
            "   $ cat /dev/ttyACM0"
            "")

printf '%s\n' "${MSJ_AYUDA[@]}"
