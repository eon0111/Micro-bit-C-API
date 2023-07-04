/**
 * @file misc.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Alberga la función init
 * @version 1.0
 * @date jul-2023
 * 
 */

#include "ubit.h"

#define DISPLAY_DIM 5
#define TMP_STEP    0.25

/* Control del termómetro del NRF52833 */
#define TEMP_BASE       0x4000C000
#define TEMP_TASK_START 0x0
#define TEMP_DATARDY    0x100
#define TEMP_DATA       0x508
volatile int *temp_base = (volatile int *)TEMP_BASE;
volatile int *temp_task_start = (volatile int *)(TEMP_BASE + TEMP_TASK_START);
volatile int *temp_datardy = (volatile int *)(TEMP_BASE + TEMP_DATARDY);
volatile int *temp_data = (volatile int *)(TEMP_BASE + TEMP_DATA);

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
    serial_init();

    timer_init();

    /* NOTE: INTERNAL se refiere a la interfaz I2C que da soporte a los
     * dispositivos integrados en la placa y, EXTERNAL, se refiere a la interfaz
     * I2C que da soporte a los dispositivos que se conecten a los pines I2C de
     * la misma (33 (SCL) y 34 (SDA))  */
    i2c_init(I2C_INTERNAL);
    i2c_init(I2C_EXTERNAL);
    
    /* Inicialización de la matriz de LEDs */
    display_init();
    image_clear(imagen_actual_microbian);   /* NOTE: hay que dejar configurada la imagen inicialmente para que, cuando se hace en primer lugar una llamada a image_set() sobre la variable compartida, esta contenga ya todas las señales de control para LEDs tanto encendidos como apagados. De no hacerlo, el image_set() tan solo configuraría las señales de control para un único LED, y la imagen de Microbian estaría incompleta */

    /* Inicialización de los botones directamente a través de los registros del
     * GPIO, porque no hay una función de librería que lo haga explícitamente. */
    gpio_connect(BUTTON_A);
    gpio_connect(BUTTON_B);
    gpio_connect(TOUCH_BUTTON_LOGO);
    gpio_connect(TOUCH_BUTTON_0);
    gpio_connect(TOUCH_BUTTON_1);
    gpio_connect(TOUCH_BUTTON_2);

    /* Inicialización del zumbador piezoeléctrico */
    gpio_dir(BUZZER, 1);

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
    timer_delay(100);
    acelerometro_inicializa();
    brujula_inicializa();
}

/**
 * @brief Obtiene el valor de temperatura leído por el probe del microcontrolador.
 * 
 * @return int Una aproximación de la temperatura ambiental
 */
float
termometro_lectura()
{
    *temp_task_start = 1;
    while (!*temp_datardy);
    return *temp_data * TMP_STEP;
}
