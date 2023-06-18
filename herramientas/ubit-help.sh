#!/bin/bash

# Autor: Noé Ruano Gutiérrez

MSJ_AYUDA=( ""
            "- Micro:bit Toolkit -"
            ""
            "1. Compilación:"
            ""
            "   $ ubit-build -o <nombre_ejecutable> <fuente>.c {librerías}"
            ""
            "2. Carga del ejecutable en la placa:"
            ""
            "   $ ubit-load <ejecutable>"
            ""
            "3. Depuración:"
            ""
            "   3.1 GDB: TODO"
            "   3.2 UART:"
            "       $ cat /dev/ttyACM0"
            "")

printf '%s\n' "${MSJ_AYUDA[@]}"