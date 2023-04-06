/**
 * @file acelerometro.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del acelerómetro.
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"

#define ACC2 0x19               /* I2C address of mk1.5 accelerometer */
#define ACC2_CTRL_REG1 0x20     /* Control register */
#define ACC2_OUT 0x28           /* Acceleration data (different format) */

void acel_init()
{
    /* Set chip to 50Hz, 8 bit, Active */
    i2c_write_reg(I2C_INTERNAL, ACC2, ACC2_CTRL_REG1, 0x4f);
}

void acel_lectura(int *x, int *y, int *z)   // TODO: hacer otras con paso por valor (int, array, etc.)
{
    signed char buf[6];
    i2c_read_bytes(I2C_INTERNAL, ACC2, ACC2_OUT|0x80,(byte *) buf, 6);
    *x = buf[1]; *y = buf[3]; *z = -buf[5];
}