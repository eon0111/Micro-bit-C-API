/**
 * @file 03_display_muestra_limpia_imagen.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba la presentación de imágenes en el display
 * @version 1.0
 * @date jul-2023
 * 
 */

#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();
    display_cambia_intensidad(INT_BAJA);
 
    while (1)
    {
        imagen_t prueba = {{0,1,0,1,0},{1,0,1,0,1},{0,1,0,1,0},{1,0,1,0,1},{0,1,0,1,0}};
        display_muestra_imagen(prueba);
        timer_delay(1000);
        imagen_t prueba2 = {{1,0,1,0,1},{0,1,0,1,0},{1,0,1,0,1},{0,1,0,1,0},{1,0,1,0,1}};
        display_muestra_imagen(prueba2);
        timer_delay(1000);
        display_limpia();
        timer_delay(1000);
    }
}
