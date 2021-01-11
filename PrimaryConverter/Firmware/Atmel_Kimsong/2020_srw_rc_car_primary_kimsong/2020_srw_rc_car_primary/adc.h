/*
 * adc.h
 *
 * Created: 12/10/2020 9:55:25 AM
 *  Author: Kimsong Lor
 */ 

#define V_ref 3300 //reference voltage 3300mV (Vcc)
#define A_int 1024 //amplitude interval 2^10 = 1024

#define ADC_used 5 //number of adc channels in use

#define ADC0 0 //adc channel 0
#define ADC1 1 //adc channel 1
#define ADC2 2 //adc channel 2
#define ADC3 3 //adc channel 3
#define ADC4 4 //adc channel 4

#define SAMPLING_SIZE 10

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init();
uint16_t adc_read(uint8_t channel);
uint32_t adc_convert(uint16_t raw_ADC); //convert the raw adc value to original value by multiplying with Vstep

void adc_readings_average(); //calculate the average values from their respective array of adc readings
void get_adc_averages(uint8_t *arr[]); //get the array of average values from the adc readings

#endif /* ADC_H_ */