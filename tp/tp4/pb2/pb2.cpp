
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BOUTON_PIN PD2

volatile bool gMinuterieExpiree = false;
volatile bool gBoutonPoussoir = false;
bool debutTest = false;

void stateMachine();

typedef enum
{
    INIT,
    PRESS1,
    RELEASE1,
    PRESS2,
    RELEASE2,
    PRESS3
} State;

State state = INIT;

void pins()

{
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD &= ~(1 << BOUTON_PIN);
}

void turnOnGreenLED()
{
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
}

void turnOnRedLED()
{
    PORTA &= ~(1 << PA1);
    PORTA |= (1 << PA0);
    debutTest = true;
}

bool stateButton()
{
    return PIND & (1 << PD2);
}

void turnOffLight()
{
    PORTA &= ~((1 << PA0) | (1 << PA1));
}

void initialisation(void)
{
    cli();
    pins();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

ISR(TIMER1_COMPA_vect)
{

    gMinuterieExpiree = 1;
}

ISR(INT0_vect)
{
    _delay_ms(30);
    if (debutTest)
    {
        gBoutonPoussoir = 1;
    }
    EIFR |= (1 << INTF0);
}

void partirMinuterie(uint16_t duree)
{

    gMinuterieExpiree = 0;

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A |= (1 << WGM11);

    TCCR1B |= (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A);
}

int main()
{

    initialisation();

    _delay_ms(10000);

    turnOnRedLED();
    _delay_ms(100);
    turnOffLight();

    partirMinuterie(780);

    do
    {

    } while (gMinuterieExpiree == 0 && gBoutonPoussoir == 0);

    cli();

    if (gBoutonPoussoir == 1 && gMinuterieExpiree == 0)
    {

        turnOnGreenLED();
    }
    else
    {

        turnOnRedLED();
    }
    return 0;
}