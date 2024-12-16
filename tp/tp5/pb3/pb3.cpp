#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"
#include <avr/eeprom.h>

#define BOUTON_PIN PD2

const char chaine[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
const uint16_t adresse = 0x0000;
char tableau[100];
uint8_t donnee;

void pins()
{
    DDRA |= (1 << PA0) | (1 << PA1); // Configurer PA0 et PA1 en sortie
    DDRD &= ~(1 << BOUTON_PIN);      // Configurer BOUTON_PIN (PD2) en entrée
    PORTD |= (1 << BOUTON_PIN);      // Activer la résistance pull-up pour le bouton
}

void modeEcriture(Memoire24CXXX &memory)
{
    uint16_t adresseEcriture = adresse;
    for (uint8_t i = 0; i < sizeof(chaine) - 1; i++)
    {
        memory.ecriture(adresseEcriture, chaine[i]);
        adresseEcriture++;
        _delay_ms(50);
    }
}

void modeLecture(Memoire24CXXX &memory)
{
    uint16_t adresseLecture = adresse;
    for (uint8_t i = 0; i < sizeof(chaine) - 1; i++)
    {
        memory.lecture(adresseLecture, &donnee);
        tableau[i] = donnee;
        adresseLecture++;
    }
}

void initialisationUART(void)
{
    // Initialisation à 2400 bauds
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // Activer la réception et la transmission via UART0
    UCSR0A = 0;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames : 8 bits, 1 stop bit, sans parité
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void transmissionUART(uint8_t donnee)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;          // Attendre que le registre soit prêt
    UDR0 = donnee; // Envoyer la donnée
}

int main()
{
    pins();               // Initialisation des broches
    initialisationUART(); // Initialisation UART

    Memoire24CXXX memory;

    // Écriture de la chaîne dans la mémoire EEPROM
    modeEcriture(memory);

    // Lecture de la chaîne depuis la mémoire EEPROM
    modeLecture(memory);

    // Transmission UART de la chaîne lue
    for (uint8_t i = 0; i < sizeof(chaine) - 1; i++)
    {
        transmissionUART(tableau[i]);
        _delay_ms(50); // Délai pour éviter la saturation du récepteur
    }

    // Transmission UART de la phrase "Le robot en INF1900\n"
    char mots[21] = "Le robot en INF1900\n";
    for (uint8_t j = 0; j < 20; j++)
    {
        transmissionUART(mots[j]);
        _delay_ms(50); // Délai après chaque transmission
    }

    while (1)
    {
        // Boucle infinie
    }
}
