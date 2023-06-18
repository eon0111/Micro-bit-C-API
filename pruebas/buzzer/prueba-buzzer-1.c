#include <ubit.h>

void
main(int n)
{
    microbit_inicializa_hardware();

    buzzer_reproduce_nota(DO_3, NEGRA);
    buzzer_reproduce_nota(RE_3, NEGRA);
    buzzer_reproduce_nota(MI_3, NEGRA);
    buzzer_reproduce_nota(FA_3, NEGRA);
    buzzer_reproduce_nota(SOL_3, NEGRA);
    buzzer_reproduce_nota(LA_3, CORCHEA);
    buzzer_reproduce_nota(SI_3, CORCHEA);
    buzzer_reproduce_nota(DO_4, CORCHEA);
    buzzer_reproduce_nota(RE_4, CORCHEA);
    buzzer_reproduce_nota(MI_4, CORCHEA);
    buzzer_reproduce_nota(FA_4, SEMICORCHEA);
    buzzer_reproduce_nota(SOL_4, SEMICORCHEA);
    buzzer_reproduce_nota(LA_4, SEMICORCHEA);
    buzzer_reproduce_nota(SI_4, SEMICORCHEA);
    buzzer_reproduce_nota(DO_5, SEMICORCHEA);
}