/**
 * @file misc.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief TODO:
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"

/**
 * @brief Esta función es el punto de entrada al código del usuario. Dicho
 * código no podrá ejecutar correctamente si no es como parte de un proceso de
 * Microbian.
 * Se incluye como parte del código de la librería para que los alumnos no tengan
 * que declararla en sus códigos, y puedan programar de la forma más parecida
 * posible a como lo vienen haciendo hasta ahora en la asignatura de Introducción
 * al Software, con una función principal main() más las funciones que ellos
 * declaren y definan.
 * 
 */
void
init()
{
    //printf(""); // FIXME: No puedo hacer un printf desde init, y no es porque en startup.c no haya include ni de microbian.h ni de lib.h (ya he probado a poner los includes y recompilar la librería, y no va)
    microbit_inicializa_hardware();
    start("MAIN", main, 0, STACK);
}

/**
 * @brief Wrapper para todas las rutinas de inicialización de los dispositivos
 * hardware manejados por la librería Microbian. TODO: quitar -> "es mucho más
 * cómo inicializar todo el hardware con una sola llamada, que tener que estar
 * incializando cada dispositivo cada vez que vayas a usarlo"
 * 
 */
void
microbit_inicializa_hardware()
{
    /* NOTE: aún no sé bien si hay más rutinas de inicialización que reciban
     * parámetros pero, de haber más, esta función de inicialización podría
     * recibir una estructura que contenga todos los parámetros, comprobarlos,
     * y pasarlos a las rutinas de microbian. Entonces esta función retornaría
     * un valor en función de la terminación (error/correcta) */


    /* NOTE: La tarea de refresco del display requiere que el timer se encuentre
     * inicializado para poder realizar el refresco del display cada 15ms */
    timer_init();
    serial_init();
    /* TODO: mirar el manual de la arquitectura a ver cómo va el I2C, y qué es INTERNAL y EXTERNAL */
    i2c_init(I2C_INTERNAL);
    i2c_init(I2C_EXTERNAL);
    display_init();

    /* Inicialización de los botones directamente a través de los registros del
     * GPIO, porque no hay una función de librería que lo haga explícitamente */
    gpio_connect(BUTTON_A);
    gpio_connect(BUTTON_B);
}