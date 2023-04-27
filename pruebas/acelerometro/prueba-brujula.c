#include "../../ubit/ubit.h"
#include <math.h>

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

float
orientacion()
{
    return atan((float)brujula_lectura_y() / (float)brujula_lectura_x());
}

int
get_p(int d)
{
    return (-5 < d  && d < 5)    ? 2 :
           (-10 < d && d <= -5)  ? 1 :
           (-15 < d && d <= -10) ? 0 :
           (5 <= d  && d < 10)   ? 3 : 4;
}

void
main(int n)
{
    microbit_inicializa_hardware();
    brujula_inicializa();
    display_cambia_intensidad(INT_BAJA);

    int b_x, b_y, b_z;
    int d_x, d_y, p_x, p_y;

    while (1) {
        timer_delay(250);

        d_x = inclinacion_eje_x();
        d_y = inclinacion_eje_y();
        p_x = get_p(d_x);
        p_y = get_p(d_y);
        display_limpia();
        display_enciende_LED(p_x, p_y);

        b_x = brujula_lectura_x();
        b_y = brujula_lectura_y();
        b_z = brujula_lectura_z();

        printf("b_x=%d b_y=%d b_z=%d orientacion: %d\n", b_x, b_y, b_z, (int)orientacion());
    }
}
