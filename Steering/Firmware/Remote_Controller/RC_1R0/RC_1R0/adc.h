/*
 * adc.h
 *
 * Created: 11/01/2021 11:58:59 PM
 *  Author: htom380
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "global.h"

#define AREF 3300
#define ADC_RES 1024

void adc_init();
uint32_t adc_convert(uint16_t adc_val);

uint16_t adc_read(uint8_t channel);


#endif /* ADC_H_ */