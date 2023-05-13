/**
 * @file sprites.h
 * @author Noé Ruano Gutiérrez (nrg916@alumnos.unican.es)
 * @brief Una pequeña librería de sprites que pueden ser mostrados en el display.
 * @version 0.1
 * @date 2023-03-22
 * 
 */

#include "ubit.h"

char *sprites[] = {
    "0010000100001000000000100",   /* 33_exclamacion_cierre.png     */
    "0101001010000000000000000",   /* 34_comillas.png               */
    "0101011111010101111101010",   /* 35_almohadilla.png            */
    "0111010100011100010101110",   /* 36_dolar.png                  */
    "1100111010001000101110011",   /* 37_porcentaje.png             */
    "0010001010001000101000101",   /* 38_ampersand.png              */
    "0010000100000000000000000",   /* 39_comilla_simple.png         */
    "0010001000010000100000100",   /* 40_parentesis_apertura.png    */
    "0010000010000100001000100",   /* 41_parentesis_cierre.png      */
    "1010101110111110111010101",   /* 42_asterisco.png              */
    "0000000100011100010000000",   /* 43_mas.png                    */
    "0000000000000000010000100",   /* 44_coma.png                   */
    "0000000000011100000000000",   /* 45_menos.png                  */
    "0000000000000000000000100",   /* 46_punto.png                  */
    "0001000010001000100001000",   /* 47_barra.png                  */
    "0010001010010100101000100",   /* 48_0.png                      */
    "0010001100001000010000100",   /* 49_1.png                      */
    "0111010001001100100011111",   /* 50_2.png                      */
    "0111000001001100000101110",   /* 51_3.png                      */
    "1000010010111110001000010",   /* 52_4.png                      */
    "1111110000011100000111110",   /* 53_5.png                      */
    "0111010000111101000101110",   /* 54_6.png                      */
    "1111100001000100010000100",   /* 55_7.png                      */
    "0111010001011101000101110",   /* 56_8.png                      */
    "0111010001011110000101110",   /* 57_9.png                      */
    "0000000100000000010000000",   /* 58_dos_puntos.png             */
    "0000000100000000010000100",   /* 59_punto_y_coma.png           */
    "0001000100010000010000010",   /* 60_menor_que.png              */
    "0000001110000000111000000",   /* 61_igual.png                  */
    "0100000100000100010001000",   /* 62_mayor_que.png              */
    "0110000010001000000000100",   /* 63_interrogacion_cierre.png   */
    "0111010001101101000001111",   /* 64_arroba.png                 */
    "0111010001100011111110001",   /* 65_A.png                      */
    "1111010001111101000111110",   /* 66_B.png                      */
    "0111010001100001000101110",   /* 67_C.png                      */
    "1111010001100011000111110",   /* 68_D.png                      */
    "1111110000111101000011111",   /* 69_E.png                      */
    "1111110000111001000010000",   /* 70_F.png                      */
    "0111110000101101000101111",   /* 71_G.png                      */
    "1111100100001000010011111",   /* 72_H.png                      */
    "0111000100001000010001110",   /* 73_I.png                      */
    "1111100010000101001001100",   /* 74_J.png                      */
    "1000110010111001001010001",   /* 75_K.png                      */
    "1000010000100001000011111",   /* 76_L.png                      */
    "1000111011101011000110001",   /* 77_M.png                      */
    "1000111001101011001110001",   /* 78_N.png                      */
    "0111010001100011000101110",   /* 79_O.png                      */
    "1111010001100011111010000",   /* 80_P.png                      */
    "0111010001100011001001101",   /* 81_Q.png                      */
    "1111010001100011111010001",   /* 82_R.png                      */
    "0111010000011100000101110",   /* 83_S.png                      */
    "1111100100001000010000100",   /* 84_T.png                      */
    "1000110001100011000101110",   /* 85_U.png                      */
    "1000110001010100101000100",   /* 86_V.png                      */
    "1000110001100011010101010",   /* 87_W.png                      */
    "1000101010001000101010001",   /* 88_X.png                      */
    "1000110001111110000101110",   /* 89_Y.png                      */
    "1111100010001000100011111",   /* 90_Z.png                      */
    "0110001000010000100001100",   /* 91_corchete_apertura.png      */
    "0100001000001000001000010",   /* 92_barra_invertida.png        */
    "0011000010000100001000110",   /* 93_corchete_cierre.png        */
    "0010001010000000000000000",   /* 94_acento_circunflejo.png     */
    "0000000000000000000001110"    /* 95_barra_baja.png             */
};

/* NOTE:
 * Opción 1:
 *      Almacenar los sprites como strings -> cada vez que se quiera mostrar un
 *      sprite, se coge el string correspondiente de este fichero de cabecera y
 *      y se convierte en el momento a su equivalente en "formato" imagen_t. Nos
 *      ahorramos tener almacenados 30 y pico arrays bidimensionales de los que
 *      no sabemos cuántos se emplearán en el código del usuario, y la conversión
 *      tampoco es que vaya a ser algo muy costoso en tiempo ni recursos
 *
 * Opción 2:
 *      Almacenar los sprites directamente como elementos del tipo imagen_t, con
 *      el desperdicio de memoria que ello puede conllevar.
 */
