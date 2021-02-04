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

void instructionSend(uint8_t str_data, uint8_t accel_data, uint8_t dir_data);

void set_RTS_flag(bool flag_val);
bool check_RTS_flag();


#endif /* CONTROLSEND_H_ */