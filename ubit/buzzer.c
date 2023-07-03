/**
 * @file buzzer.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el control del zumbador piezoeléctrico.
 * @version 1.0
 * @date jul-2023
 * 
 */

#include "ubit.h"

unsigned int periodo_us[] = {3822, 3405, 3033, 2863, 2551, 2272, 2024, 1911,
                             1702, 1516, 1431, 1275, 1136, 1012, 955};

/**
 * @brief Reproduce un tono de frecuencia igual al inverso del periodo
 * correspondiente a la nota "n" indicada, durante t_ms milisegundos.
 * 
 * @param n le nota a reproducir
 * @param t_ms la duración de la nota
 * 
 */
void
buzzer_reproduce_nota(nota_t n, int t_ms)
{
    int i, p = periodo_us[n] / 2, t_cc = 1000 * t_ms / (p * 2);

    for (i = 0; i < t_cc; i++)
    {
        gpio_out(BUZZER, 1);
        delay_loop(p);
        gpio_out(BUZZER, 0);
        delay_loop(p);
    }
}
