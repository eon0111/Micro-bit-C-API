/**
 * @file botones.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo de los dos botones A y B.
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"

/**
 * @brief Retorna el estado del botón A.
 * 
 * @return int 1 si el botón está pulsado en el momento de la comprobación, 0 en
 * otro caso
 */
int
boton_A_pulsado()
{
    /* NOTE: la negación es bit a bit (!0b0...1 = 0b1...10). Me interesa el
     * último bit, que es el que contiene el estado del botón, el resto no
     * indican absolutamente nada */
    return !gpio_in(BUTTON_A) & 0x1;
}

/**
 * @brief Retorna el estado del botón B.
 * 
 * @return int 1 si el botón está pulsado en el momento de la comprobación, 0 en
 * otro caso
 */
int
boton_B_pulsado()
{
    return !gpio_in(BUTTON_B) & 0x1;
}

/* NOTE: creo que las funciones de "espera_boton" son prescindibles (no cuesta
 * tanto construir el bucle de comprobación...) */

/**
 * @brief Realiza una espera activa en tanto no se haya pulsado el botón A.
 * 
 */
void
boton_A_espera_pulsacion()
{
    while (!boton_A_pulsado()) timer_delay(100);
}

/**
 * @brief Realiza una espera activa en tanto no se haya pulsado el botón B.
 * 
 */
void
boton_B_espera_pulsacion()
{
    while (!boton_B_pulsado()) timer_delay(100);
}
