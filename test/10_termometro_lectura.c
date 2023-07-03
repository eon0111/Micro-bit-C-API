/**
 * @file prueba-temp.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba la lectura de la temperatura del microcontrolador
 * @version 1.0
 * @date jul-2023
 * 
 */

#include <ubit.h>

void
main(int n)
{
    while (1)
    {
        printf("temp: %d\n", (int)termometro_lectura());
        timer_delay(500);
    }
}
