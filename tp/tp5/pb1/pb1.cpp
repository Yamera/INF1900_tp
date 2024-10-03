#include "memoire_24.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <util/delay.h>

const char chaine[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
const uint16_t adresse = 0x0000;
char tableau[100];
uint8_t donnee;

void pins()
{
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD &= ~(1 << BOUTON_PIN);
}

void allumerVert()
{
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
}

void allumerRouge()
{
    PORTA &= ~(1 << PA1);
    PORTA |= (1 << PA0);
}

void modeEcriture()
{
    for (uint8_t i = 0; i < 22; i++)
    {
        memory.ecriture(adresseEcriture, chaine[i]);
        adresseEcriture++;
        delay_ms(5);
    }
}

void modeLecture()
{
    for (uint8_t i = 0; i < 22 1; i++)
    {
        memory.lecture(adresseLecture, &donnee);
        tableau[i] = donnee;
        adresseLecture++;
    }
}

int main()
{
    pins();
    Memoire24CXXX memory;
    modeEcriture(Memoire24CXXX & memory);
    modeLecture(Memoire24CXXX & memory);

    if (strcmp(chaine.tableau) = 0)
    {
        allumerVert();
    }
    else
    {
        allumerRouge();
    }
}
