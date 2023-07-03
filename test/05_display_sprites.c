/**
 * @file 05_display_sprites.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba la presentación de todos los sprites disponibles en la librería
 * por medio de las funciones display_char2codi y display_muestra_sprite
 * @version 1.0
 * @date jul-2023
 * 
 */

#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();
    display_cambia_intensidad(INT_BAJA);

    char *caracteres = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";
    char *tmp;
    
    int i;
    for (i = 0; i < 64; i++)
    {
        display_char2codi(caracteres[i], &tmp);
        display_muestra_sprite(tmp);
        timer_delay(500);
    }
}
