
#include <avr/io.h>
#include <avr/interrupt.h>

#include "classInterrupt.hpp"

#include "can.h"

void InterruptConfig::configureExternalInterrupt(InterruptType interruptType, TriggerMode triggerMode)
{
    cli();

    switch (interruptType)
    {
    case InterruptType::INT_0:
        EIMSK |= (1 << INT0);

        EICRA &= ~((1 << ISC01) | (1 << ISC00));

        switch (triggerMode)
        {
        case TriggerMode::LOW_LEVEL:

            break;
        case TriggerMode::ANY_CHANGE:
            EICRA |= (1 << ISC00);
            break;
        case TriggerMode::FALLING_EDGE:
            EICRA |= (1 << ISC01);
            break;
        case TriggerMode::RISING_EDGE:
            EICRA |= (1 << ISC01) | (1 << ISC00);
            break;
        default:
            break;
        }
        break;

    case InterruptType::INT_1:
        EIMSK |= (1 << INT1);

        EICRA &= ~((1 << ISC11) | (1 << ISC10));

        switch (triggerMode)
        {
        case TriggerMode::LOW_LEVEL:
            break;
        case TriggerMode::ANY_CHANGE:
            EICRA |= (1 << ISC10);
            break;
        case TriggerMode::FALLING_EDGE:
            EICRA |= (1 << ISC11);
            break;
        case TriggerMode::RISING_EDGE:
            EICRA |= (1 << ISC11) | (1 << ISC10);
            break;
        default:
            break;
        }
        break;

    case InterruptType::INT_2:
        EIMSK |= (1 << INT2);

        EICRA &= ~((1 << ISC21) | (1 << ISC20));

        switch (triggerMode)
        {
        case TriggerMode::LOW_LEVEL:
            break;
        case TriggerMode::ANY_CHANGE:
            EICRA |= (1 << ISC20);
            break;
        case TriggerMode::FALLING_EDGE:
            EICRA |= (1 << ISC21);
            break;
        case TriggerMode::RISING_EDGE:
            EICRA |= (1 << ISC21) | (1 << ISC20);
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    sei();
}

LightSensor::LightSensor(uint8_t pin, uint8_t low, uint8_t high)
    : pin_(pin), low_(low), high_(high)
{
    DDRA &= ~(1 << pin_);
}

uint8_t LightSensor::read(can &adcConverter)
{
    return (adc.lecture(pin_) >> 2);
}

bool LightSensor::isLow(uint8_t level)
{
    return level < low_;
}

bool LightSensor::isHigh(uint8_t level)
{
    return level >= high_;
}

bool LightSensor::isMid(uint8_t level)
{
    return level >= low_ && level < high_;
}
