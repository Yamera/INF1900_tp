

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BOUTON_PIN PD2

constexpr uint8_t DEBOUNCE_DELAY_MS = 10;
constexpr uint16_t DELAY_MS = 2000;

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
volatile bool pressedButton = false;

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
}

void turnOnAmberLED()
{
    turnOnGreenLED();
    _delay_ms(25);
    turnOnRedLED();
    _delay_ms(10);
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
};

ISR(INT0_vect)
{
    _delay_ms(30);
    pressedButton = !pressedButton;
    EIFR |= (1 << INTF0); // Réinitialiser le flag d'interruption
}
void stateMachine()
{
    switch (state)
    {
    case INIT:
        turnOnRedLED();
        if (pressedButton == true)
        {
            state = PRESS1;
        }
        break;

    case PRESS1:
        turnOnAmberLED();
        if (pressedButton == false)
        {
            state = RELEASE1;
        }
        break;
    case RELEASE1:
        turnOnGreenLED();
        if (pressedButton)
        {
            state = PRESS2;
        }
        break;
    case PRESS2:
        turnOnRedLED();
        if (pressedButton)
        {
            state = RELEASE2;
        }
        break;
    case RELEASE2:
        turnOffLight();
        if (pressedButton)
        {
            state = PRESS3;
        }

        break;

    case PRESS3:
        turnOnGreenLED();
        if (pressedButton)
        {
            state = INIT;
        }
        break;
    default:
        state = INIT;
        break;
    }
}

int main()
{
    pins();
    initialisation();
    while (true)
    {
        stateMachine();
    }
}
