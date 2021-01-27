/*
 * adc.h
 *
 * Created: 12/10/2020 9:55:25 AM
 *  Author: Kimsong Lor
 */ 

#define V_ref 3300 //reference voltage 3300mV (Vcc)
#define A_int 1024 //amplitude interval 2^10 = 1024

#define rated_V 1000 //3000mV
#define rated_C 1000 //3000mV (needs changes)
#define rated_T1 1000 //3000mV (needs changes)
#define rated_T2 1000 //3000mV (needs changes)
#define rated_T3 1000 //3000mV (needs changes)

#define ADC_used 5 //number of adc channels in use

#define ADC_V 6 //adc channel 6, voltage
#define ADC_C 5 //adc channel 5, current
#define ADC_T1 2 //adc channel 2, temp1
#define ADC_T2 3 //adc channel 3, temp2
#define ADC_T3 4 //adc channel 4, temp3

#define SAMPLING_SIZE 10

#define TIMER1_COMPB_CLR TIFR1 |= (1 << OCF1B)	//clear timer1 overflow flag

#define ADC_CH_CLR				ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0))		//ADC0 -> clear MUX[2:0]
#define ADC_CH_TEMP1			ADMUX |= (1 << MUX1)									//ADC2
#define ADC_CH_TEMP2			ADMUX |= ((1 << MUX1) | (1 << MUX0))					//ADC3
#define ADC_CH_TEMP3			ADMUX |= (1 << MUX2)									//ADC4
#define ADC_CH_ISENS1			ADMUX |= ((1 << MUX2) | (1 << MUX0))					//ADC5
#define ADC_CH_VSENS1			ADMUX |= ((1 << MUX2) | (1 << MUX1))					//ADC6
#define ADC_ENABLE				ADCSRA |= (1 << ADEN)									//enable ADC
#define ADC_DISABLE				ADCSRA &= ~(1 << ADEN)									//disable ADC

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init();
uint16_t adc_read(uint8_t channel);
uint32_t adc_convert_mV(uint16_t raw_ADC); //convert the raw adc value to original value by multiplying with Vstep
void reset_counters();

void adc_readings_average(); //calculate the average values from their respective array of adc readings
void get_adc_averages(uint32_t *arr); //get the array of average values from the adc readings

#endif /* ADC_H_ */