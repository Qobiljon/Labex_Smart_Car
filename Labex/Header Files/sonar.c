#include <util/atomic.h>
#include "sonar.h"
#include "../Special Files/tools.h"



volatile uint32_t overFlowCounter = 0;
volatile uint32_t trig_counter = 0;
volatile uint32_t no_of_ticks = 0;

void init_sonar() {
	TRIG_OUTPUT_MODE();     // Set Trigger pin as output
	ECHO_INPUT_MODE();      // Set Echo pin as input
}

void trigger_sonar() {
	TRIG_LOW();             // Clear pin before setting it high
	_delay_us(10);           // Clear to zero and give time for electronics to set
	TRIG_HIGH();            // Set pin high
	_delay_us(15);          // Send high pulse for minimum 10us
	TRIG_LOW();             // Clear pin
}

ISR(TIMER0_OVF_vect) {  // Timer1 overflow interrupt
	overFlowCounter++;
	TCNT0 = 0;
}

uint16_t read_sonar()
{
	uint16_t dist_in_cm = 0;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		init_sonar();                       // Setup pins and ports
		trigger_sonar();                    // send a 10us high pulse
		trig_counter = 0;

		while (!(ECHO_PIN & (1 << ECHO_BIT))) { // while echo pin is still low
			trig_counter++;
			uint32_t max_response_time = SONAR_TIMEOUT;
			if (trig_counter > max_response_time) {  // SONAR_TIMEOUT
				return TRIG_ERROR;
			}
		}

		TCNT0=0;							// reset timer
		TCCR0 |= (1 << CS00);				// start 16 bit timer with no prescaler
		TIMSK |= (1 << TOIE0);				// enable overflow interrupt on timer1
		overFlowCounter=0;                  // reset overflow counter
		sei();                              // enable global interrupts

		while ((ECHO_PIN & (1 << ECHO_BIT))) { // while echo pin is still high
			trig_counter++;
			uint32_t max_response_time = SONAR_TIMEOUT;
			if (trig_counter > max_response_time){   // SONAR_TIMEOUT
				return TRIG_ERROR;
			}
		}
		
		TCCR0 = 0x00;
		sei();
		
		no_of_ticks = ((overFlowCounter * TIMER0_MAX) + TCNT0);			// counter count
		dist_in_cm = (no_of_ticks / (CONVERT_TO_CM * CYCLES_PER_US));	// distance in cm
	}
	return (dist_in_cm);
}

uint16_t sample_sonar(uint8_t precision)
{
	uint16_t res;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		uint8_t n;

		res = read_sonar();
		for(n = 0; n < precision && (res == ECHO_ERROR || res == TRIG_ERROR || noObstacle(res)); n++)
		{
			res = read_sonar();
		}
	}
	return res;
}

uint16_t read_sonar_precise()
{
	uint16_t data;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		data = read_sonar();
		if(data == ECHO_ERROR || data == TRIG_ERROR || noObstacle(data))
		data = sample_sonar(PRESICION);
	}
	return data;
}