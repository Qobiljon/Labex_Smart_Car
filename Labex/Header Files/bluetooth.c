#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "bluetooth.h"
#include "../Special Files/tools.h"



void bluetooth_init()
{
	UBRR1H = (uint8_t)((MYBAUD) >> 8);
	UBRR1L = (uint8_t)(MYBAUD);

	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
	UCSR1C = (1 << USBS1) | (1 << UCSZ10) | (1 << UCSZ11);
	sei();
}

void bt_detach_device()
{
	UCSR1A = UCSR1B = UCSR1C = UBRR1H = UBRR1L = 0;
	cli();
}

uint8_t bt_receive_byte()
{
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

void bt_send_byte(uint8_t data)
{
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;
}

void bt_send_string(char* data, uint8_t len)
{
	bt_send_byte(len);

	uint8_t n;
	for (n = 0; n < len; n++)
	bt_send_byte(data[n]);
}

uint8_t bt_receive_string(char* data)
{
	uint8_t len = bt_receive_byte();

	uint8_t n;
	for (n = 0; n < len; n++)
	data[n] = bt_receive_byte();
	return len;
}
