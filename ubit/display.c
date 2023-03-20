/**
 * @file display.c
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del display de 5x5 LEDs.
 * @version 0.1
 * @date TODO
 * 
 */

#include "ubit.h"
#include "../microbian/microbian.h"
#include "../microbian/hardware.h"

#define DIM     5

typedef enum {
    true,
    false
} booleano;

image imagen_actual_microbian;
booleano imagen_actual_legible[DIM][DIM];

// TODO: no sé muy bien cómo enfocar lo de múltiples funciones que hagan lo mismo con distintos argumentos
typedef struct {
    int x;
    int y
} coordenada;

/**
 * @brief Wrapper para la rutina de inicialización del proceso de refresco
 * del display, proporcionada por la librería Microbian.
 * 
 */
void
display_inicializa()
{
    display_init();

    int i, j;
    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            imagen_actual_legible[i][j] = false;
}

/**
 * @brief Enciende un único LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 */
void
display_enciende_LED(int x, int y)
{
    image_set(x, y, imagen_actual_microbian);
    imagen_actual_legible[y][x] = true;
    display_show(imagen_actual_microbian);
}

/**
 * @brief Apaga un único LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 */
void
display_apaga_LED(int x, int y)
{
    image_clear(imagen_actual_microbian);
    imagen_actual_legible[y][x] = false;

    /*
     * La librería no implementa ninguna función que apague un LED. No obstante,
     * esto puede lograrse a partir de la función de encendido, creando una 
     * nueva imagen a partir del estado anterior a la modificación
     */ 
    int i, j;
    for (i = 0; i < DIM; i++)
        for (j = 0; i < DIM; j++)
            if (imagen_actual_legible[j][i] && i != x && j != y)
                image_set(i, j, imagen_actual_microbian);

    display_show(imagen_actual_microbian);
}

/**
 * @brief Retorna el estado de un LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 * @return El estado del LED, encendido (1) o apagado (0), o -1 si la coordenada
 * no es válida
 * 
 */
int
display_estado_LED(int x, int y)
{
    return (0 <= x && x <= 4 && 0 <= y && y <= 4) ? imagen_actual_legible[y][x] : -1;
}
