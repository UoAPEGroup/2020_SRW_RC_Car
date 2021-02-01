/*
 * pi_c.h
 *
 * Created: 18/01/2021 11:39:30 am
 *  Author: npat692
 */ 


#ifndef PI_C_H_
#define PI_C_H_

#include "global.h"
#include "adc_pwm.h"

#define MAX_LIMIT 5000
#define MIN_LIMIT 0

float k_p;
float k_i;
volatile int16_t error;
volatile int16_t prevError;
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

#endif /* PI_C_H_ */