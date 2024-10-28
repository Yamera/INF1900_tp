#include "timer0.h"

void Timer0::setPercentage(uint8_t percentage)
{
    if (percentage > 100)
    {
        percentage = 100;
    }
    OCR = percentage(255 / 100);
}

Timer0::Timer0(Timer0Pin pin, uint8_t percentage)
{
    TCCR0A = 0;
    if (pin == Timer0Pin::pb3)
    {
        TCCR0A |= 1 << COM0A0;
        OCR = &OCR0A;
    }
    else
    {
        TCCR0A |= 1 << COM0B0;
        OCR = &OCR0B;
    }
    setPercentage(percentage);

    TCCR0B = 0;
    TCCR0B |= 1 << CS00;
}