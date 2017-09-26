/*!
* ********************************************************************************************************
* \file sonar.h
* \brief Interfacing HC-SR04 Ultrasonic Sensor Module (Sonar)
*
* \author      :   Praveen Kumar
* \date        :   Mar 24, 2014
* Copyright(c) :   Praveen Kumar - www.veerobot.com
* Description  :   Interfacing HC-SR04 Ultrasonic Sensor Module (Sonar). Program is tested on
*                  Draco - AVR Development board available at www.veerobot.com/store which has an
*                  ATmega328P microcontroller. If you replace that with any other 28 pin AVR
*                  microcontroller, be sure to modify registers accordingly.
*
* LICENSE      :   Redistribution and use in source and/or binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* - Redistributions of source code must retain this copyright notice, list of conditions and disclaimer.
* - Redistributions in binary form must reproduce this copyright notice, list of conditions and disclaimer in
*      documentation and/or other materials provided with the distribution.
*
* DISCLAIMER   :   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" WITHOUT ANY
* KIND OF WARRANTIES. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE
*
* ********************************************************************************************************
*/
#ifndef SONAR_H_
#define SONAR_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*...- . . .-. --- -... --- -
* Define Ports and Pins as required
* Modify Maximum response time and delay as required
* MAX_RESP_TIME : default: 300
* DELAY_BETWEEN_TESTS : default: 50
*/
#define TRIG_DDR    DDRD            // Trigger Port
#define TRIG_PORT   PORTD
#define TRIG_PIN    PIND
#define TRIG_BIT    PD0             // Trigger Pin

#define ECHO_DDR    DDRD            // Echo Port
#define ECHO_PORT   PORTD
#define ECHO_PIN    PIND
#define ECHO_BIT    PD1             // Echo Pin

// Speed of sound
// Default: 343 meters per second in dry air at room temperature (~20C)
#define SPEED_OF_SOUND  343
#define MAX_SONAR_RANGE 2           // This is trigger + echo range (in meters) for SR04
#define DELAY_BETWEEN_TESTS 500     // Echo canceling time between sampling. Default: 500us
#define TIMER0_MAX 255				// 65535 for 16 bit timer and 255 for 8 bit timer

/* ...- . . .-. --- -... --- -
* Do not change anything further unless you know what you're doing
* */
#define TRIG_ERROR -1
#define ECHO_ERROR -2

#define CYCLES_PER_US (F_CPU/1000000)// instructions per microsecond
#define CYCLES_PER_MS (F_CPU/1000)      // instructions per millisecond
// Timeout. Decreasing this decreases measuring distance
// but gives faster sampling
#define SONAR_TIMEOUT ((F_CPU*MAX_SONAR_RANGE)/SPEED_OF_SOUND)

#define TRIG_INPUT_MODE() TRIG_DDR &= ~(1<<TRIG_BIT)
#define TRIG_OUTPUT_MODE() TRIG_DDR |= (1<<TRIG_BIT)
#define TRIG_LOW() TRIG_PORT &= ~(1<<TRIG_BIT)
#define TRIG_HIGH() TRIG_PORT |=(1<<TRIG_BIT)

#define ECHO_INPUT_MODE() ECHO_DDR &= ~(1<<ECHO_BIT)
#define ECHO_OUTPUT_MODE() ECHO_DDR |= (1<<ECHO_BIT)
#define ECHO_LOW() ECHO_PORT &= ~(1<<ECHO_BIT)
#define ECHO_HIGH() ECHO_PORT |=(1<<ECHO_BIT)

#define CONVERT_TO_CM ((10000*2)/SPEED_OF_SOUND)    // or simply 58

#define PRESICION 5

/** ...- . . .-. --- -... --- -
* @brief   Initiate Ports for Trigger and Echo pins
* @param   void
* @return  none
*/
void init_sonar();

/**  ...- . . .-. --- -... --- -
* @brief   Send 10us pulse on Ultrasonic Trigger pin
* @param   void
* @return  none
*/
void trigger_sonar();

/**  ...- . . .-. --- -... --- -
* @brief   Calculate and store echo time and return distance
* @param   void
* @return  unsigned int
*/
uint16_t read_sonar();

/**  ...- . . .-. --- -... --- -
* @brief   Calculate Precisely and return precise distance
* @param   void
* @return  unsigned int
*/
uint16_t sample_sonar(uint8_t);

/**  ...- . . .-. --- -... --- -
* @brief   Calculate Precisely and return precise distance
* @param   void
* @return  unsigned int
*/
uint16_t read_sonar_precise();


#endif /* SONAR_H_ */