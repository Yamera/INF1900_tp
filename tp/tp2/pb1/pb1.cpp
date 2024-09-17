/*
 * Noms: Yasmine Meraoubi, Maroua Lassakeur
 * Équipe: 70
 * Groupe: 01
 * TP2 PB1
 * Description: Appuyer 3 fois sur le bouton-poussoir afin d'allumer la DEL pendant 2 secondes.
 * Identifications matérielles : La pin D2 est notre boutton en entrée / Les pins A0 et A1 sont les sorties de la DEL
 */

/*
Table des états:
+----------------+-------+---------------+--------+
|  Etat courrant | Entree| Prochain Etat |  LED   |
+----------------+-------+---------------+--------+
| INIT           | 0     | INIT          |    off |
| INIT           | 1     | PRESS1        |    off |
| PRESS1         | 0     | PRESS1        |    off |
| PRESS1         | 1     | PRESS2        |    off |
| PRESS2         | 0     | PRESS2        |    off |
| PRESS2         | 1     | PRESS3        |    off |
| PRESS3         | X     | INIT          |     on |
+----------------+-------+---------------+--------+
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_PIN PD2

constexpr uint8_t DEBOUCE_DELAY_MS = 10;
constexpr uint16_t DELAY_MS = 2000;

typedef enum
{
    INIT,
    PRESS1,
    PRESS2,
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

bool isClicked()
{
    uint8_t initial = PIND & (1 << PD2);
    _delay_ms(DEBOUCE_DELAY_MS);
    return initial & PIND & (1 << PD2);
}

void turnOffLight()
{
    PORTA &= ~((1 << PA0) | (1 << PA1));
}

void stateMachine()
{
    bool buttonPressed = isClicked();
    switch (state)
    {
    case INIT:
        if (buttonPressed)
        {
            while (isClicked())
            {
            }
            state = PRESS1;
        }
        break;
    case PRESS1:
        if (buttonPressed)
        {
            while (isClicked())
            {
            }
            state = PRESS2;
        }
        break;
    case PRESS2:

        if (buttonPressed)
        {
            while (isClicked())
            {
            }
            state = PRESS3;
        }
        break;
    case PRESS3:
        state = INIT;
        turnOnGreenLED();
        _delay_ms(DELAY_MS);
        turnOffLight();
        break;
    default:
        state = INIT;
        break;
    }
}

int main()
{
    pins();
    while (1)
    {
        stateMachine();
    }
}
