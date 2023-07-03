#include <ubit.h>

int
get_p(float d)
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
    display_cambia_intensidad(INT_BAJA);

    float d_x, d_y;
    int p_x, p_y;

    while (1)
    {
        d_x = acelerometro_inclinacion_eje_x();
        d_y = acelerometro_inclinacion_eje_y();

        p_x = get_p(d_x);
        p_y = get_p(d_y);

        printf("d_x=%d\td_y=%d\tp_x=%d\tp_y=%d\n", (int)d_x, (int)d_y, p_x, p_y);

        display_limpia();
        display_enciende_LED(p_x, p_y);

        timer_delay(100);
    }
}