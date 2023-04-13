/**
 * @file acelerometro.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del acelerómetro, brújula
 * y termómetro, integrados en el chip LSM303AGR.
 * @version 0.1
 * @date TODO:
 * 
 */

#include "ubit.h"
// FIXME: #include <math.h>

#define ACC 0x19    /* La dirección del acelerómetro en el bus I2C -- NOTE: (PDF-accel@p39) */
#define MAG 0x1E    /* La dirección de la brújula en el bus I2C    -- NOTE: (PDF-accel@p39) */

/* NOTE: Direcciones -> PDF-accel@p43 */
#define ACC_CTRL_REG1 0x20  /* Registro de control del acelerómetro */
#define ACC_OUT_X     0x28  /* Valor de aceleración en el eje X */
#define ACC_OUT_Y     0x2A  /* Valor de aceleración en el eje Y */
#define ACC_OUT_Z     0x2C  /* Valor de aceleración en el eje Z */

#define MAG_CTRL_REG1 0x60  /* Registro de control del magnetómetro */
#define MAG_CTRL_REG2 0x61  /* Otro registro de control (activación cancelación de offset) */
#define MAG_OUT_X     0x68  /* Valor del campo magnético en el eje X */
#define MAG_OUT_Y     0x6A  /* Valor del campo magnético en el eje Y */
#define MAG_OUT_Z     0x6C  /* Valor del campo magnético en el eje Z */

/* NOTE: el sensor se configura para que trabaje en modo de "bajo consumo", es
 * decir, que proporcionará datos de aceleración con una resolución de 8 bits ->
 * PDF-accel@p27[tabla-14] */

void acelerometro_inicializa()
{
    /* NOTE:  0b01001111 -> 0100 = 50Hz; 1111 = habilita modo de bajo consumo y
     * activa los tres ejes X,Y y Z -> PDF-accel@p47 */
    i2c_write_reg(I2C_INTERNAL, ACC, ACC_CTRL_REG1, 0x4f);
}

/* FIXME: he probado con i2c_read_reg para sacar cada valor leyendo cada registro
 * por separado, pero sólo lee ceros */

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

int
acelerometro_lectura_x_2()
{
    signed char buf[6];
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
    /* 10011000 -> b8: habilita compensación de temperatura;
     *             b5: modo bajo consumo; b4-3: 50MHz;
     *             b2-1: modo de medición contínua
     * NOTE: PDF-accel@p61-62 */
    i2c_write_reg(I2C_INTERNAL, MAG, MAG_CTRL_REG1, 0x90);

    /* 00000010 -> b2: habilita la cancelación de offset
     * NOTE: PDF-accel@p23-63 */
    i2c_write_reg(I2C_INTERNAL, MAG, MAG_CTRL_REG2, 0x02);
}

int
brujula_lectura_x()
{
    //signed char buf[6];
    //i2c_read_bytes(I2C_INTERNAL, MAG, MAG_OUT_X|0x80, (byte *) buf, 6);
    return i2c_read_reg(I2C_INTERNAL, MAG, MAG_OUT_X);
    //return buf[1];
}

int
brujula_lectura_x_2()
{
    signed char buf[6];
    i2c_read_bytes(I2C_INTERNAL, MAG, MAG_OUT_X|0x80, (byte *) buf, 6);
    return buf[1];
}

int
brujula_lectura_y()
{
    //signed char buf[6];
    //i2c_read_bytes(I2C_INTERNAL, MAG, MAG_OUT_X|0x80, (byte *) buf, 6);
    return i2c_read_reg(I2C_INTERNAL, MAG, MAG_OUT_Y);
    //return buf[3];
}

int
brujula_lectura_z()
{
    //signed char buf[6];
    //i2c_read_bytes(I2C_INTERNAL, MAG, MAG_OUT_X|0x80, (byte *) buf, 6);
    return i2c_read_reg(I2C_INTERNAL, MAG, MAG_OUT_Z);
    //return buf[5];
}