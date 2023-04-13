/**
 * @file misc.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief TODO:
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"

#define GRUPO_RADIO 1

/**
 * @brief Esta función es el punto de entrada al código del usuario. Dicho
 * código no podrá ejecutar correctamente si no es como parte de un proceso de
 * Microbian.
 * Se incluye como parte del código de la librería para que los alumnos no
 * tengan que declararla en sus códigos, y puedan programar de la forma más
 * parecida posible a como lo vienen haciendo hasta ahora en la asignatura de
 * Introducción al Software, con una función principal main() más las funciones
 * que ellos declaren y definan.
 * 
 */
void
init()
{
    /* NOTE: aún no sé bien si hay más rutinas de inicialización que reciban
     * parámetros pero, de haber más, esta función de inicialización podría
     * recibir una estructura que contenga todos los parámetros, comprobarlos,
     * y pasarlos a las rutinas de microbian. Entonces esta función retornaría
     * un valor en función de la terminación (error/correcta) */

    serial_init();

    /* NOTE: La tarea de refresco del display requiere que el timer se encuentre
     * inicializado para poder realizar el refresco del display cada 15ms */
    timer_init();

    /* NOTE: INTERNAL se refiere a la interfaz I2C que da soporte a los
     * dispositivos integrados en la placa y, EXTERNAL, se refiere a la interfaz
     * I2C que da soporte a los dispositivos que se conecten a los pines I2C de
     * la misma (33 (SCL) y 34 (SDA))  */
    i2c_init(I2C_INTERNAL);
    i2c_init(I2C_EXTERNAL);
    
    display_init();
    image_clear(imagen_actual_microbian);   /* NOTE: hay que dejar configurada la imagen inicialmente para que, cuando se hace en primer lugar una llamada a image_set() sobre la variable compartida, esta contenga ya todas las señales de control para LEDs tanto encendidos como apagados. De no hacerlo, el image_set() tan solo configuraría las señales de control para un único LED, y la imagen de Microbian estaría incompleta */

    /* Inicialización de los botones directamente a través de los registros del
     * GPIO, porque no hay una función de librería que lo haga explícitamente */
    gpio_connect(BUTTON_A);
    gpio_connect(BUTTON_B);

    radio_init();
    radio_group(GRUPO_RADIO);

    start("MAIN", main, 0, STACK);
}

/**
 * @brief Wrapper para todas las rutinas de inicialización de los dispositivos
 * hardware manejados por la librería Microbian que no pueden ser inicializados
 * desde fuera de un proceso de Microbian.
 * 
 */
void
microbit_inicializa_hardware()
{
    timer_delay(100);   /* NOTE: un pequeño delay para que le de tiempo a arrancar a la tarea de refresco del display y no nos de error al hacer operaciones sobre el display desde el proceso principal (main) */
    acelerometro_inicializa();    /* FIXME: por alguna razón que desconozco no se puede hacer la inicialización del acelerómetro desde fuera de un proceso de Microbian... */
    brujula_inicializa();
}
