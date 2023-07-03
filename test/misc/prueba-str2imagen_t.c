#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();
    display_cambia_intensidad(INT_BAJA);

    imagen_t_wrapper wrapper;
    char *str_tmp = "1111100000111110000011111";
    str2imagen_t(str_tmp, &wrapper);

    display_muestra_imagen(wrapper.imagen);
}
