/*
 * Noms: Yasmine Meraoubi et Maroua Lassakeur
 * Équipe: 70
 * Groupe: 03
 * TP6 pb1
 * Description: Lorsque le bouton est appuyer, un compteur est initialiser s'il atteint 120, la LED verte
 * pendant  1/2 seconde, ou lorsque le bouton est relache. Puis la DEl rouge s'allume 2s plus tard
 * au nombre de compteur / 2 fois puis la DEL verte pendant 1s, et retour a l'etat initial
 * Identifications matérielles : La DEl libre est reliee a B0 et B1 en sortie,
 * et le signal de sortie au port PD2
 */

/*
Table des états:
+-----------------------+-----------------------------+------------------------+-----------------------------------+
|    Current State      |        Input                |      Next State        |          Led State                |
+-----------------------+-----------------------------+------------------------+-----------------------------------+
| WAIT_FOR_BUTTON_PRESS | 1                           | BUTTON_HELD            | OFF                               |
| WAIT_FOR_BUTTON_PRESS | 0                           | WAIT_FOR_BUTTON_PRESS  | OFF                               |
| BUTTON_HELD           | 0                           | EXECUTE_SEQUENCE       | OFF                               |
| BUTTON_HELD           | 1 (maxCounterValue Reached) | EXECUTE_SEQUENCE       | OFF                               |
| BUTTON_HELD           | 1                           | BUTTON_HELD            | OFF                               |
| EXECUTE_SEQUENCE      | 1 (Sequence Done)           | WAIT_FOR_BUTTON_PRESS  | Green Blink, Red Blink,Green,OFF  |
| EXECUTE_SEQUENCE      | 0                           | EXECUTE_SEQUENCE       | LED Blinking                      |
+-----------------------+-----------------------------+------------------------+-----------------------------------+
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t MAX_COUNTER_VALUE = 120;
const uint16_t GREEN_BLINK_TOTAL_MS = 500;
const uint16_t GREEN_BLINK_INTERVAL_MS = 125;
const uint8_t RED_BLINK_DURATION_MS = 250;
const uint8_t RED_BLINK_DEFAULT_COUNT = 2;
const uint16_t DELAY_AFTER_GREEN_BLINK_MS = 2000;
const uint16_t GREEN_AFTER_RED_MS = 1000;

enum class State
{
    WAIT_FOR_BUTTON_PRESS,
    BUTTON_HELD,
    EXECUTE_SEQUENCE
};

volatile uint8_t buttonPressCounter = 0;
volatile bool buttonPressed = false;

void pins()
{
    DDRB |= (1 << DDB0) | (1 << DDB1);
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PD2);
}

void setLedGreen(bool isLit)
{
    if (isLit)
        PORTB |= (1 << PB0);
    else
        PORTB &= ~(1 << PB0);
}

void setLedRed(bool isLit)
{
    if (isLit)
        PORTB |= (1 << PB1);
    else
        PORTB &= ~(1 << PB1);
}

void blinkLedGreen()
{
    uint16_t iterations = GREEN_BLINK_TOTAL_MS / (2 * GREEN_BLINK_INTERVAL_MS);

    for (uint16_t i = 0; i < iterations; i++)
    {
        setLedGreen(true);
        _delay_ms(GREEN_BLINK_INTERVAL_MS);

        setLedGreen(false);
        _delay_ms(GREEN_BLINK_INTERVAL_MS);
    }
}

void blinkLedRed(uint8_t times)
{
    for (uint8_t i = 0; i < times; i++)
    {
        setLedRed(true);
        _delay_ms(RED_BLINK_DURATION_MS);
        setLedRed(false);
        _delay_ms(RED_BLINK_DURATION_MS);
    }
}

void configureTimer1()
{
    TCNT1 = 0;
    OCR1A = 0xC35;

    TCCR1A = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS12);

    TIMSK1 |= (1 << OCIE1A);
}

void initializeSystem(void)
{
    cli();

    EICRA = (1 << ISC00);
    EIMSK |= (1 << INT0);

    sei();
}

ISR(TIMER1_COMPA_vect)
{
    if (buttonPressed && buttonPressCounter < MAX_COUNTER_VALUE)
    {
        buttonPressCounter++;
    }
}

ISR(INT0_vect)
{
    if (!(PIND & (1 << PD2)))
    {
        buttonPressed = true;
    }
    else
    {
        buttonPressed = false;
    }
}

int main()
{
    pins();
    initializeSystem();
    configureTimer1();

    uint8_t redBlinks = 0;

    State currentState = State::WAIT_FOR_BUTTON_PRESS;

    while (1)
    {
        switch (currentState)
        {
        case State::WAIT_FOR_BUTTON_PRESS:
            if (buttonPressed)
            {
                buttonPressCounter = 0;
                currentState = State::BUTTON_HELD;
            }
            break;

        case State::BUTTON_HELD:
            if (!buttonPressed || buttonPressCounter >= MAX_COUNTER_VALUE)
            {
                currentState = State::EXECUTE_SEQUENCE;
            }
            break;

        case State::EXECUTE_SEQUENCE:
            blinkLedGreen();
            _delay_ms(DELAY_AFTER_GREEN_BLINK_MS);

            redBlinks = buttonPressCounter / 2;
            if (redBlinks == 0)
                redBlinks = RED_BLINK_DEFAULT_COUNT;

            blinkLedRed(redBlinks);

            setLedGreen(true);
            _delay_ms(GREEN_AFTER_RED_MS);
            setLedGreen(false);

            buttonPressCounter = 0;
            currentState = State::WAIT_FOR_BUTTON_PRESS;
            break;

        default:
            currentState = State::WAIT_FOR_BUTTON_PRESS;
            break;
        }
    }
}