#include <avr/io.h>
#include <util/delay.h>
#include "tools.h"
#include "labex.h"
#include "../Header Files/sonar.h"



uint8_t noObstacle(uint16_t value)
{
	return (value != TRIG_ERROR && value != ECHO_ERROR) && (value < 0 || value > 200);
}