#include <ubit.h>

imagen_t a    = {{0,1,1,1,0},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1}};
imagen_t b    = {{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0}};
imagen_t m    = {{1,0,0,0,1},{1,1,0,1,1},{1,0,1,0,1},{1,0,0,0,1},{1,0,0,0,1}};
imagen_t cero = {{0,0,1,0,0},{0,1,0,1,0},{0,1,0,1,0},{0,1,0,1,0},{0,0,1,0,0}};
imagen_t uno  = {{0,0,1,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}};
imagen_t dos  = {{0,1,1,1,0},{1,0,0,0,1},{0,0,1,1,0},{0,1,0,0,0},{1,1,1,1,1}};

imagen_t *imagenes[] = {&a, &b, &m, &cero, &uno, &dos};

void
muestra_caracter(int i)
{
    display_limpia();
    if (i >= BOTON_A && i <= BOTON_2)
        display_muestra_imagen(*imagenes[i]);       
}

void
main(int n)
{
    int i;
    for (i = 0; i <= BOTON_2; i++)
    {
        boton_espera_pulsacion(i);
        muestra_caracter(i);
    }
}