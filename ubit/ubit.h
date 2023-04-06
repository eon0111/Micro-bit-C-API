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

#define DISPLAY_DIM 5

/* misc.c */
void main(int n);   // NOTE: aquí va la cabecera de la función principal
void microbit_inicializa_hardware();

/* display.c */
typedef enum {INT_BAJA, INT_MEDIA, INT_ALTA} intensidad_t;
typedef int imagen_t[DISPLAY_DIM][DISPLAY_DIM];
int display_cambia_intensidad(intensidad_t i);
int display_enciende_LED(int x, int y);
int display_apaga_LED(int x, int y);
int display_estado_LED(int x, int y);
int display_muestra_imagen(imagen_t img);
int display_muestra_secuencia(imagen_t seq[], int num_imgs, int delay_ms);
void display_limpia();

/* botones.c */
typedef enum {BOTON_A, BOTON_B} boton_t;
void boton_A_espera_pulsacion();
void boton_B_espera_pulsacion();
int boton_A_pulsado();
int boton_B_pulsado();

/* radio.c */
/* NOTE: casi que se pueden usar directamente las funciones de Microbian */

/* acelerometro.c */
void acel_init();
void acel_lectura(int *x, int *y, int *z);
