#include <avr/io.h>
#include <util/delay.h>
#include "wheels.h"
#include "../Special Files/tools.h"



void wheels_init(uint8_t ACTION)
{
	DDROUT = 0xff;
	
	if(ACTION == HIGH)
	{
		OUT |= 1 << ENABLE_LEFT_WHEEL;
		OUT |= 1 << ENABLE_RIGHT_WHEEL;
	}
	else if(ACTION == LOW)
	{
		OUT &= ~(1 << ENABLE_LEFT_WHEEL);
		OUT &= ~(1 << ENABLE_RIGHT_WHEEL);
	}
}

void wheel_act(uint8_t WHEEL, uint8_t ACTION)
{
	// FIND PROPER ACTION VALUES
	uint8_t IN_FIRST = 0, IN_SECOND = 0;

	switch(ACTION)
	{
		case FORWARD:
		IN_FIRST = HIGH;
		IN_SECOND = LOW;
		break;
		
		case BACKWARD:
		IN_FIRST = LOW;
		IN_SECOND = HIGH;
		break;
		
		case BRAKE:
		IN_FIRST = HIGH;
		IN_SECOND = HIGH;
		break;
		
		case COAST:
		IN_FIRST = LOW;
		IN_SECOND = LOW;
		break;
		
		default:
		break;
	}
	
	if(WHEEL == ALL_WHEELS)
	{
		BIT_TOGGLE(OUT, IN1, IN_FIRST);
		BIT_TOGGLE(OUT, IN2, IN_SECOND);
		BIT_TOGGLE(OUT, IN3, IN_FIRST);
		BIT_TOGGLE(OUT, IN4, IN_SECOND);
	}
	else if(WHEEL == LEFT_WHEELS)
	{
		BIT_TOGGLE(OUT, IN1, IN_FIRST);
		BIT_TOGGLE(OUT, IN2, IN_SECOND);
	}
	else if(WHEEL == RIGHT_WHEELS)
	{
		BIT_TOGGLE(OUT, IN3, IN_FIRST);
		BIT_TOGGLE(OUT, IN4, IN_SECOND);
	}
}

void step(uint8_t WHEEL, uint8_t ISFORWARD)
{
	if(ISFORWARD == POSITIVE)
	{
		wheel_act(WHEEL, FORWARD);
		SLEEP(STEP_LEN);
		wheel_act(WHEEL, BRAKE);
	}
	else if(ISFORWARD == NEGATIVE)
	{
		wheel_act(WHEEL, BACKWARD);
		SLEEP(STEP_LEN);
		wheel_act(WHEEL, BRAKE);
	}
}

void wheels_turn_stay(uint8_t DIRECTION) {
	if(DIRECTION == LEFT)
	{
		wheel_act(LEFT_WHEELS, BACKWARD);
		wheel_act(RIGHT_WHEELS, FORWARD);
	}
	else if(DIRECTION == RIGHT)
	{
		wheel_act(LEFT_WHEELS, FORWARD);
		wheel_act(RIGHT_WHEELS, BACKWARD);
	}
}

void wheels_turn(uint8_t DIRECTION, uint8_t CUR_DIR) {
	if(DIRECTION == LEFT)
	{
		wheel_act(LEFT_WHEELS, BRAKE);
		wheel_act(RIGHT_WHEELS, CUR_DIR);
	}
	else if(DIRECTION == RIGHT)
	{
		wheel_act(LEFT_WHEELS, CUR_DIR);
		wheel_act(RIGHT_WHEELS, BRAKE);
	}
}

void motor_offline_check()
{
	while (1){
		wheel_act(ALL_WHEELS, FORWARD);
		SLEEP(200);
		wheels_turn_stay(RIGHT);
		
		wheel_act(ALL_WHEELS, BACKWARD);
		SLEEP(200);
		wheels_turn_stay(LEFT);
		
		uint8_t n;
		for(n = 0; n < 8; n++){
			wheel_act(LEFT_WHEELS, FORWARD);
			wheel_act(RIGHT_WHEELS, BACKWARD);
			SLEEP(200);
			
			wheel_act(LEFT_WHEELS, BACKWARD);
			wheel_act(RIGHT_WHEELS, FORWARD);
			SLEEP(200);
		}
		
		for(n = 0; n < 8; n++){
			wheel_act(LEFT_WHEELS, FORWARD);
			wheel_act(RIGHT_WHEELS, FORWARD);
			SLEEP(200);
			
			wheel_act(LEFT_WHEELS, BACKWARD);
			wheel_act(RIGHT_WHEELS, BACKWARD);
			SLEEP(200);
		}
	}
}
