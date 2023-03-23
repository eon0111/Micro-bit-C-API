/**
 * @file ubit.h
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 */

#include "../microbian/microbian.h"
#include "../microbian/hardware.h"
#include "../microbian/lib.h"
#include "sprites.h"

#define DISPLAY_DIM 5

/* display.c */
typedef int imagen_t[DISPLAY_DIM][DISPLAY_DIM];
typedef enum {INT_BAJA, INT_MEDIA, INT_ALTA} intensidad_t;
int display_inicializa(intensidad_t i);
int display_enciende_LED(int x, int y);
int display_apaga_LED(int x, int y);
int display_estado_LED(int x, int y);