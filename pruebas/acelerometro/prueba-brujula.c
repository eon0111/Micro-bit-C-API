#include "../../ubit/ubit.h"

enum {NORTE, SUR, ESTE, OESTE};

imagen_t p_card[] = {{{1,0,0,0,1},{1,1,0,0,1},{1,0,1,0,1},{1,0,0,1,1},{1,0,0,0,1}},  /* N */
                     {{0,1,1,1,1},{1,0,0,0,0},{0,1,1,1,0},{0,0,0,0,1},{1,1,1,1,0}},  /* S */
                     {{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,0},{1,0,0,0,0},{1,1,1,1,1}},  /* E */
                     {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}}}; /* O */

/**
 * N: -2/-2/0, -2/0/0       
 * W: -1/-2/0, -1/0/-1      
 * S: -1/-1/0, -2/0/-2      
 * E: -2/-1/0, -2/0/-1      
 */

void
main(int n)
{
    brujula_inicializa();
    display_cambia_intensidad(INT_BAJA);

    int px, px2, py, pz;

    while (1) {
        timer_delay(500);
        px = brujula_lectura_x();
        px2 = brujula_lectura_x_2();
        py = brujula_lectura_y();
        pz = brujula_lectura_z();

        printf("px=%d px2=%d py=%d pz=%d\n", px, px2, py, pz);
    }
}
