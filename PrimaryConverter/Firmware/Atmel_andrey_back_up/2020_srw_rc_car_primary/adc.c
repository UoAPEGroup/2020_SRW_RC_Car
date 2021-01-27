/*
 * adc.c
 *
 * Created: 12/10/2020 9:55:45 AM
 * Author: Kimsong Lor
 */ 

#include "adc.h"
#include "functions.h"
#include "usart0.h"
#include "led.h"

//ADC read counters
volatile uint8_t voltage_counter = 0;
volatile uint8_t current_counter = 0;
volatile uint8_t temp1_counter = 0;
volatile uint8_t temp2_counter = 0;
volatile uint8_t temp3_counter = 0;

//ADC transfer booleans
bool adc_full = false; //set all booleans to false 

//ADC read arrays
uint32_t adc_voltage[SAMPLING_SIZE]; //mV
uint32_t adc_current[SAMPLING_SIZE]; //mA
uint32_t adc_temp1[SAMPLING_SIZE]; //mV
uint32_t adc_temp2[SAMPLING_SIZE]; //mV
uint32_t adc_temp3[SAMPLING_SIZE]; //mV
uint32_t adc_averages[ADC_used] = {0}; // voltage[0], current[1], temp1[2], temp2[3], temp3[4]

ISR(ADC_vect) {
	if (adc_full == false) {
		if (voltage_counter < SAMPLING_SIZE) {
			TIMER1_COMPB_CLR;
			adc_voltage[voltage_counter] = adc_convert_mV(ADC);
			//check for rated value and cut (check max value)
			if (adc_voltage[voltage_counter] >= rated_V) {
				reset_counters(); 
				//call PWM shutdown function
			}
			voltage_counter++;
			
			if (voltage_counter == 10) {
				ADC_CH_CLR;
				ADC_CH_ISENS;
			}
		}
		else if (current_counter < SAMPLING_SIZE) {
			TIMER1_COMPB_CLR;
			adc_current[current_counter] = adc_convert_mV(ADC); //conversion for mA, needs adjustment
			//check for rated value and cut
			if (adc_voltage[voltage_counter] >= rated_C) {
				reset_counters(); 
				//call PWM shutdown function
			}
			current_counter++;
			
			if (current_counter == 10) {
				ADC_CH_CLR;
				ADC_CH_TEMP1;
			}
		}
		else if (temp1_counter < SAMPLING_SIZE) {
			TIMER1_COMPB_CLR;
			adc_temp1[temp1_counter] = adc_convert_mV(ADC); //conversion for temp different, needs adjustment
			//check for rated value and cut
			if (adc_voltage[voltage_counter] >= rated_T1) {
				reset_counters(); 
				//call PWM shutdown function
			}
			temp1_counter++;
			
			if (temp1_counter == 10) {
				ADC_CH_CLR;
				ADC_CH_TEMP2;
			}
		}
		else if (temp2_counter < SAMPLING_SIZE) {
			TIMER1_COMPB_CLR;
			adc_temp2[temp2_counter] = adc_convert_mV(ADC); //conversion for temp different, needs adjustment
			//check for rated value and cut
			if (adc_voltage[voltage_counter] >= rated_T2) {
				reset_counters(); 
				//call PWM shutdown function
			}
			temp2_counter++;
			
			if (temp2_counter == 10) {
				ADC_CH_CLR;
				ADC_CH_TEMP3;
			}
		}
		else if (temp3_counter < SAMPLING_SIZE) {
			TIMER1_COMPB_CLR;
			adc_temp3[temp3_counter] = adc_convert_mV(ADC); //conversion for temp different, needs adjustment
			//check for rated value and cut
			if (adc_voltage[voltage_counter] >= rated_T3) {
				reset_counters(); 
				//call PWM shutdown function
			}
			temp3_counter++;
			
			if (temp3_counter == 10) {
				ADC_CH_CLR;
				ADC_CH_VSENS;
			}
		}
		else {
			TIMER1_COMPB_CLR;
			//flag for processing
			ADC_DISABLE;
			adc_full = true;
			set_adc_average();
			led_on();
		}
	}
}

void adc_init() {
	ADMUX |= (1<<REFS0); //Reference voltage selected to be AVCC
	
	ADCSRA |= (1<<ADEN); //ADC enabled
	ADC_CH_VSENS;		//set start channel to vsens
	ADCSRA |= (1<<ADATE); //ADC auto trigger enabled
	ADCSRA |= (1<<ADIE); //ADC interrupt enabled
	ADCSRA |= (1<<ADPS2) | (1<<ADPS0); //ADC prescaler = 32, system clock = 8Mhz, adc clock = 250kHz
	
	ADCSRB |= (1<<ADTS2) | (1<<ADTS0); //ADC auto trigger source = Timer/Counter1 compare match B
}

uint16_t adc_read(uint8_t channel) {
	ADMUX &= ~( (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0) ); //clearing MUX register
	ADMUX |= channel; //select the adc channel
	
	return ADC; //return the ADC value from the ADCL and ADCH registers
}

//convert the raw adc value to original value by multiplying with Vstep in mV
uint32_t adc_convert_mV(uint16_t raw_ADC) {  
	uint32_t original_V = (raw_ADC*V_ref)/A_int;  //reference voltage, amplitude interval
	return original_V;							
}

void reset_counters() {
	//reset all counters to 0
	voltage_counter = 0;
	current_counter = 0;
	temp1_counter = 0;
	temp2_counter = 0;
	temp3_counter = 0;
}

void set_adc_average() {
	if (adc_full == true) {
		adc_averages[ADC_V] = calc_average(adc_voltage);
		adc_averages[ADC_C] = calc_average(adc_current);
		adc_averages[ADC_T1] = calc_average(adc_temp1);
		adc_averages[ADC_T2] = calc_average(adc_temp2);
		adc_averages[ADC_T3] = calc_average(adc_temp3);
		
		//set adc_full back to false to get new adc readings
		adc_full = false;
		reset_counters();
		ADC_ENABLE;
	}
}

void get_adc_averages(uint32_t *arr) {
	//set_adc_average();
	for (uint8_t i = 0; i < ADC_used; i++) {
		
		
		
		arr[i] = adc_averages[i];
	}
}