/**
 * @file ubit.h
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 */

#include <stdbool.h>

#define DISPLAY_DIM 5

typedef bool imagen_t[DISPLAY_DIM][DISPLAY_DIM];

/* display.c */
void display_inicializa();
void display_enciende_LED(int x, int y);
int display_apaga_LED(int x, int y);
bool display_estado_LED(int x, int y);