/**
 * @file botones.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo de los botones A y B, así como el
 * botón táctil.
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"

static unsigned int botones[] = {BUTTON_A, BUTTON_B, TOUCH_BUTTON_LOGO, 
                                 TOUCH_BUTTON_0, TOUCH_BUTTON_1, TOUCH_BUTTON_2};

/**
 * @brief Retorna el estado de un botón.
 * 
 * @param b El botón cuyo estado quiere conocerse
 * @return int 1 si el botón está pulsado o 0 si no lo está
 */
int
boton_pulsado(boton_t b)
{
    return (b < BOTON_A || b > BOTON_2) ? -1 : !gpio_in(botones[b]) & 0x1;
}

/**
 * @brief Realiza una espera activa a la espera de que se pulse un botón 
 * concreto.
 * 
 * @param b El botón cuya pulsación debe detectarse
 * @return int -1 si el botón indicado no se corresponde con ninguno de los 
 * contemplados, o 0 una vez el botón ha sido pulsado
 */
int
boton_espera_pulsacion(boton_t b)
{
    if (b < BOTON_A || b > BOTON_2) return -1;

    while (!boton_pulsado(b)) timer_delay(100);

    return 0;
}
