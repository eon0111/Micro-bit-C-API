#include "../ubit/ubit.h"
#include <math.h>

/* NOTE: busca dispositivos mapeados en el bus I2C interno de la placa */
static void i2c_map(void)
{
    static char *hex = "0123456789abcdef";

    printf("I2C bus map:\n");
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
    for (int a = 0; a < 8; a++) {
        printf("%c0:", hex[a]);
        for (int b = 0; b < 16; b++) {
            int addr = (a<<4) + b;
            if (addr < 0x08 || addr >= 0x78)
                /* Reserved addresses */
                printf("   ");
            else {
                int status = i2c_probe(I2C_INTERNAL, addr);
                if (status == OK)
                    printf(" %c%c", hex[a], hex[b]);
                else
                    printf(" --");
            }
        }
        printf("\n");
    }
}

/* FIXME: estas funciones deberían estar en acelerometro.c, pero no encuentro la
 * manera de incluir la librería matemática en ubit.a */

/**
 * @brief Proporciona el valor de la inclinación en el eje X, en el rango
 * [-90, 90]. Con la placa posicionada de forma paralela al suelo
 * 
 * @return float La inclinación en el eje X
 */
float
inclinacion_eje_x() {
    float d = atan((float)acelerometro_lectura_z() /
                   (float)acelerometro_lectura_x()) * RAD_A_GRAD;
    return (d < 0) ? -90 - d : 90 - d;
    /* NOTE: atan() retorna un valor en radianes */
}

/**
 * @brief Proporciona el valor de la inclinación en el eje Y, en el rango
 * [-90, 90].
 * 
 * @return float La inclinación en el eje Y
 */
float
inclinacion_eje_y() {
    float d = atan((float)acelerometro_lectura_z() /
                   (float)acelerometro_lectura_y()) * RAD_A_GRAD;
    return (d < 0) ? -90 - d : 90 - d;
}

void
main(int n)
{
    //microbit_inicializa_hardware(); /* FIXME: no se puede hacer, porque salta error de hardware en la placa */
    acelerometro_inicializa();

    double gx, gy, gz;

    while (1) {
        timer_delay(100);

        /* NOTE: el rango de valores proporcionados por el sensor (en las
         * pruebas realizadas) va de -128 a 128, siendo 64 el valor obtenido en
         * reposo (en promedio), correspondiente con el valor de aceleración
         * sobre la superficie terrestre */

        gx = inclinacion_eje_x();
        gy = inclinacion_eje_y();

        display_enciende_LED(1, 1);

        printf("px=%d py=%d pz=%d\tx=%d y=%d\n", acelerometro_lectura_x(), acelerometro_lectura_y(), acelerometro_lectura_z(), (int)gx, (int)gy);
    }
}