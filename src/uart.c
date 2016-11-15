#include <avr/io.h>
#include "../include/usart.h"

unsigned char
USART_ready_to_be_written();

void
USART_block_until_ready_to_write();

unsigned char
USART_ready_to_be_read();

void
USART_block_until_ready_to_read();

void
USART_init(void)
{
  /* set baud rate */
  UBRR0H = (unsigned char) (MYUBRR>>8);
  UBRR0L = (unsigned char) (MYUBRR);

  /* enable transmitter and receiver */
  UCSR0B = (1<<TXEN0) | (1<<RXEN0);

  /* set frame format 8data, 1 stop bit */
  UCSR0C = (3<<UCSZ00);

}


void
USART_write_single_char(unsigned char input)
{
  while ( !(UCSR0A & (1<<UDRE0)) )
    {};
  UDR0 = input;
}


void
USART_write_string(char input_string[])
{
  int current_index = 0;
  while(input_string[current_index] != '\0')
    {
      USART_write_single_char((unsigned char) input_string[current_index] );
      current_index++;
    }
}


unsigned char
USART_read_char()
{
  USART_block_until_ready_to_read();
  while ( !( UCSR0A & (1<<RXC0) ) )
    {};
  return UDR0;
}


unsigned char
USART_ready_to_be_read()
{
  return ( UCSR0A & (1<<RXC0) );
}


void
USART_block_until_ready_to_read()
{
  while ( !USART_ready_to_be_read() )
    {};
}


unsigned char
USART_ready_to_be_written()
{
  return ( UCSR0A & (1<<UDRE0) );
}


void
USART_block_until_ready_to_write()
{
  while ( !USART_ready_to_be_written() )
    {};
}

