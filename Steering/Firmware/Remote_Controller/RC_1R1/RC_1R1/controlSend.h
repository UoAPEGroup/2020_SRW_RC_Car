/*
 * controlSend.h
 *
 * Created: 18/01/2021 2:48:37 PM
 *  Author: htom380
 */ 


#ifndef CONTROLSEND_H_
#define CONTROLSEND_H_

#include "global.h"
#include <stdbool.h>

void str_data_conversion();
void accel_data_conversion();

void instructionSend();
void get_instruction_byte();

void set_RTS_flag(bool flag_val);
bool check_RTS_flag();


/***************** ACCEL. SW. MACROS ******************/

#define READ_ACCEL_SW_1 PINB & (1 << PB0)
#define READ_ACCEL_SW_2 PIND & (1 << PD6)
#define READ_ACCEL_SW_3 PIND & (1 << PD7)
#define READ_ACCEL_SW_4 PINB & (1 << PB1)

/******************************************************/

#endif /* CONTROLSEND_H_ */