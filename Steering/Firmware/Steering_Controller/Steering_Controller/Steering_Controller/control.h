/*
 * control.h
 *
 * Created: 12/01/2021 6:45:52 p.m.
 *  Author: npat692
 */ 


#ifndef CONTROL_H_
#define CONTROL_H_

#include "global.h"
#include "uart.h"
#include "led.h"
#include "steering.h"

// OUTPUT PIN INITIALIZATION
void pin_init();

// MAIN READER FUNCTION
void read_data();

// READER AND SETTER FUNCTIONS
void set_direction();
void set_speed();
void set_turn_angle();

// SPEED CONTROL SETTER FUNCTIONS
void set_no_speed();
void set_low_speed();
void set_med_speed();
void set_high_speed();

// SPEED BITS
#define LOW_H (input_data & (1 << 0))
#define MED_H (input_data & (1 << 1))
#define HIGH_H (input_data & (1 << 2))

// DIRECTION BITS
#define BACKWARD_H (input_data & (1 << 3))

// TURN BITS
#define RIGHT_H (input_data & (1 << 4))
#define HALF_TURN_H (input_data & (1 << 5))
#define FULL_TURN_H (input_data & (1 << 6))


#endif /* CONTROL_H_ */