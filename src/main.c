#include "../include/usart.h"
#include <util/delay.h>
#include "../include/led.h"

char
isNumber(unsigned char data)
{
  return ('0' <= data && data <= '9');
}

int main(void)
{
  USART_init();
  led_init();
  unsigned char buffer;
  while(1)
    {
      buffer = USART_read_char();
      if(isNumber(buffer)) led_blink_n_times(buffer-'0');
      else
        {
          USART_write_single_char(buffer);
        }
    }
}
