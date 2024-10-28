#include <avr/io.h>
#include "can.h"

#ifndef CLASS_INTERRUPT_HPP
#define CLASS_INTERRUPT_HPP
#include <avr/io.h>
#include "can.h"

enum class TriggerMode
{
    LOW_LEVEL,
    ANY_CHANGE,
    FALLING_EDGE,
    RISING_EDGE
};

enum class InterruptType
{
    INT_0,
    INT_1,
    INT_2
};

class InterruptConfig
{
public:
    static void configureExternalInterrupt(InterruptType interruptType, TriggerMode triggerMode); // Mise à jour de la signature
};

class LightSensor
{
public:
    LightSensor(uint8_t pin, uint8_t low, uint8_t high);

    uint8_t lecture(can &adcConverter);

    bool isLow(uint8_t level);
    bool isHigh(uint8_t level);
    bool isMid(uint8_t level);

private:
    uint8_t pin_;
    uint8_t low_;
    uint8_t high_;
};
