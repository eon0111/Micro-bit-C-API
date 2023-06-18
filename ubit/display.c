/**
 * @file display.c
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del display de 5x5 LEDs.
 * @version 0.1
 * @date TODO:
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
    /* NOTE: podría haber hecho una configuración inicial del nivel de intensidad
     * empleando el argumento de la función display_init(), pero preferimos no
     * tocar la librería (copyright??) */

    if (intensidad < INT_BAJA || intensidad > INT_ALTA) return -1;

    /* NOTE: podría emplear sus constantes (GPIO_DRIVE_X@hardware.c), pero 
     * tendría que hacer un mapeo de la intensidad (enumerado) a cada constante,
     * y este encima sería directo porque, por ejemplo, intensidad "INT_BAJA"
     * sería el equivalente de GPIO_DRIVE_S0S1 */
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

    /* NOTE: Actualiza el valor de la variable compartida de la librería Microbian
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
display_enciende_LED_coordenada(coordenada_t c)
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

    /* NOTE: no tiene sentido apagar un LED directamente tocando el GPIO, porque
     * la tarea de refresco te lo va a volver a encender si ese LED se encuentra
     * encendido en la imagen que lee el proceso. Hay que tocar la imagen,
     * generando en la posición a apagar las señales de control necesarias para
     * ello */

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

    /* NOTE: no tiene sentido llamar en cada iteración a enciende_LED(). Esto
     * generaría una escritura en el estado del display de Microbian por
     * iteración, a demás de las escrituras sobre la imagen que se va formando
     * en el estado de mi librería, cuando tener tan solo estas últimas, y una
     * única escritura de las primeras */

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
            if (sprite_bin[i] != '1' || sprite_bin[i] != '0')
                return -1;
            else
                tmp[i][j] = (sprite_bin[i] == '1') ? 1 : 0;

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
char2codi(char c, char **codi)
{
    if (c < '!' || c > '_')
        *codi = sprites['?' - 33];
    else
        *codi = sprites[(int)c - 33];
}

#define abs(x) (x < 0) ? -x : x

// TODO: candidato a práctica también
void
display_muestra_texto(char *str, velocidad_texto_t v)
{
    int i, j, k, m, longitud_str = strlen(str);

    char *codificacion_1 = "";
    char *codificacion_2 = "";

    imagen_t imagen_tmp_1;
    imagen_t imagen_tmp_2;
    imagen_t imagen_compuesta;

    char2codi(str[0], &codificacion_1);

    /* Mostramos cada uno de los carácteres de la cadena */
    for (k = 0; k < longitud_str - 1; k++)
    {
        /* Obtenemos la codificación "binaria" del primer caracter en este ciclo,
         * y el inmediatamente posterior */
        char2codi(str[k + 1], &codificacion_2);

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
            timer_delay(1000);
        }

        char2codi(str[k + 1], &codificacion_1);
    }
}
