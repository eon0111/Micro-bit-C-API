#include "../ubit/ubit.h"

void
main(int n)
{
    brujula_inicializa();
    int px;

    while (1) {
        timer_delay(500);
        px = brujula_lectura_x();
        printf("px=%d\n", px);
    }
}