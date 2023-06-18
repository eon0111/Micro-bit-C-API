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
    microbit_inicializa_hardware();

    while (1)
    {
        muestra_caracter((boton_pulsado(BOTON_A)) ? BOTON_A :
                         (boton_pulsado(BOTON_B)) ? BOTON_B :
                         (boton_pulsado(BOTON_LOGO)) ? BOTON_LOGO :
                         (boton_pulsado(BOTON_0)) ? BOTON_0 :
                         (boton_pulsado(BOTON_1)) ? BOTON_1 :
                         (boton_pulsado(BOTON_2)) ? BOTON_2 : -1);
        timer_delay(100);
    }
}