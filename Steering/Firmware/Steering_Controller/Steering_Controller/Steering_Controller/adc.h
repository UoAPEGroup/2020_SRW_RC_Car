/*
 * adc.h
 *
 * Created: 11/01/2021 10:06:01 am
 *  Author: npat692
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "global.h"

volatile uint16_t adc_val;

void adc_init();
uint16_t adc_read();

#endif /* ADC_H_ */