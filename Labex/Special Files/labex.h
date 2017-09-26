#ifndef LABEX_H_
#define LABEX_H_



// MODES: AUTOPILOT, HANDDRIVEN
#define MODE_HANDDRIVEN 0
#define MODE_AUTOPILOT 1
#define REQUEST_OBSTACLE_DISTANCE 0
// AUTO MODES: 
#define AUTOMODE_RIGHTHANDRULE 0
#define AUTOMODE_FORWARDRULE 1
// ACTIONS + SUBACTIONS + DIRECTIONS
#define ACTION_MOVE 0
#define ACTION_LOOK 1
#define ACTION_PERFORM 2
#define ACTION_CHANGEMODE 3
#define ACTION_DATAREQUEST 4
// PERFORMANCES
#define PERFORMANCE1 0
#define PERFORMANCE2 1


volatile uint8_t control_mode;

void manual_control();

void artificial_control();


void handle_move_action(uint8_t);

void handle_look_action(uint8_t);

void handle_perform_action(uint8_t);

void handle_datarequest_action(uint8_t);



#endif