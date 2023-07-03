/**
 * @file display.c
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del display de 5x5 LEDs.
 * @version 1.0
 * @date jul-2023
 * 
 */

#include "ubit.h"
#include "sprites.h"

/**
 * @brief Wrapper para la rutina de inicialización del proceso de refresco
 * del display, proporcionada por la librería Microbian.
 * @return int -1 si el valor de intensidad no es apropiado, 0 en caso de una
 * terminación correcta 
 */
int
display_cambia_intensidad(intensidad_t intensidad)
{
    if (intensidad < INT_BAJA || intensidad > INT_ALTA) return -1;

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

    /* Actualiza el valor de la variable compartida de la librería Microbian */
    display_show(imagen_actual_microbian);

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

    image_clear_led(x, y, imagen_actual_microbian);
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

    for (i = 0; i < DISPLAY_DIM; i++)
        for (j = 0; j < DISPLAY_DIM; j++)
            if (img[i][j])
                image_set(j, DISPLAY_DIM-1-i, imagen_actual_microbian);

    display_show(imagen_actual_microbian);

    return 0;
}

/**
 * @brief Muestra una secuencia de imágenes en el display.
 * 
 * @param seq El array que contiene las imágenes
 * @param n_elem_seq El número de imágenes
 * @param delay_ms El delay entre cada imagen
 * @return int -1 si el delay indicado no es válido, o 0 en caso de una
 * terminación correcta
 */
int
display_muestra_secuencia(imagen_t seq[], int n_elem_seq, int delay_ms)
{
    if (delay_ms < 0) return -1;

    int i;
    for (i = 0; i < n_elem_seq; i++)
    {
        display_muestra_imagen(seq[i]);
        timer_delay(delay_ms);
    }

    return 0;
}

/**
 * @brief Retorna la longitud de un string.
 * 
 * @param str El string
 * @return int La longitud del string
 */
static int
strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

/**
 * @brief Muestra en el display el sprite correspondiente a la codificación
 * indicada.
 * 
 * @param sprite_bin La codificación del sprite
 * @return int -1 si la codificación del string no tiene una longitud adecuada
 * (1 carácter por píxel = 25 píxeles) o si alguno de los carácteres de la cadena
 * es distinto de '0' o '1'. Retorna 0 en caso de una terminación correcta
 */
int
display_muestra_sprite(char *sprite_bin)
{
    if (strlen(sprite_bin) != DISPLAY_DIM * DISPLAY_DIM) return -1;

    imagen_t tmp;
    int i, j;
    for (i = 0; i < DISPLAY_DIM; i++)
        for (j = 0; j < DISPLAY_DIM; j++)
            if (sprite_bin[i * DISPLAY_DIM + j] != '1' && sprite_bin[i * DISPLAY_DIM + j] != '0')
                return -1;
            else
                tmp[i][j] = (sprite_bin[i * DISPLAY_DIM + j] == '1') ? 1 : 0;

    display_muestra_imagen(tmp);

    return 0;
}

/**
 * @brief Obtiene la codificación de un carácter. Si la codificación del
 * carácter no se encuentra en la librería de sprites, esta se sustituye por la
 * codificación del signo de cierre de interrogación.
 * 
 * @param c El carácter cuya codificación quiere obtenerse
 * @param codi El string donde depositar la codificación del carácter
 */
void
display_char2codi(char c, char **codi)
{
    if (c < '!' || c > '_')
        *codi = sprites['?' - 33];
    else
        *codi = sprites[(int)c - 33];
}

#define abs(x) (x < 0) ? -x : x

/**
 * @brief Muestra un texto en el display LED de la placa con una animación de
 * deslizamiento hacia la izquierda.
 * 
 * @param str El texto a mostrar
 * @param v La velocidad con la que deberá deslizarse el texto
 */
void
display_muestra_texto(char *str, velocidad_texto_t vel)
{
    int i, j, k, m, longitud_str = strlen(str);

    char *codificacion_1 = "";
    char *codificacion_2 = "";

    imagen_t imagen_tmp_1;
    imagen_t imagen_tmp_2;
    imagen_t imagen_compuesta;

    display_char2codi(str[0], &codificacion_1);

    /* Mostramos cada uno de los carácteres de la cadena */
    for (k = 0; k < longitud_str - 1; k++)
    {
        /* Obtenemos la codificación "binaria" del primer caracter en este ciclo,
         * y el inmediatamente posterior */
        display_char2codi(str[k + 1], &codificacion_2);

        /* Convertimos las codificaciones en sus respectivas imágenes */
        for (i = 0; i < DISPLAY_DIM; i++)
            for (j = 0; j < DISPLAY_DIM; j++)
            {
                imagen_tmp_1[i][j] = (codificacion_1[i * DISPLAY_DIM + j] == '1') ? 1 : 0;
                imagen_tmp_2[i][j] = (codificacion_2[i * DISPLAY_DIM + j] == '1') ? 1 : 0;
            }

        /* Mostramos los carácteres con una animación de deslizamiento de dcha. a izda. */
        for (m = 0; m <= DISPLAY_DIM + 1; m++)
        {
            for (i = 0; i < DISPLAY_DIM; i++)
            {
                for (j = 0; j < DISPLAY_DIM; j++)
                {
                    imagen_compuesta[i][j] = (m + j < DISPLAY_DIM) ? imagen_tmp_1[i][j + m] : 
                                            ((m + j == DISPLAY_DIM) ? 0 : imagen_tmp_2[i][abs((DISPLAY_DIM - (j - 1 + m)))]);
                    display_muestra_imagen(imagen_compuesta);
                }
            }
            if (m < DISPLAY_DIM + 1) timer_delay(1000 / (10 * vel + 1));
        }

        display_char2codi(str[k + 1], &codificacion_1);
    }
}
