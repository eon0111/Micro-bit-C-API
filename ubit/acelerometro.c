/**
 * @file acelerometro.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del acelerómetro.
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"

#define ACC 0x19    /* La dirección del acelerómetro en el bus I2C - NOTE: (PDF-accel@p39) */
#define MAG 0x1E    /* La dirección de la brújula en el bus I2C - NOTE: (PDF-accel@p39) */

/* NOTE: Direcciones -> PDF-accel@p43 */
#define ACC_CTRL_REG1 0x20  /* Registro de control del acelerómetro */
#define ACC_OUT_X     0x28  /* Registro donde se deposita el valor de aceleración en el eje X */
#define ACC_OUT_Y     0x2A  /* Registro donde se deposita el valor de aceleración en el eje Y */
#define ACC_OUT_Z     0x2C  /* Registro donde se deposita el valor de aceleración en el eje Z */

#define MAG_CTRL_REG1 0x60  /* Registro de control del magnetómetro */
#define MAG_OUT_X     0x68  /* Registro donde se deposita el valor del campo magnético en el eje X */
#define MAG_OUT_Y     0x6A  /* Registro donde se deposita el valor del campo magnético en el eje Y */
#define MAG_OUT_Z     0x6C  /* Registro donde se deposita el valor del campo magnético en el eje Z */

/* NOTE: el sensor se configura para que trabaje en modo de "bajo consumo", es
 * decir, que proporcionará datos de aceleración con una resolución de 8 bits -> PDF-accel@p27[tabla-14] */

void acelerometro_inicializa()
{
    i2c_write_reg(I2C_INTERNAL, ACC, ACC_CTRL_REG1, 0x4f);  /* NOTE:  0b01001111 -> 0100 = 50Hz; 1111 = habilita modo de bajo consumo y activa los tres ejes X,Y y Z -> PDF-accel@p47 */
}

/* FIXME: he probado con i2c_read_reg para sacar cada valor leyendo cada registro por separado, pero sólo lee ceros */

/**
 * @brief Obtiene el valor de la aceleración en el eje X, codificado como un
 * entero en el rango [-128, 128].
 * 
 * @return int El valor de la aceleración en el eje X
 */
int
acelerometro_lectura_x()
{
    signed char buf[6];
    /* FIXME: no entiendo el por qué de hacer que el parámetro cmd sea
     * 0x28 | 0x80 = 0xA8. Yo entiendo que en cmd tiene que ir la dirección del
     * registro que quieres leer, seguida del bit de lectura/escritura, no?? */
    i2c_read_bytes(I2C_INTERNAL, ACC, ACC_OUT_X|0x80, (byte *) buf, 6);
    return buf[1];
}

/**
 * @brief Obtiene el valor de la aceleración en el eje Y, codificado como un
 * entero en el rango [-128, 128].
 * 
 * @return int El valor de la aceleración en el eje Y
 */
int
acelerometro_lectura_y()
{
    signed char buf[6];
    i2c_read_bytes(I2C_INTERNAL, ACC, ACC_OUT_X|0x80, (byte *) buf, 6);
    return buf[3];
}

/**
 * @brief Obtiene el valor de la aceleración en el eje Z, codificado como un
 * entero en el rango [-128, 128].
 * 
 * @return int El valor de la aceleración en el eje Z
 */
int
acelerometro_lectura_z()
{
    signed char buf[6];
    i2c_read_bytes(I2C_INTERNAL, ACC, ACC_OUT_X|0x80, (byte *) buf, 6);
    return buf[5];
}

void
brujula_inicializa()
{
    /* NOTE: se habilita el modo de lectura única (PDF-accel@p22) en lugar de
     * hacer muestreo periódico.
     * NOTE: 0x70 -> PDF-accel@p61 */
    i2c_write_reg(I2C_INTERNAL, MAG, MAG_CTRL_REG1, 0x70);
}

int
brujula_lectura_x()
{
    signed char buf[6];
    i2c_read_bytes(I2C_INTERNAL, ACC, MAG_OUT_X|0x80, (byte *) buf, 6);
    return buf[1];
}