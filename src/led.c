#include <avr/io.h>
#include <util/delay.h>
#include "../include/led.h"

void
led_init()
{
  DDRB |= (1 << PB5);
  led_switch_off();
}

void
led_switch_on()
{
  PORTB |= (1 << PB5);
}

void
led_switch_off()
{
  PORTB &= ~(1 << PB5);
}

void
led_blink_n_times(int n)
{
  led_switch_off();
  int counter = 0;
  while(counter < n)
    {
      _delay_ms(500);
      led_switch_on();
      _delay_ms(500);
      led_switch_off();
      counter++;
    }
  _delay_ms(500);
}
