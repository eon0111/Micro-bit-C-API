#include "../../ubit/ubit.h"

void
main(int n)
{
    while (1)
    {
        printf("temp: %d\n", (int)termometro_lectura());
        timer_delay(500);
    }
}