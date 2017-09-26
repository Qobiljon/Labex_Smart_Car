#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Header Files/wheels.h"
#include "../Header Files/head.h"
#include "../Special Files/labex.h"
#include "../Special Files/tools.h"
#include "../Header Files/bluetooth.h"
#include "../Header Files/sonar.h"



int main()
{
	wheels_init(HIGH);
	bluetooth_init();
	servo_init();
	
	// DEVICES ARE INITIALIZED
	control_mode = MODE_HANDDRIVEN;
	DDRC = 0xff;
	
	while(1)
	{
		switch(control_mode)
		{
			case MODE_AUTOPILOT:
			artificial_control();
			break;
			
			case MODE_HANDDRIVEN:
			manual_control();
			break;
			
			// IDLE STATE (WAIT UNTIL MODE CHANGES BACK)
			default:
			break;
		}
	}
	return 0;
}
