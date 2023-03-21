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

/* El conjunto de señales que controlan el estado de los LEDs en Microbian */
image imagen_actual_microbian;

/* El conjunto de valores booleanos que indican el estado de los LEDs */
bool imagen_actual_legible[DISPLAY_DIM][DISPLAY_DIM];

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
    // TODO: todas estas funciones de inicialización de dispositivos pueden agruparse en un wrapper que las llame a todas, para que el usuario no tenga que ir dispositivo a dispositivo haciendo las inicializaciones
    serial_init();

    /* NOTE: La tarea de refresco del display requiere que el timer se encuentre
     * inicializado para poder realizar el refresco del display cada 15ms */
    timer_init();
    display_init();

    image_clear(imagen_actual_microbian);

    int i, j;
    for (i = 0; i < DISPLAY_DIM; i++)
        for (j = 0; j < DISPLAY_DIM; j++)
            imagen_actual_legible[i][j] = false;
}

/**
 * @brief Enciende un único LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 * @return int 0 en caso de una terminación correcta de la función, -1 si el
 * valor de alguna coordenada está fuera del rango [0, 4]
 */
void
display_enciende_LED(int x, int y)
{
    if (0 <= x && x < DISPLAY_DIM && 0 <= y && y < DISPLAY_DIM)
        return -1;

    /* Crea la imagen de forma que pueda ser procesada por las funciones de la
     * librería Microbian */
    image_set(x, y, imagen_actual_microbian);

    /* Actualiza el estado del display en el array que lo contiene en un formato
     * legible por el usuario */
    imagen_actual_legible[y][x] = true;

    /* Actualiza el valor de la variable compartida de la librería Microbian
     * que guarda el estado de los LEDs del display
     * (display_image@display.c[86]) */
    display_show(imagen_actual_microbian);

    return 0;
}

/**
 * @brief Enciende un único LED en el display.
 * 
 * @param c Las coordenadas del LED en el display
 * @return int 0 en caso de una terminación correcta de la función, -1 si el
 * valor de alguna coordenada está fuera del rango [0, 4]
 */
int
display_enciende_LED_coordenada(coordenada c)
{
    if (0 <= c.x && c.x < DISPLAY_DIM && 0 <= c.y && c.y < DISPLAY_DIM)
        return -1;

    display_enciende_LED(c.x, c.y);

    return 0;
}

/**
 * @brief Apaga un único LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 * @return int 0 en caso de una terminación correcta de la función, -1 si el
 * valor de alguna coordenada está fuera del rango [0, 4]
 */
int
display_apaga_LED(int x, int y)
{
    if (0 <= x && x < DISPLAY_DIM && 0 <= y && y < DISPLAY_DIM)
        return -1;

    image_clear(imagen_actual_microbian);
    imagen_actual_legible[y][x] = false;

    /*
     * La librería no implementa ninguna función que apague un LED. No obstante,
     * esto puede lograrse a partir de la función de encendido, creando una 
     * nueva imagen a partir del estado anterior a la modificación
     */ 
    int i, j;
    for (i = 0; i < DISPLAY_DIM; i++)
        for (j = 0; i < DISPLAY_DIM; j++)
            if (imagen_actual_legible[j][i] && i != x && j != y)
                image_set(i, j, imagen_actual_microbian);

    // TODO: mirar para hacerlo directamente sin iterar ni nada, interactuando directamente con el GPIO

    display_show(imagen_actual_microbian);

    return 0;
}

/**
 * @brief Apaga todos los LEDs en el display.
 * 
 */
void
display_limpia()
{
    /* Construye una imagen vacía y actualiza el estado del display */
    image_clear(imagen_actual_microbian);
    display_show(imagen_actual_microbian);
}

/**
 * @brief Muestra una imagen 2D utilizando los LEDs del display.
 * 
 * @param img El array que contiene los valores que determinarán el estado de
 * cada LED
 */
void
display_muestra_imagen(imagen_t img)
{
    int i, j;
    for (i = 0; i < DISPLAY_DIM; i++)
        for (j = 0; j < DISPLAY_DIM; j++)
            if (img[i][j])  // NOTE: no hago comprobación del valor en la imagen porque ya en la compilación del código debería cantar que has intentado guardar un valor no booleano en alguna posición
                display_enciende_LED(j, i);
}

/**
 * @brief Retorna el estado de un LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 * @return El estado del LED, encendido (true) o apagado (false), o -1 si el
 * valor de alguna coordenada está fuera del rango [0, 4] 
 */
bool
display_estado_LED(int x, int y)
{
    return ((0 <= x && x < DISPLAY_DIM &&
             0 <= y && y < DISPLAY_DIM) ? imagen_actual_legible[y][x] : -1);
}

// TODO: hacer que el linker script coja una función de nombre "main" como función principal, en lugar de init()

void
init(void)
{
    display_inicializa();
    imagen_t img_prueba = {{true,  true,  true,  true,  true},
                           {false, false, false, false, false},
                           {true,  true,  true,  true,  true},
                           {false, false, false, false, false},
                           {true,  true,  true,  true,  true}};
    display_muestra_imagen(img_prueba);
}
