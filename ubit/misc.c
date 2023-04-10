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
    microbit_inicializa_hardware();
    start("MAIN", main, 0, STACK);
}

/**
 * @brief Wrapper para todas las rutinas de inicialización de los dispositivos
 * hardware manejados por la librería Microbian. TODO: quitar -> "es mucho más
 * cómo inicializar todo el hardware con una sola llamada, que tener que estar
 * incializando cada dispositivo cada vez que vayas a usarlo"
 * 
 * FIXME: me da que no va a quedar más remedio que hacer que llamen a las 
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

    /* Inicialización de los botones directamente a través de los registros del
     * GPIO, porque no hay una función de librería que lo haga explícitamente */
    gpio_connect(BUTTON_A);
    gpio_connect(BUTTON_B);

    radio_init();
    radio_group(GRUPO_RADIO);

    //acelerometro_inicializa();    /* FIXME: por alguna razón que desconozco no se puede hacer la inicialización del acelerómetro desde fuera de un proceso de Microbian... */
}
