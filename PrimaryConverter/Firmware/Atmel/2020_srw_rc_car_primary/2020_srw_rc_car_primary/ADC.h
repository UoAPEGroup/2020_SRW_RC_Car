/*
 * adc.h
 *
 * Created: 12/10/2020 9:55:25 AM
 *  Author: Kimsong Lor
 */ 

#define ADC0 0 //adc channel 0
#define ADC1 1 //adc channel 1
#define ADC2 2 //adc channel 2
#define ADC3 3 //adc channel 3
#define ADC4 4 //adc channel 4

#define SAMPLING_SIZE 10

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

//ADC read counters
uint8_t voltage_counter = 0;
uint8_t current_counter = 0;
uint8_t temp1_counter = 0;
uint8_t temp2_counter = 0;
uint8_t temp3_counter = 0;

//ADC read arrays
uint8_t adc_voltage[SAMPLING_SIZE];
uint8_t adc_current[SAMPLING_SIZE];
uint8_t adc_temp1[SAMPLING_SIZE];
uint8_t adc_temp2[SAMPLING_SIZE];
uint8_t adc_temp3[SAMPLING_SIZE];

void adc_init();
uint16_t adc_read(uint8_t channel);
uint32_t adc_convert(uint16_t raw_ADC); //convert the raw adc value to original value by multiplying with Vstep

#endif /* ADC_H_ */