/**
 * @file ubit.h
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)
 * @brief 
 * @version 0.1
 * @date TODO:
 * 
 */

#include <microbian.h>
#include <hardware.h>
#include <lib.h>

/* misc.c */
void main(int n);
void microbit_inicializa_hardware();
float termometro_lectura();

/* display.c */
#define DISPLAY_DIM 5
/* El conjunto de señales que controlan el estado de los LEDs en Microbian */
image imagen_actual_microbian;
typedef enum {INT_BAJA, INT_MEDIA, INT_ALTA} intensidad_t;
typedef enum {VEL_1, VEL_2, VEL_3} velocidad_texto_t;
typedef int imagen_t[DISPLAY_DIM][DISPLAY_DIM];
typedef struct { int x; int y; } coordenada_t;
int display_cambia_intensidad(intensidad_t i);
int display_enciende_LED(int x, int y);
int display_apaga_LED(int x, int y);
int display_muestra_imagen(imagen_t img);
int display_muestra_secuencia(imagen_t seq[], int n_elem_seq, int delay_ms);
void display_limpia();
int display_muestra_sprite(char *sprite_bin);
void char2codi(char c, char **codi);
void display_muestra_texto(char *str, velocidad_texto_t v);

/* botones.c */
typedef enum {BOTON_A, BOTON_B, BOTON_LOGO, BOTON_0, BOTON_1, BOTON_2} boton_t;
int boton_pulsado(boton_t b);
int boton_espera_pulsacion(boton_t b);

/* radio.c */
/* NOTE: casi que se pueden usar directamente las funciones de Microbian */
/* NOTE: la librería Microbian no implementa el driver para establecer comunicaciones
 * a través de Bluetooth, tan solo implementa el driver del protocolo de radio
 * de Nordic */

/* acelerometro.c */    /* NOTE: dejamos las funciones de lectura de datos en crudo porque podría ser interesante que los alumnos implementasen la conversión a datos reales */
void acelerometro_inicializa();
int acelerometro_lectura_x();
int acelerometro_lectura_y();
int acelerometro_lectura_z();
float inclinacion_eje_x();
float inclinacion_eje_y();
void brujula_inicializa();
int brujula_lectura_x();
int brujula_lectura_x2();
int brujula_lectura_y();
int brujula_lectura_z();

/* buzzer.c */
#define NEGRA       1000
#define CORCHEA     500
#define SEMICORCHEA 250
typedef enum {DO_3, RE_3, MI_3, FA_3, SOL_3, LA_3, SI_3, DO_4, RE_4, MI_4, FA_4,
              SOL_4, LA_4, SI_4, DO_5} nota_t;
void buzzer_reproduce_nota(nota_t n, int t_ms);
