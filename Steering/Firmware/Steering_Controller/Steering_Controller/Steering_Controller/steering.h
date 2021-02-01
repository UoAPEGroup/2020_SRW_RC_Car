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

#endif /* STEERING_H_ */