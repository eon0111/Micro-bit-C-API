/**
 * @file 02_display_enciende_apaga_led.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba el encendido y apagado de LEDs individuales
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

    int i, j;
    while (1)
    {
        for (i = 0; i < DISPLAY_DIM; i++)
        {
            for (j = 0; j < DISPLAY_DIM; j++)
            {
                display_enciende_LED((i%2 == 0) ? j : DISPLAY_DIM-1 - j, i);
                timer_delay(100);
            }
        }
        for (i = DISPLAY_DIM - 1; i >= 0; i--)
        {
            for (j = DISPLAY_DIM - 1; j >= 0; j--)
            {
                display_apaga_LED((i%2 == 0) ? j : DISPLAY_DIM-1 - j, i);
                timer_delay(100);
            }
        }
    }
}
