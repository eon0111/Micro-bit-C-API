/**
 * @file buzzer.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el control del zumbador piezoeléctrico.
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"


unsigned int periodo_us[] = {3822, 3405, 3033, 2863, 2551, 2272, 2024, 1911,
                             1702, 1516, 1431, 1275, 1136, 1012, 955};

void
buzzer_reproduce_nota(nota_t n, int t_ms)
{
    int i, p = periodo_us[n] / 2, t_cc = 1000 * t_ms / (p * 2); /* FIXME: el 2 es para compensar los ciclos de reloj que conllevan las funciones empleadas. Se podría mirar en el .hex para ver cuántas instrucciones se ejecutan en el bucle para tener un ajuste más preciso... */

    for (i = 0; i < t_cc; i++)
    {
        gpio_out(BUZZER, 1);
        delay_loop(p);  /* NOTE: delay_loop() se queda iterando en un bucle haciendo NOPs por p microsegundos */
        gpio_out(BUZZER, 0);
        delay_loop(p);
    }
}
