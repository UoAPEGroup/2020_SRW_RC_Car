/*
 * pi_controller.h
 *
 * Created: 28/01/2021 4:18:25 pm
 *  Author: npat692
 */ 


#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_

#include "global.h"
#include "adc_pwm.h"

#define MAX_LIMIT 5000
#define MIN_LIMIT 0

float k_p;
float k_i;

volatile int16_t error;
int16_t prevError;
float sampling_t;
volatile int16_t input;
volatile int16_t output;
volatile int16_t integrator;
volatile int16_t set_output;
int16_t setPoint;

void setup();
void pi_controller();
void printval();
int16_t compute_pi(uint16_t input);


#endif /* PI_CONTROLLER_H_ */