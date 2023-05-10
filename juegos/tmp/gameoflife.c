#include "../../ubit/ubit.h"

#define DIM 5

/* Algunos osciladores */
imagen_t poblacion = {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,0,1,0,0},{0,0,0,0,0}};
// imagen_t poblacion = {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0}};
// imagen_t poblacion = {{0,0,1,0,0},{1,0,0,1,0},{1,0,0,1,0},{0,1,0,0,0},{0,0,0,0,0}};
// imagen_t poblacion = {{1,1,0,0,0},{1,1,0,0,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,0,0,0}};

imagen_t siguiente_poblacion;

/* 
 * REGLAS: 
 *  - Si una célula viva y tiene 2 o 3 vecinos, sigue viva
 *  - Si una célula viva tiene menos de 2 o más de 3 vecinos, muere, por
 *    aislamiento o sobrepoblación respectivamente
 *  - Si una célula muerta tiene exactamente 3 vecinos, nace
 */
void
procesa_inividuo(int i, int j)
{
    int m, n, estado, vecinos = 0;

    /* Obtenemos los límites para generar las "coordenadas" de los vecinos inmediatos */
    int m_ini = (i - 1 <= 0) ? 0 : i - 1;
    int n_ini = (j - 1 <= 0) ? 0 : j - 1;

    int m_lim = (i + 1 >= DIM - 1) ? DIM - 1 : i + 1;
    int n_lim = (j + 1 >= DIM - 1) ? DIM - 1 : j + 1;

    /* Nos interesa conocer el número de individuos con vida a su alrededor */
    for (m = m_ini; m <= m_lim; m++)
        for (n = n_ini; n <= n_lim; n++)
            if ((m != i || n != j) && poblacion[m][n])
                vecinos++;

    /* Obtenemos el estado del individuo en la siguiente generación */
    estado = ((poblacion[i][j] && (vecinos == 2 || vecinos == 3)) ||
              (!poblacion[i][j] && vecinos == 3)) ? 1 : 0;

    /* Actualizamos el estado de la siguiente generación */
    siguiente_poblacion[i][j] = estado;
}

void
main(int n)
{
    microbit_inicializa_hardware();
    display_cambia_intensidad(INT_BAJA);
    display_muestra_imagen(poblacion);

    int i, j;

    while (1)
    {
        /* Genera la siguiente generación a partir de la actual */
        for (i = 0; i < DIM; i++)
            for (j = 0; j < DIM; j++)
                procesa_inividuo(i, j);

        /* Actualiza la generación actual */
        for (i = 0; i < DIM; i++)
            for (j = 0; j < DIM; j++)
                poblacion[i][j] = siguiente_poblacion[i][j];

        timer_delay(500);
        display_muestra_imagen(poblacion);
    }
}
