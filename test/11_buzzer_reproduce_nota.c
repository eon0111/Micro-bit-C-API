/**
 * @file 01_buzzer_reproduce_nota.c
 * @author Noé Ruano (nrg916@alumnos.unican.es)
 * @brief Prueba la reproducción de todos los tonos disponibles con distintas
 * duraciones
 * @version 1.0
 * @date jul-2023
 * 
 */

#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();

    buzzer_reproduce_nota(DO_4, NEGRA);
    buzzer_reproduce_nota(RE_4, NEGRA);
    buzzer_reproduce_nota(MI_4, NEGRA);
    buzzer_reproduce_nota(FA_4, NEGRA);
    buzzer_reproduce_nota(SOL_4, NEGRA);
    buzzer_reproduce_nota(LA_4, CORCHEA);
    buzzer_reproduce_nota(SI_4, CORCHEA);
    buzzer_reproduce_nota(DO_5, CORCHEA);
    buzzer_reproduce_nota(RE_5, CORCHEA);
    buzzer_reproduce_nota(MI_5, CORCHEA);
    buzzer_reproduce_nota(FA_5, SEMICORCHEA);
    buzzer_reproduce_nota(SOL_5, SEMICORCHEA);
    buzzer_reproduce_nota(LA_5, SEMICORCHEA);
    buzzer_reproduce_nota(SI_5, SEMICORCHEA);
    buzzer_reproduce_nota(DO_6, SEMICORCHEA);
}