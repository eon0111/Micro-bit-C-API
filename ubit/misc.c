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

/* NOTE: Según el manual de la arquitectura, el valor leído del registro de
 * datos del sensor de temperatura indica el valor de dicha temperatura, pero
 * expresado en número de incrementos de 0.25 ºC (pdfNRF@p427) */
#define TMP_STEP    0.25

/* Control del termómetro del NRF52833 */
#define TEMP_BASE       0x4000C000  /* NOTE: pdfNRF@p425 */
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

    /* NOTE: La tarea de refresco del display requiere que el timer se encuentre
     * inicializado para poder realizar el refresco del display cada 15ms */
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
     * GPIO, porque no hay una función de librería que lo haga explícitamente.
     * NOTE: Se configuran como entrada en el registro de configuración del GPIO */
    gpio_connect(BUTTON_A);
    gpio_connect(BUTTON_B);
    gpio_connect(TOUCH_BUTTON_LOGO);
    gpio_connect(TOUCH_BUTTON_0);
    gpio_connect(TOUCH_BUTTON_1);
    gpio_connect(TOUCH_BUTTON_2);

    /* Inicialización del zumbador piezoeléctrico */
    gpio_dir(BUZZER, 1);

    /* NOTE: la librería Microbian contiene el driver para operar con el protocolo
     * de radio de Nordic, no Bluetooth (ni BLE) */
    radio_init();
    radio_group(GRUPO_RADIO);   /* NOTE: un grupo es lo mismo que un canal */

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

/**
 * @brief 
 * 
 * @return int 
 */
float
termometro_lectura()
{
    *temp_task_start = 1;
    while (!*temp_datardy);
    return *temp_data * TMP_STEP;

    /* NOTE: he probado con código oficial de Micro:bit y se muestra el mismo
     * valor de temperatura (+2 ºC aprox.), así que deduzco que lo anómalo del
     * valor depositado en el registro de datos se deba a factores externos a la
     * programación del dispositivo, quizá una falta (enorme) de precisión en
     * las lecturas, un error de hardware, etc. */
}
