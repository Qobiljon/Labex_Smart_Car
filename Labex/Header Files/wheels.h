#ifndef WHEELS_H_
#define WHEELS_H_



// ALIASES
#define OUT PORTA
#define DDROUT DDRA
// MOTOR DRIVER PINOUT
#define ENABLE_LEFT_WHEEL 0
#define ENABLE_RIGHT_WHEEL 1
#define IN1 3
#define IN2 5
#define IN3 4
#define IN4 2
// WHEELS
#define ALL_WHEELS 0
#define LEFT_WHEELS 1
#define RIGHT_WHEELS 2
// ACTIONS
#define BRAKE 0
#define COAST 1
#define FORWARD 2
#define BACKWARD 3
#define RIGHT 4
#define LEFT 5
#define FORWARD_1STEP 6
#define BACKWARD_1STEP 7
#define RIGHT_STAY 8
#define LEFT_STAY 9
#define STEP_LEN 400


void wheels_init(uint8_t);

void wheel_act(uint8_t, uint8_t);

void wheels_turn_stay(uint8_t);

void wheels_turn(uint8_t, uint8_t);

void motor_offline_check();

void step(uint8_t, uint8_t);



#endif