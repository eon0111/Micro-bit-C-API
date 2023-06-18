#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();
    display_cambia_intensidad(INT_BAJA);

    char *str = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";

    display_muestra_texto(str, VEL_1);
}
