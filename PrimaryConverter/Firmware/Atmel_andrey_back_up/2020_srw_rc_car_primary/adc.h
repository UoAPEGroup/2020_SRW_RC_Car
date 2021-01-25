/*
 * adc.h
 *
 * Created: 16/12/2020 10:13:53 am
 *  Author: achu072
 */ 


#ifndef ADC_H_
#define ADC_H_

//ADC macros
#define ADC_ENABLE				ADCSRA |= (1 << ADEN)									//enable ADC
#define ADC_DISABLE				ADCSRA &= ~(1 << ADEN)									//disable ADC
#define ADC_CH_CLR				ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0))		//ADC0 -> clear MUX[2:0]		
#define ADC_CH_TEMP1			ADMUX |= (1 << MUX1)									//ADC2
#define ADC_CH_TEMP2			ADMUX |= ((1 << MUX1) | (1 << MUX0))					//ADC3
#define ADC_CH_TEMP3			ADMUX |= (1 << MUX2)									//ADC4
#define ADC_CH_ISENS1			ADMUX |= ((1 << MUX2) | (1 << MUX0))					//ADC5
#define ADC_CH_VSENS1			ADMUX |= ((1 << MUX2) | (1 << MUX1))					//ADC6

#define TIMER1_COMPB_CLR		TIFR1 |= (1 << OCF1B)									//clear timer1 overflow flag						

void adc_init();
uint32_t adc_get_vsens();
uint32_t adc_get_isens();
uint32_t adc_get_temp1();
uint32_t adc_get_temp2();
uint32_t adc_get_temp3();


#endif /* ADC_H_ */