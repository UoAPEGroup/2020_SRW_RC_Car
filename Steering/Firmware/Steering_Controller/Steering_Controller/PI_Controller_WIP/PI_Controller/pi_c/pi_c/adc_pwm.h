/*
 * adc_pwm.h
 *
 * Created: 18/01/2021 11:51:48 am
 *  Author: npat692
 */ 


#ifndef ADC_PWM_H_
#define ADC_PWM_H_


#include "global.h"

uint16_t adc_read();

void analog_write(int16_t value);

#endif /* ADC_PWM_H_ */