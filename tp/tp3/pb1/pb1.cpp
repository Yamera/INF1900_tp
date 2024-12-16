#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_PIN PD2

constexpr uint16_t DELAY_MS = 2000;

void pins();
void setPWM();
void turnOnGreenLED();
void turnOffLight();
bool isClicked();

void pins()
{
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD &= ~(1 << BOUTON_PIN);
} 


void delai(uint8_t pourcentagePWM)
{

    uint16_t delaiTotal = (pourcentagePWM * DELAI_BASE) / 100;
    for (uint16_t i = 0; i < delaiTotal; i++)
    {
        _delay_ms(1);
    }
}

void setPWM()
{
    int pourcentageAllume = 100;
    int nombrePeriodes = 5;

    for (int i = 0; i < nombrePeriodes; i++)
    {

        int dureeAllumee = (pourcentageAllume * 10);

        turnOnGreenLED();
        delai(pourcentageAllume);

        turnOffLight();
        delai(100 - dureeAllumee);

        pourcentageAllume -= 20;
    }
}

void turnOnGreenLED()
{
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
}

void turnOffLight()
{
    PORTA &= ~((1 << PA0) | (1 << PA1));
}

bool isClicked()
{
    uint8_t initial = PIND & (1 << BOUTON_PIN);
    _delay_ms(DELAY_MS);
    uint8_t current = PIND & (1 << BOUTON_PIN);
    return (initial == 0 && current == 0);
}

int main()
{
    pins();
    while (true)
    {
        if (isClicked())
        {
            setPWM();
        }
    }
}