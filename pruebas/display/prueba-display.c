#include "../../ubit/ubit.h"

void
main(int n)
{
    display_cambia_intensidad(INT_BAJA);
 
    while (1)
    {
        imagen_t prueba = {{0,1,0,1,0},{1,0,1,0,1},{0,1,0,1,0},{1,0,1,0,1},{0,1,0,1,0}};
        display_muestra_imagen(prueba);
        timer_delay(1000);
        imagen_t prueba2 = {{1,0,1,0,1},{0,1,0,1,0},{1,0,1,0,1},{0,1,0,1,0},{1,0,1,0,1}};
        display_muestra_imagen(prueba2);
        timer_delay(1000);
    }
}
