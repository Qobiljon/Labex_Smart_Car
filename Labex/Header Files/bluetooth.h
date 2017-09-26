#ifndef BLUETOOTH_H
#define BLUETOOTH_H



// UART DEFINITIONS
#define BAUD 9600
#define MYBAUD F_CPU/16/BAUD-1


void bluetooth_init();

uint8_t bt_receive_byte();

void bt_send_byte(uint8_t);

void bt_send_string(char*, uint8_t);

uint8_t bt_receive_string(char*);



#endif