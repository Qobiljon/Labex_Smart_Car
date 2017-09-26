#ifndef TOOLS_H_
#define TOOLS_H_



// MACROS
#define SLEEP(MILLIS) _delay_ms(MILLIS);
// BINARY
#define HIGH 1
#define LOW 0
#define TRUE 1
#define FALSE 0
// BINARY
#define POSITIVE 0
#define NEGATIVE 1
#define NEUTRAL 2
// TOGGLE DEFINITION
#define BIT_TOGGLE(REG, IND, VALUE) (VALUE ? (REG |= 1 << IND) : (REG &= ~(1 << IND)))


uint8_t noObstacle(uint16_t);



#endif