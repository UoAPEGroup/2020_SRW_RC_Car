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

uint8_t str_data_conversion();
void accel_data_conversion();

void instructionSend();
uint8_t get_instruction_byte();

void set_RTS_flag(bool flag_val);
bool check_RTS_flag();


#endif /* CONTROLSEND_H_ */