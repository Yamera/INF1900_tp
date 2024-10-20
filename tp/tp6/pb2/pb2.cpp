/*
 * Noms: Yasmine Meraoubi et Maroua Lassakeur
 * Équipe: 70
 * Groupe: 03
 * TP6 pb1
 * Description: Ajustement de la DEL en fonction de la photorésistance,
 * A la lumiere ambiante la DEL s'allume ambre, a haute intensitee en rouge et a basse intensite en vert.
 * Identifications matérielles : La DEl libre est reliee a B0 et B1 en sortie,
 * et A0 est en  sortie pour le convertisseur.
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

const uint8_t GREEN_LED_DELAY_MS_FOR_AMBER_LED = 9;
const uint8_t RED_LED_DELAY_MS_FOR_AMBER_LED = 6;
const uint8_t LIGHT_THRESHOLD_LOW = 100;
const uint8_t LIGHT_THRESHOLD_HIGH = 240;

void pins()
{
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRA &= ~(1 << PA0);
}

void turnOnGreenLED()
{
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB1);
}

void turnOnRedLED()
{
    PORTB |= (1 << PB1);
    PORTB &= ~(1 << PB0);
}

void turnOnAmberLED()
{
    turnOnRedLED();
    _delay_ms(RED_LED_DELAY_MS_FOR_AMBER_LED);

    turnOnGreenLED();
    _delay_ms(GREEN_LED_DELAY_MS_FOR_AMBER_LED);
}

uint8_t readLightLevel(can &adcConverter)
{
    uint16_t rawValue = adcConverter.lecture(PA0);
    return (rawValue >> 2);
}

void initializeUART(void)
{
    UBRR0H = 0;
    UBRR0L = 0xCF;

    UCSR0A = 0;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void transmitUART(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

void setLed(uint8_t currentLightLevel)
{
    if (currentLightLevel < LIGHT_THRESHOLD_LOW)
    {
        turnOnGreenLED();
    }
    else if (currentLightLevel >= LIGHT_THRESHOLD_HIGH)
    {
        turnOnRedLED();
    }
    else
    {
        turnOnAmberLED();
    }
}

int main()
{
    initializeUART();
    pins();
    can adcConverter;
    uint8_t currentLightLevel;

    while (1)
    {
        currentLightLevel = readLightLevel(adcConverter);
        transmitUART(currentLightLevel);

        setLed(currentLightLevel);
    }
}
