/**
 * @file ubit.h
 * @author Noe Ruano Gutierrez (nrg916@alumnos.unican.es)   // FIXME: quitar cuando pongas el repo público (cambiar, limpiar repo y resubir)
 * @brief 
 * @version 0.1
 * @date TODO:
 * 
 */

#include "../microbian/microbian.h"
#include "../microbian/hardware.h"
#include "../microbian/lib.h"

/* misc.c */
void main(int n);   // NOTE: aquí va la cabecera de la función principal
void microbit_inicializa_hardware();

/* display.c */
#define DISPLAY_DIM 5
/* El conjunto de señales que controlan el estado de los LEDs en Microbian */
image imagen_actual_microbian;
typedef enum {INT_BAJA, INT_MEDIA, INT_ALTA} intensidad_t;
typedef int imagen_t[DISPLAY_DIM][DISPLAY_DIM];
typedef struct { int x; int y;} coordenada_t;
int display_cambia_intensidad(intensidad_t i);
int display_enciende_LED(int x, int y);
int display_apaga_LED(int x, int y);
int display_muestra_imagen(imagen_t img);
int display_muestra_secuencia(imagen_t seq[], int num_imgs, int delay_ms);
void display_limpia();

/* botones.c */
typedef enum {BOTON_A, BOTON_B, BOTON_LOGO, BOTON_0, BOTON_1, BOTON_2} boton_t;
int boton_pulsado(boton_t b);
int boton_espera_pulsacion(boton_t b);
int boton_A_pulsado();
int boton_B_pulsado();
int boton_tactil_pulsado();
int boton_tactil_0_pulsado();
int boton_tactil_1_pulsado();
int boton_tactil_2_pulsado();
void boton_A_espera_pulsacion();
void boton_B_espera_pulsacion();
void boton_tactil_espera_pulsacion();

/* radio.c */
/* NOTE: casi que se pueden usar directamente las funciones de Microbian */
/* TODO: probar Bluetooth */

/* acelerometro.c */
/* FIXME: por ahora las constantes están aqui para poder utilizarlas desde el
 * ejemplo. Lo suyo es que tanto estas constantes como las funciones que uso
 * en el ejemplo se pasen a acelerometro.c, cuando haya dado con la manera de
 * incluir la librería matemática en mi librería */
#define PI 3.14159265358979323846
#define RAD_A_GRAD 180 / PI /* = 360 / (2 * PI) */
void acelerometro_inicializa();
/* FIXME: realmente, creo que con las funciones de inclinación sería suficiente */
int acelerometro_lectura_x();
int acelerometro_lectura_y();
int acelerometro_lectura_z();
// FIXME: float inclinacion_eje_x();
// FIXME: float inclinacion_eje_y();
void brujula_inicializa();
int brujula_lectura_x();
int brujula_lectura_y();
int brujula_lectura_z();

/* buzzer.c */
#define NEGRA       1000
#define CORCHEA     500
#define SEMICORCHEA 250
typedef enum {DO_3, RE_3, MI_3, FA_3, SOL_3, LA_3, SI_3, DO_4, RE_4, MI_4, FA_4,
              SOL_4, LA_4, SI_4, DO_5} nota_t;
typedef struct { nota_t nota; int duracion_ms; } tono_t;
void buzzer_reproduce_nota(nota_t n, int t_ms);
