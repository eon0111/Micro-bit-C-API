#include "../ubit/ubit.h"

void
main(int n)
{
    //printf(""); // FIXME: en alguna prueba si no ponía un printf el comienzo de la función principal, el código no hacía nada, pero de repente ha empezado a funcionar sin el printf... WTF
    display_cambia_intensidad(INT_BAJA);
    display_limpia();

    while (1)
    {
        if (boton_A_pulsado() == 1)
        {
            imagen_t prueba = {{0,1,1,1,0},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1}};
            display_muestra_imagen(prueba);
        }
        else if (boton_B_pulsado() == 1)
        {
            imagen_t prueba2 = {{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0}};
            display_muestra_imagen(prueba2);
        }
        else
        {
            imagen_t def = {{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1}};
            display_muestra_imagen(def);
        }
        timer_delay(100);
    }
}
