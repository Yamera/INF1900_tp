/*
 * Nom: compteur 32 bits/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 *
 * Version 1.2 par Jérôme Collin, août 2023
 * Nom : Yasmine Meraoubi (2292276) et Maroua Lassakeur ()
 * Groupe : 03
 * TP0 Pb1
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_PIN PD2

constexpr uint16_t DELAY_MS = 2000;

void pins()
{
  DDRA |= (1 << PA0) | (1 << PA1); // Configure
  DDRD &= ~(1 << BOUTON_PIN);
}

void allumerRouge()
{
  PORTA &= ~(1 << PA1);
  PORTA |= (1 << PA0);
}

void allumerVert()
{
  PORTA &= ~(1 << PA0);
  PORTA |= (1 << PA1);
}

bool isClicked()
{
  constexpr uint8_t debounceDelayMs = 10;
  uint8_t initial = PIND & (1 << PD2);
  _delay_ms(debounceDelayMs);
  return initial & PIND & (1 << PD2);
}

int main()
{
  pins();

  while (true)
  {
    if (isClicked())
    {
      allumerRouge();
    }
    else
    {
      allumerVert();
    }
  }
}
