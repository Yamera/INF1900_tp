#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BOUTON_PIN PD2

void ajustementPwm(uint8_t ratioA, uint8_t ratioB)
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)

    OCR1A = ratioA;

    OCR1B = ratioB;

    DDRD |= (1 << PD4) | (1 << PD5);

    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A |= (1 << WGM00) | (1 << COM1A1) | (1 << COM1B1);

    TCCR1B |= (1 << CS01);

    TCCR1C = 0;
}

int main()
{
    while (true)
    {
        ajustementPwm(0.75 * (255), 0.25 * (255));
        }
}