/*
 * pi_controller.h
 *
 * Created: 28/01/2021 4:18:25 pm
 *  Author: npat692
 */ 


#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_

#include "global.h"
#include "adc.h"
#include "led.h"
#include "pwm.h"

float k_p;
float k_i;

volatile int16_t error;
volatile int16_t prev_error;
volatile int16_t input;
volatile int16_t integrator;
volatile int16_t set_output;

void pi_setup();
void pi_controller();
void printval();
int16_t compute_pi(uint16_t input);

#endif /* PI_CONTROLLER_H_ */