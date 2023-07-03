/**
 * @file 01_acelerometro_inclinacion_lectura.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba las funciones de lectura de las mediciones de aceleración y 
 * cálculo de la inclinación de la placa
 * @version 1.0
 * @date jul-2023
 * 
 */

#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();

    double gx, gy, gz;

    while (1) {
        timer_delay(100);

        /* El rango de valores proporcionados por el sensor (en las
         * pruebas realizadas) va de -128 a 128, siendo 64 el valor obtenido en
         * reposo (en promedio), correspondiente con el valor de aceleración
         * sobre la superficie terrestre */

        gx = acelerometro_inclinacion_eje_x();
        gy = acelerometro_inclinacion_eje_y();

        printf("px=%d py=%d pz=%d\tx=%d y=%d\n", acelerometro_lectura_x(),
            acelerometro_lectura_y(), acelerometro_lectura_z(), (int)gx, (int)gy);
    }
}