/**
 * @file 02_boton_espera_pulsacion.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba la espera a la pulsación de todos los botones
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

    boton_t botones[] = {BOTON_0, BOTON_1, BOTON_2, BOTON_A, BOTON_B, BOTON_LOGO};
    char *botones_str = "012ABM";
    char *btn_codi;

    int i;
    for (i = 0; i < 6; i++)
    {
        boton_espera_pulsacion(botones[i]);
        display_char2codi(botones_str[i], &btn_codi);
        display_muestra_sprite(btn_codi);
    }
}
