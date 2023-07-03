#include <ubit.h>

#define DIM     5
#define INCL    5
#define NIVELES 3

typedef struct {
    coordenada_t comienzo;
    coordenada_t final;
    imagen_t laberinto;
} nivel_t;

nivel_t nivel_1 = {.comienzo = {.x = 0, .y = 0}, .final = {.x = 4, .y = 4},
                  {{0,0,0,1,0},
                   {0,1,0,1,0},
                   {0,1,0,1,0},
                   {0,1,0,1,0},
                   {0,1,0,0,0}}};

nivel_t nivel_2 = {.comienzo = {.x = 0, .y = 0}, .final = {.x = 2, .y = 2},
                  {{0,0,0,0,0},
                   {0,1,1,1,0},
                   {0,1,0,1,0},
                   {0,1,0,1,0},
                   {0,1,0,0,0}}};

nivel_t nivel_3 = {.comienzo = {.x = 0, .y = 4}, .final = {.x = 0, .y = 1},
                  {{0,1,1,1,1},
                   {0,0,0,0,0},
                   {1,1,1,1,0},
                   {0,0,0,1,0},
                   {1,1,0,0,0}}};

nivel_t *niveles[] = {&nivel_1, &nivel_2, &nivel_3};

void
main (int n)
{
    microbit_inicializa_hardware();
    display_cambia_intensidad(INT_BAJA);

    coordenada_t posicion_jugador;
    coordenada_t posicion_anterior;
    int estado_meta = 0;

    for (int i = 0; i < NIVELES; i++)
    {
        posicion_jugador.x = niveles[i]->comienzo.x;
        posicion_jugador.y = niveles[i]->comienzo.y;

        /* Mostramos el estado inicial del laberinto en el display */
        display_enciende_LED(posicion_jugador.x, posicion_jugador.y);
        display_enciende_LED(niveles[i]->final.x, niveles[i]->final.y);
        display_muestra_imagen(niveles[i]->laberinto);

        while (posicion_jugador.x != niveles[i]->final.x ||
               posicion_jugador.y != niveles[i]->final.y)
        {
            posicion_anterior.x = posicion_jugador.x;
            posicion_anterior.y = posicion_jugador.y;

            /* Obtenemos las lecturas de inclinación del acelerómetro */
            int incl_x = inclinacion_eje_x();
            int incl_y = inclinacion_eje_y();

            /* Procesamos las colisiones con las paredes del laberinto */
            if (incl_x > INCL && posicion_jugador.x - 1 >= 0 &&         /* Inclinación hacia la IZDA. */
                !niveles[i]->laberinto[DIM - posicion_jugador.y - 1][posicion_jugador.x - 1])
                posicion_jugador.x--;
            else if (incl_x < -INCL && posicion_jugador.x + 1 < DIM &&  /* Inclinación hacia la DCHA. */
                    !niveles[i]->laberinto[DIM - posicion_jugador.y - 1][posicion_jugador.x + 1])
                posicion_jugador.x++;

            if (incl_y > INCL && posicion_jugador.y - 1 >= 0 &&         /* Inclinación hacia ABAJO */
                !niveles[i]->laberinto[DIM - posicion_jugador.y][posicion_jugador.x])
                posicion_jugador.y--;
            else if(incl_y < -INCL && posicion_jugador.y + 1 < DIM &&   /* Inclinación hacia ARRIBA */
                    !niveles[i]->laberinto[DIM - posicion_jugador.y - 2][posicion_jugador.x])
                posicion_jugador.y++;

            // TODO: refactorizar. Detallar los pseudocódigos de cada fase de la práctica y lo que se va aprendiendo en cada una.

            /* Actualizamos la posición del jugador en el display */
            timer_delay(200);
            display_apaga_LED(posicion_anterior.x, posicion_anterior.y);
            display_enciende_LED(posicion_jugador.x, posicion_jugador.y);

            /* Generamos el parpadeo del punto donde se encuentra la meta */
            estado_meta++;
            if (!(estado_meta % 2))
                display_enciende_LED(niveles[i]->final.x, niveles[i]->final.y);
            else
                display_apaga_LED(niveles[i]->final.x, niveles[i]->final.y);
        }
    }

    // TODO: suena melodía
    display_muestra_texto("WINNER!", MEDIO);
}
