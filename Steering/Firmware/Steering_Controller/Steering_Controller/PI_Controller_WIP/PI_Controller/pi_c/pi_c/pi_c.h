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


float k_p;
float k_i;

int16_t error;
int16_t prevError;
int16_t sampling_t;
int16_t input; 
int16_t output;
int16_t integrator;
int16_t output_1;
int16_t setPoint;

void setup();
void loop();
uint16_t computePID(uint16_t input);

#endif /* PI_C_H_ */