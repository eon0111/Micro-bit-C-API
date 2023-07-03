/**
 * @file 01_display_cambia_intensidad.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba los distintos niveles de intensidad en los LEDs de la placa
 * @version 1.0
 * @date jul-2023
 * 
 */

#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();

    imagen_t img = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    display_muestra_imagen(img);

    printf("test_display: display_cambia_intensidad -> INT_BAJA\n");
    printf("%s\n", (!display_cambia_intensidad(INT_BAJA)) ? "CORRECTO" : "FALLA");
    timer_delay(1000);
    printf("test_display: display_cambia_intensidad -> INT_MEDIA\n");
    printf("%s\n", (!display_cambia_intensidad(INT_MEDIA)) ? "CORRECTO" : "FALLA");
    timer_delay(1000);
    printf("test_display: display_cambia_intensidad -> INT_ALTA\n");
    printf("%s\n", (!display_cambia_intensidad(INT_ALTA)) ? "CORRECTO" : "FALLA");
    timer_delay(1000);
    printf("test_display: display_cambia_intensidad -> intensidad incorrecta\n");
    printf("%s\n", (!display_cambia_intensidad(-1)) ? "FALLA" : "CORRECTO");
    timer_delay(1000);
}
