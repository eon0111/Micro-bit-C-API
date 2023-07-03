/**
 * @file 01_boton_pulsado.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba la detección de pulsaciones en todos los botones
 * @version 1.0
 * @date jul-2023
 * 
 */

#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();
    display_cambia_intensidad(INT_BAJA);
    
    char btn;
    char *btn_codi;
    while (1)
    {
        btn = (boton_pulsado(BOTON_0))    ? '0' :
              (boton_pulsado(BOTON_1))    ? '1' : 
              (boton_pulsado(BOTON_2))    ? '2' : 
              (boton_pulsado(BOTON_LOGO)) ? 'M' : 
              (boton_pulsado(BOTON_A))    ? 'A' : 
              (boton_pulsado(BOTON_B))    ? 'B' : '-';

        display_char2codi(btn, &btn_codi);
        display_muestra_sprite(btn_codi);

        timer_delay(100);
    }
}
