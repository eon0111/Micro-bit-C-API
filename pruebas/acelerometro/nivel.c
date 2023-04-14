#include "../../ubit/ubit.h"
#include <math.h>

float
inclinacion_eje_x() {
    float d = atan((float)acelerometro_lectura_z() /
                   (float)acelerometro_lectura_x()) * RAD_A_GRAD;
    return (d < 0) ? -90 - d : 90 - d;
}

float
inclinacion_eje_y() {
    float d = atan((float)acelerometro_lectura_z() /
                   (float)acelerometro_lectura_y()) * RAD_A_GRAD;
    return (d < 0) ? -90 - d : 90 - d;
}

int
get_p(int d)
{
    return (-9 < d  && d < 9)    ? 2 :
           (-18 < d && d <= -9)  ? 1 :
           (-27 < d && d <= -18) ? 0 :
           (9 <= d  && d < 18)   ? 3 : 4;
}

void
main(int n)
{
    microbit_inicializa_hardware();

    int d_x, d_y, p_x, p_y;

    while (1)
    {
        d_x = inclinacion_eje_x();
        d_y = inclinacion_eje_y();
        
        p_x = get_p(d_x);
        p_y = get_p(d_y);

        display_limpia();
        display_enciende_LED(p_x, p_y);

        timer_delay(100);
    }
}