/*
 * steering.h
 *
 * Created: 21/01/2021 11:22:18 am
 *  Author: npat692
 */ 


#ifndef STEERING_H_
#define STEERING_H_

#include "global.h"
#include "adc.h"
#include "pwm.h"
#include "led.h"

void calibrate_steering();
void find_ref();
void set_reference_values();
 
volatile uint16_t min_val;
volatile uint16_t max_val;
volatile uint8_t calibration_flag;

void set_half_r_turn();
void set_full_r_turn();
void set_half_l_turn();
void set_full_l_turn();
void set_straight_turn();

#endif /* STEERING_H_ */