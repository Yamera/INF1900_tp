#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum class Timer0Pin
{
    pb3,
    pb4
};

class Timer0
{
private:
    volatile uint8_t *OCR;

public:
    Timer0(Timer0Pin pin, uint8_t percentage);
    void setPercentage(uint8_t percentage);
};