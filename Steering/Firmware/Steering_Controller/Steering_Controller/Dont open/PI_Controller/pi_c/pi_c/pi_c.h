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


uint8_t k_p;

double error;
double input; 
double output;
double setPoint;

void setup();
double computePID(double input);

#endif /* PI_C_H_ */