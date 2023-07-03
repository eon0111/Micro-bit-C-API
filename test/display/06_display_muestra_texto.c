/**
 * @file 06_display_muestra_texto.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba la presentación de un texto en el display a distintas velocidades
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

    char *str = "MICROBIT";

    display_muestra_texto(str, RAPIDO);
    timer_delay(1000);
    display_muestra_texto(str, MEDIO);
    timer_delay(1000);
    display_muestra_texto(str, LENTO);
}
