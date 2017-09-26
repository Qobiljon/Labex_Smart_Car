#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "labex.h"
#include "../Header Files/bluetooth.h"
#include "../Header Files/wheels.h"
#include "../Special Files/tools.h"
#include "../Header Files/sonar.h"
#include "../Header Files/head.h"



// VARIABLES NEEDED FOR BT_ISR and Control Routines
volatile uint8_t action = 0, data = 0, bt_react = 0;

// VARIABLES FOR BLUETOOTH CONTROL HANDLING
volatile uint8_t cur_dir = COAST;


// ISR FOR BLUETOOTH SIGNALS HANDLING
ISR(USART1_RX_vect)
{
	if(bt_react)
	{
		data = UDR1;
		bt_react = 0;
		
		if(control_mode == MODE_HANDDRIVEN)
		{
			// HANDLING BT CONTROL ON HANDDRIVEN MODE
			#pragma region
			switch(action){
				case ACTION_MOVE:
				handle_move_action(data);
				break;
				
				case ACTION_LOOK:
				handle_look_action(data);
				break;
				
				case ACTION_PERFORM:
				handle_perform_action(data);
				break;
				
				case ACTION_CHANGEMODE:
				control_mode = data;
				break;

				case ACTION_DATAREQUEST:
				handle_datarequest_action(data);
				break;
				
				default:
				break;
			}
			#pragma endregion
		}
		else if(control_mode == MODE_AUTOPILOT)
		{
			// HANDLING BT CONTROL ON AUTOPILOT MODE
			#pragma region
			switch(action){
				case ACTION_CHANGEMODE:
				control_mode = data;
				break;
				
				case ACTION_PERFORM:
				handle_perform_action(data);
				break;
				
				case ACTION_DATAREQUEST:
				handle_datarequest_action(data);
				break;
				
				default:
				break;
			}
			#pragma endregion
		}
	}
	else
	{
		action = UDR1;
		bt_react = 1;
	}
}


void manual_control()
{
	while(control_mode == MODE_HANDDRIVEN)
	{
		
	}
}

void artificial_control()
{
	uint16_t data;
	head_look(LEFT);
	SLEEP(500);
	head_look(RIGHT);
	SLEEP(500);
	
	const uint16_t _90DRT = 400;
	const uint16_t _90DLT = 200;
	const uint8_t MIN_DIS = 20;
	
	while(control_mode == MODE_AUTOPILOT)
	{
		// CHECK FORWARD
		head_look(FORWARD);
		SLEEP(_90DLT);
		
		data = read_sonar_precise();
		
		if(data == ECHO_ERROR || data == TRIG_ERROR)
		{
			PORTC = 0b11111111;
		}
		else if(data != 4 && data < MIN_DIS)
		{
			wheel_act(ALL_WHEELS, BRAKE);
			
			// CHECK THE RIGHT SIDE
			head_look(RIGHT);
			SLEEP(_90DLT);
			data = read_sonar_precise();
			
			if(data == ECHO_ERROR || data == TRIG_ERROR)
			{
				PORTC = 0b11110000;
			}
			else if(data != 4 && data > MIN_DIS)
			{
				wheels_turn_stay(RIGHT);
				SLEEP(_90DRT);
				wheel_act(ALL_WHEELS, FORWARD);
			}
			else if(data != 4)
			{
				// CHECK THE LEFT SIDE
				head_look(LEFT);
				SLEEP(_90DLT);
				data = read_sonar_precise();
				
				if(data == ECHO_ERROR || data == TRIG_ERROR)
				{
					PORTC = 0b00001111;
				}
				else if(data > MIN_DIS)
				{
					wheels_turn_stay(LEFT);
					SLEEP(_90DRT);
					wheel_act(ALL_WHEELS, FORWARD);
				}
				else
				{
					// GO BACK
					wheels_turn_stay(LEFT);
					SLEEP(_90DRT);
					wheels_turn_stay(LEFT);
					SLEEP(_90DRT);
					wheel_act(ALL_WHEELS, FORWARD);
				}
			}
		}
		else wheel_act(ALL_WHEELS, FORWARD);
	}
}


void handle_move_action(uint8_t ACTION)
{
	switch(ACTION)
	{
		case LEFT:
		if(cur_dir != COAST && cur_dir != BRAKE)
		wheels_turn(LEFT, cur_dir);
		break;
		
		case RIGHT:
		if(cur_dir != COAST && cur_dir != BRAKE)
		wheels_turn(RIGHT, cur_dir);
		break;

		case FORWARD:
		wheel_act(ALL_WHEELS, cur_dir = FORWARD);
		break;

		case BACKWARD:
		wheel_act(ALL_WHEELS, cur_dir = BACKWARD);
		break;
		
		case FORWARD_1STEP:
		step(ALL_WHEELS, POSITIVE);
		break;
		
		case BACKWARD_1STEP:
		step(ALL_WHEELS, NEGATIVE);
		break;
		
		case LEFT_STAY:
		wheels_turn_stay(LEFT);
		break;
		
		case RIGHT_STAY:
		wheels_turn_stay(RIGHT);
		break;

		case COAST:
		wheel_act(ALL_WHEELS, cur_dir = COAST);
		break;
		
		case BRAKE:
		wheel_act(ALL_WHEELS, cur_dir = BRAKE);
		cur_dir = -1;
		break;
		
		default:
		break;
	}
}

void handle_look_action(uint8_t ANGLE)
{
	if(head_rotate(ANGLE) != 0);
}

void handle_datarequest_action(uint8_t ACTION)
{
	// sample size will decide precision of small distance obstacles
	uint16_t data;

	switch(ACTION)
	{
		case REQUEST_OBSTACLE_DISTANCE:
		
		data = read_sonar_precise();
		
		bt_send_byte(data);
		bt_send_byte(data >> 8);

		default:
		break;
	}
}


void handle_perform_action(uint8_t ACTION)
{
	switch(ACTION){
		case PERFORMANCE1:
		head_rotate(180);
		wheel_act(ALL_WHEELS, FORWARD);
		SLEEP(1000);
		
		head_rotate(135);
		wheel_act(LEFT_WHEELS, COAST);
		SLEEP(300);
		
		head_rotate(0);
		wheel_act(LEFT_WHEELS, BACKWARD);
		SLEEP(150);
		
		head_rotate(90);
		wheel_act(ALL_WHEELS, BRAKE);
		break;
		
		case PERFORMANCE2:
		head_rotate(0);
		wheel_act(ALL_WHEELS, FORWARD);
		SLEEP(1000);
		
		wheel_act(ALL_WHEELS, BRAKE);
		
		head_rotate(0);
		SLEEP(500);
		head_rotate(180);
		SLEEP(500);
		head_rotate(0);
		SLEEP(500);
		head_rotate(90);
		SLEEP(500);
		break;
		
		default:
		break;
	}
}