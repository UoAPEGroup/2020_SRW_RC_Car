/*
 * adc.c
 *
 * Created: 17/12/2020 12:52:36 PM
 *  Author: Manoj
 */ 

void adc_init() {
	ADMUX |= (1<<REFS0);
}