#ifndef HEAD_H_
#define HEAD_H_



// SERVO CONSTANTS
/*#define DEFAULT_ANGLE 1255
#define R90_ANGLE 530
#define L90_ANGLE 2250*/
/*#define DEFAULT_ANGLE 1425
#define R90_ANGLE 600
#define L90_ANGLE 2425*/
#define DEFAULT_ANGLE 1525
#define L90_ANGLE 650
#define R90_ANGLE 2400


void servo_init();

uint8_t head_rotate(uint8_t);

uint8_t head_look(uint8_t);



#endif