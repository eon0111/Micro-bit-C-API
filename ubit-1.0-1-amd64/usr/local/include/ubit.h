/**
 * @file ubit.h
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief Fichero de cabecera de la librería Ubit
 * @version 1.0
 * @date jul-2023
 * 
 */

#include "microbian.h"
#include "hardware.h"
#include "lib.h"

/* misc.c */
void main(int n);
void microbit_inicializa_hardware();
float termometro_lectura();

/* display.c */
#define DISPLAY_DIM 5
image imagen_actual_microbian;
typedef struct { int x; int y; } coordenada_t;
typedef enum {INT_BAJA, INT_MEDIA, INT_ALTA} intensidad_t;
typedef enum {LENTO, MEDIO, RAPIDO} velocidad_texto_t;
typedef int imagen_t[DISPLAY_DIM][DISPLAY_DIM];
int display_cambia_intensidad(intensidad_t i);
int display_enciende_LED(int x, int y);
int display_apaga_LED(int x, int y);
int display_muestra_imagen(imagen_t img);
int display_muestra_secuencia(imagen_t seq[], int n_elem_seq, int delay_ms);
void display_limpia();
int display_muestra_sprite(char *sprite_bin);
void display_char2codi(char c, char **codi);
void display_muestra_texto(char *str, velocidad_texto_t v);

/* botones.c */
typedef enum {BOTON_A, BOTON_B, BOTON_LOGO, BOTON_0, BOTON_1, BOTON_2} boton_t;
int boton_pulsado(boton_t b);
int boton_espera_pulsacion(boton_t b);

/* acelerometro.c */
void acelerometro_inicializa();
int acelerometro_lectura_x();
int acelerometro_lectura_y();
int acelerometro_lectura_z();
float acelerometro_inclinacion_eje_x();
float acelerometro_inclinacion_eje_y();
void brujula_inicializa();
int brujula_lectura_x();
int brujula_lectura_x2();
int brujula_lectura_y();
int brujula_lectura_z();

/* buzzer.c */
#define NEGRA       1000
#define CORCHEA     500
#define SEMICORCHEA 250
typedef enum {DO_4, RE_4, MI_4, FA_4, SOL_4, LA_4, SI_4, DO_5, RE_5, MI_5, FA_5,
              SOL_5, LA_5, SI_5, DO_6} nota_t;
void buzzer_reproduce_nota(nota_t n, int t_ms);
