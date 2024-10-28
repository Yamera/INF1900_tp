#include "timer1.h"

Timer1::Timer1(Timer1Pin pin)
{
    TCCR1A = 0;

    if (pin == Timer1Pin::pd5)
    {
        pinPos = PD5;
        OCR = &OCR1A;
        TCCR1A |= 1 << COM1A0;
    }
    else
    {
        pinPos = PD4;
        OCR = &OCR1B;
        TCCR1A |= 1 << COM1B0;
    }
    DDRD |= 1 << pinPos;

    TCCR1B = 0;

    TCCR1B |= 1 << WGM12;
    TCCR1C = 0;
}

void Timer1::startTimer()
{
    PORTD &= ~(1 << pinPos);
    TCNT1 = 0;
    TCCR1B |= 1 << CS12 | 1 << CS10;
}

uint8_t Timer1::stopTimer()
{
    TCCR1B &= ~(1 << CS12 | 1 << CS10);
    return TCNT1;
}

void Timer1::countMS(uint16_t durationInMs)
{
    OCR = ((durationInMs 100) / 128) * 10;
    startTimer();
}