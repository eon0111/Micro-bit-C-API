/**
 * @file acelerometro.c
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Conjunto de rutinas para el manejo del acelerómetro, integrado en el
 * chip LSM303AGR.
 * @version 1.0
 * @date jul-2023
 * 
 */

#include "ubit.h"

/**
 * @brief La dirección base del acelerómetro en el bus I2C.
 * 
 */
#define ACC 0x19
#define MAG 0x1E

/**
 * @brief La dirección del registro de control del acelerómetro.
 * 
 */
#define ACC_CTRL_REG1   0x20

/**
 * @brief La dirección del registro de datos donde el acelerómetro deposita las
 * lecturas del valor de aceleración en el eje X.
 * 
 */
#define ACC_OUT_X       0x29

/**
 * @brief La dirección del registro de datos donde el acelerómetro deposita las
 * lecturas del valor de aceleración en el eje X.
 * 
 */
#define ACC_OUT_Y       0x2B

/**
 * @brief La dirección del registro de datos donde el acelerómetro deposita las
 * lecturas del valor de aceleración en el eje X.
 * 
 */
#define ACC_OUT_Z       0x2D

#define MAG_CTRL_REG1   0x60    /* Registro de control del magnetómetro */
#define MAG_CTRL_REG2   0x61    /* Otro registro de control (activación cancelación de offset) */
#define MAG_OUT_X       0x68    /* Valor del campo magnético en el eje X */
#define MAG_OUT_Y       0x6A    /* Valor del campo magnético en el eje Y */
#define MAG_OUT_Z       0x6C    /* Valor del campo magnético en el eje Z */

/* Constantes para el cálculo del valor de la inclinación en grados */
#define PI 3.14159265358979323846
#define RAD_A_GRAD 180 / PI /* = 360 / (2 * PI) */
#define abs(x) (x < 0) ? -x : x

/**
 * @brief Configura el acelerómetro para que comience a realizar mediciones de
 * la aceleración en los ejes X, Y y Z.
 * 
 */
void acelerometro_inicializa()
{
    i2c_write_reg(I2C_INTERNAL, ACC, ACC_CTRL_REG1, 0x4f);
}

/**
 * @brief Obtiene el valor de la aceleración en el eje X, codificado como un
 * entero en el rango [-128, 128].
 * 
 * @return int El valor de la aceleración en el eje X
 */
int
acelerometro_lectura_x()
{
    signed char tmp;
    i2c_read_bytes(I2C_INTERNAL, ACC, ACC_OUT_X|0x80, (byte *) &tmp, 1);
    return tmp;
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
    signed char tmp;
    i2c_read_bytes(I2C_INTERNAL, ACC, ACC_OUT_Y|0x80, (byte *) &tmp, 1);
    return tmp;
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
    signed char tmp;
    i2c_read_bytes(I2C_INTERNAL, ACC, ACC_OUT_Z|0x80, (byte *) &tmp, 1);
    return tmp;
}

void
brujula_inicializa()
{
    /* 10011000 -> b8: habilita compensación de temperatura;
     *             b5: modo bajo consumo;
     *             b4-3: 50MHz;
     *             b2-1: modo de medición contínua
     * NOTE: PDF-accel@p61-62 */
    i2c_write_reg(I2C_INTERNAL, MAG, MAG_CTRL_REG1, 0x88);

    /* 00000010 -> b2: habilita la cancelación de offset
     * NOTE: PDF-accel@p23-63 */
    i2c_write_reg(I2C_INTERNAL, MAG, MAG_CTRL_REG2, 0x02);
}

int
brujula_lectura_x()
{
    return i2c_read_reg(I2C_INTERNAL, MAG, MAG_OUT_X);
}

int
brujula_lectura_y()
{
    return i2c_read_reg(I2C_INTERNAL, MAG, MAG_OUT_Y);
}

int
brujula_lectura_z()
{
    return i2c_read_reg(I2C_INTERNAL, MAG, MAG_OUT_Z);
}

/**
 * @brief Retorna la potencia 'e' de un número 'b'.
 * 
 * @param b la base
 * @param e el exponente
 * @return float b elevado a e
 */
static float
pow(float b, float e)
{
    int n, t = abs(e);
    float r = 1.0;
    for (n = 0; n < t; n++)
        r = r * b;
    return (e > 0) ? r : 1 / r;
}

/**
 * @brief Calcula el arcotangente de un valor numérico en base a la serie de
 * Taylor que aproxima dicha función. Con 10 términos de la serie se consigue
 * una precisión aceptable.
 * 
 * @param x el valor cuyo arcotangente quiere conocerse
 * @return float el arcotangente (en radianes) del valor indicado
 */
static float
atan(float x)
{
    int n;
    float x2 = abs(x), r = 0.0, c = (x2 < 1) ? 1 : -1, c2 = (x < 0) ? -1 : 1;

    for (n = 0; n < 10; n++)
        r += pow(-1,n) * pow(x2,c*(1+2*n)) / (1+2*n);

    return (x2 < 1) ? c2 * r : c2 * ((PI / 2) - r);
}

/**
 * @brief Proporciona el valor de la inclinación en el eje X, en el rango
 * [-90, 90].
 * 
 * @return float La inclinación en el eje X
 */
float
acelerometro_inclinacion_eje_x() {
    float d = atan((float)acelerometro_lectura_z() /
                   (float)acelerometro_lectura_x()) * RAD_A_GRAD;
    return (d < 0) ? -90 - d : 90 - d;
}

/**
 * @brief Proporciona el valor de la inclinación en el eje Y, en el rango
 * [-90, 90].
 * 
 * @return float La inclinación en el eje Y
 */
float
acelerometro_inclinacion_eje_y() {
    float d = atan((float)acelerometro_lectura_z() /
                   (float)acelerometro_lectura_y()) * RAD_A_GRAD;
    return (d < 0) ? -90 - d : 90 - d;
}
