#define FCPU 16000000
#define BAUD 9600 // XBee's baud rate must match this
#define MYUBRR ( FCPU / 16 / BAUD ) - 1

void USART_init(void);

void USART_write_single_char(unsigned char input);

void USART_write_string(char input_string[]);

unsigned char USART_read_char();
