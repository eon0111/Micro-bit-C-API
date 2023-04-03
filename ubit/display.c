/**
 * @file display.c
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del display de 5x5 LEDs.
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"

/* El conjunto de señales que controlan el estado de los LEDs en Microbian */
image imagen_actual_microbian;

/* El conjunto de valores que indican el estado de los LEDs de forma comprensible
 * para el usuario */
int imagen_actual_legible[DISPLAY_DIM][DISPLAY_DIM] = {};

typedef struct {
    int x;
    int y
} coordenada;

/**
 * @brief Wrapper para la rutina de inicialización del proceso de refresco
 * del display, proporcionada por la librería Microbian.
 * @return int -1 si el valor de intensidad no es apropiado, 0 en caso de una
 * terminación correcta 
 */
int
display_cambia_intensidad(intensidad_t intensidad)
{
    /* NOTE: podría haber hecho una configuración inicial del nivel de intensidad
     * empleando el argumento de la función display_init(), pero preferimos no
     * tocar la librería (copyright??) */

    if (intensidad < INT_BAJA || intensidad > INT_ALTA) return -1;

    /* NOTE: podría emplear sus constantes (GPIO_DRIVE_X@hardware.c), pero 
     * tendría que hacer un mapeo de la intensidad (enumerado) a cada constante,
     * y este encima sería directo porque, por ejemplo, intensidad "INT_BAJA" sería
     * el equivalente de GPIO_DRIVE_S0S1 */
    gpio_drive(ROW1, intensidad);
    gpio_drive(ROW2, intensidad);
    gpio_drive(ROW3, intensidad);
    gpio_drive(ROW4, intensidad);
    gpio_drive(ROW5, intensidad);

    return 0;
}

/**
 * @brief Enciende un único LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 * @return int 0 en caso de una terminación correcta de la función, -1 si el
 * valor de alguna coordenada está fuera del rango [0, 4]
 */
int
display_enciende_LED(int x, int y)
{
    if (x < 0 || x >= DISPLAY_DIM || y < 0 || y >= DISPLAY_DIM) return -1;

    /* Elabora el conjunto de señales que hacen que se encienda el LED */
    image_set(x, y, imagen_actual_microbian);

    /* Actualiza el estado "legible" del display */
    imagen_actual_legible[x][y] = 1;

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
    if (c.x < 0 || c.x >= DISPLAY_DIM || c.y < 0 || c.y >= DISPLAY_DIM) return -1;

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
    if (x < 0 || x >= DISPLAY_DIM || y < 0 || y >= DISPLAY_DIM) return -1;

    image_clear(imagen_actual_microbian);
    imagen_actual_legible[x][y] = 0;

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
 * @return int 0 si la imagen pudo mostrarse correctamente, o 1 si
 * alguno de los valores de la imagen no es válido
 */
int
display_muestra_imagen(imagen_t img)
{
    int i, j;

    display_limpia();

    /* NOTE: no tiene sentido llamar en cada iteración a enciende_LED(). Esto
     * generaría una escritura en el estado del display de Microbian por
     * iteración, a demás de las escrituras sobre la imagen que se va formando
     * en el estado de mi librería, cuando tener tan solo estas últimas, y una
     * única escritura de las primeras */

    for (i = 0; i < DISPLAY_DIM; i++)
        for (j = 0; j < DISPLAY_DIM; j++)
            if (img[i][j])
                image_set(j, DISPLAY_DIM-i-1, imagen_actual_microbian);

    display_show(imagen_actual_microbian);

    return 0;
}

/**
 * @brief Muestra una secuencia de imágenes en el display.
 * 
 * @param seq El array que contiene las imágenes
 * @param num_imgs El número de imágenes
 * @param delay_ms El delay entre cada imagen
 * @return int -1 si el delay indicado no es válido, o 0 en caso de una
 * terminación correcta
 */
int
display_muestra_secuencia(imagen_t seq[], int num_imgs, int delay_ms)
{
    if (delay_ms < 0) return -1;

    int i;
    for (i = 0; i < num_imgs; i++)
    {
        display_muestra_imagen(seq[i]);
        timer_delay(delay_ms);
    }

    return 0;
}

/**
 * @brief Retorna el estado de un LED en el display.
 * 
 * @param x La coordenada en el eje de abscisas dentro del display
 * @param y La coordenada en el eje de ordenadas dentro del display
 * @return El estado del LED, encendido (1) o apagado (0), o -1 si el
 * valor de alguna coordenada está fuera del rango [0, 4] 
 */
int
display_estado_LED(int x, int y)
{
    if (0 <= x && x < DISPLAY_DIM && 0 <= y && y < DISPLAY_DIM)
        return imagen_actual_legible[y][x];
    return -1;
}

/* NOTE: mirando en la librería ([148-186]@microbian.c), me doy cuenta de que el SO tan sólo admite 3 procesos en cualquier estado */