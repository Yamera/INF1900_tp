/*
 * Noms: Yasmine Meraoubi, Maroua Lassakeur
 * Équipe: 70
 * Groupe: 01
 * TP2 PB2
 * Description: DEl initialement en rouge, lorsque appuyer passe au ambre. Lorsque relâché devient vert, ensuite lorsque appuyer
 * repasse au rouge, quand relâché s'éteint. Reappuyer l'a rend vert, puis relâcher repart à l'état initial rouge.
 * Identifications matérielles : La pin D2 est notre boutton en entrée / Les pins A0 et A1 sont les sorties de la DEL.
 */

/*
Table des états: //Changer nom des etats
+---------------+-------+---------------+-------+
| Etat courrant | Entree|  Prochain Etat| DEL   |
+---------------+-------+---------------+-------+
| INIT          |     0 | INIT          | Red   |
| INIT          |     1 | PRESS1        | Red   |
| PRESS1        |     0 | RELEASE1      | Amber |
| PRESS1        |     1 | PRESS1        | Amber |
| RELEASE1      |     0 | RELEASE       | Green |
| RELEASE1      |     1 | PRESS2        | Green |
| PRESS2        |     0 | RELEASE2      | Red   |
| PRESS2        |     1 | PRESS2        | Red   |
| RELEASE2      |     0 | RELEASE2      | Off   |
| RELEASE2      |     1 | PRESS3        | Off   |
| PRESS3        |     0 | INIT          | Green |
| PRESS3        |     1 | PRESS3         | Green |
+---------------+-------+---------------+-------+
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_PIN PD2

constexpr uint8_t debounceDelayMs = 10;
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
    return PIND & (1 << PD2); // fonction utile ?
}
bool isClicked()
{
    uint8_t initial = stateButton();
    _delay_ms(debounceDelayMs);
    return initial && stateButton();
}

void turnOffLight()
{
    PORTA &= ~((1 << PA0) | (1 << PA1));
}

bool isRelease()
{
    uint8_t initial = stateButton();
    _delay_ms(debounceDelayMs);
    return (!initial && !(PIND & (1 << PD2)));
}

void stateMachine()
{
    switch (state)
    {
    case INIT:
        turnOnRedLED();
        if (isClicked())
        {
            state = PRESS1;
        }
        break;

    case PRESS1:
        turnOnAmberLED();
        if (isRelease())
        {
            state = RELEASE1;
        }
        break;
    case RELEASE1:
        turnOnGreenLED();
        if (isClicked())
        {
            state = PRESS2;
        }
        break;
    case PRESS2:
        turnOnRedLED();
        if (isRelease())
        {
            state = RELEASE2;
        }
        break;
    case RELEASE2:
        turnOffLight();
        if (isClicked())
        {
            state = PRESS3;
        }

        break;

    case PRESS3:
        turnOnGreenLED();
        if (isRelease())
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
    while (true)
    {
        stateMachine();
    }
}
