/*
 * adc.h
 *
 * Created: 12/10/2020 9:55:25 AM
 *  Author: Kimsong Lor
 */ 

#define V_ref		3300															//reference voltage 3300mV (Vcc)
#define A_int		1024															//amplitude interval 2^10 = 1024

//threshold values for protection -> trigger halt ***UPDATE FOR FINAL IMPLEMENTATION***
#define rated_V		664																//~60V
#define rated_C		1023															//for testing only 
#define rated_T1	1023															//for testing only 
#define rated_T2	1023															//for testing only 
#define rated_T3	1023															//for testing only 

#define ADC_used	5																//number of adc channels in use

#define ADC_V		6																//adc channel 6, voltage
#define ADC_C		5																//adc channel 5, current
#define ADC_T1		2																//adc channel 2, temp1
#define ADC_T2		4																//adc channel 4, temp2
#define ADC_T3		3																//adc channel 3, temp3

#define SAMPLING_SIZE 10

#define VOLTAGE_POS	0
#define CURRENT_POS	1
#define TEMP1_POS	2
#define TEMP2_POS	3
#define TEMP3_POS	4

#define TIMER1_COMPB_CLR TIFR1 |= (1 << OCF1B)										//clear timer1 overflow flag

#define ADC_CH_CLR			ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0))		//ADC0 -> clear MUX[2:0]
#define ADC_CH_TEMP1		ADMUX |= (1 << MUX1)									//ADC2
#define ADC_CH_TEMP2		ADMUX |= ((1 << MUX1) | (1 << MUX0))					//ADC3
#define ADC_CH_TEMP3		ADMUX |= (1 << MUX2)									//ADC4
#define ADC_CH_ISENS		ADMUX |= ((1 << MUX2) | (1 << MUX0))					//ADC5
#define ADC_CH_VSENS		ADMUX |= ((1 << MUX2) | (1 << MUX1))					//ADC6
#define ADC_ENABLE			ADCSRA |= (1 << ADEN)									//enable ADC
#define ADC_DISABLE			ADCSRA &= ~(1 << ADEN)									//disable ADC

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init();
uint16_t adc_read(uint8_t channel);
void adc_convert_all();																//convert the raw adc value to original value by multiplying with Vstep
void adc_reset_counters();

void adc_make_averages();

void halt_safety_function();
																					//calculate the average values from their respective array of adc readings
uint32_t adc_get_avg_voltage();														//getters for average values
uint32_t adc_get_avg_current();
uint32_t adc_get_avg_temp1();
uint32_t adc_get_avg_temp2();
uint32_t adc_get_avg_temp3();

void adc_make_averages();															//fill array of ADC average values
bool adc_get_full_flag();
void adc_clr_full_flag();

void set_overV_flag();
bool get_overV_flag();
void clr_overV_flag();

void set_overC_flag();
bool get_overC_flag();
void clr_overC_flag();

void set_overT1_flag();
bool get_overT1_flag();
void clr_overT1_flag();

void set_overT2_flag();
bool get_overT2_flag();
void clr_overT2_flag();

void set_overT3_flag();
bool get_overT3_flag();
void clr_overT3_flag();


#endif /* ADC_H_ */