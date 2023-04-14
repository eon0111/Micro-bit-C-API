#include "../../ubit/ubit.h"

void
main(int n)
{
    display_cambia_intensidad(INT_BAJA);
    display_limpia();

    boton_A_espera_pulsacion();
    imagen_t prueba = {{0,1,1,1,0},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1}};
    display_muestra_imagen(prueba);

    boton_B_espera_pulsacion();
    imagen_t prueba2 = {{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0}};
    display_muestra_imagen(prueba2);
}
