#include <avr/io.h>
#include "head.h"
#include "../Header Files/wheels.h"



void servo_init()
{
	// Set pin to output
	DDRB |= (1 << PB6);
	
	// Timer Top
	ICR1 = 20000;
	
	TCCR1A = (1 << COM1B1);
	
	// PWM Phase and Frequency Correct, Clk/8
	TCCR1B = (1 << WGM13) | (1 << CS11);
	
	TCCR1C = 0x00;
}

uint8_t head_rotate(uint8_t ANGLE)
{
	if(ANGLE <= 180)
	{
		/*if(ANGLE < 90) {
			OCR1B = R90_ANGLE + (DEFAULT_ANGLE - R90_ANGLE) * (ANGLE / 90.0);
		}
		else {
			OCR1B = DEFAULT_ANGLE + (L90_ANGLE - DEFAULT_ANGLE) * ((ANGLE - 90) / 90.0);
		}*/
		OCR1B = L90_ANGLE + (R90_ANGLE - L90_ANGLE) * (ANGLE / 180.0);
		return 0;
	}
	return 1;
}

uint8_t head_look(uint8_t DIRECTION)
{
	switch(DIRECTION)
	{
		case LEFT:
		return head_rotate(180);
		
		case RIGHT:
		return head_rotate(0);
		
		case FORWARD:
		return head_rotate(90);
		
		default:
		return -1;
		break;
	}
}
