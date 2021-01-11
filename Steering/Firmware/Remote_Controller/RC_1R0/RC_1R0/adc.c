/*
 * adc.c
 *
 * Created: 12/01/2021 11:13:15 AM
 *  Author: htom380
 */ 

// ADC Initialisation (Boot)
void adc_init() {
	
	ADCSRA |= (1 << ADEN);					// Enable ADC
	ADCSRA |= (1 << ADATE);					// Enable Auto Trigger conversion mode
	ADCSRA |= (1 << ADIE);					// Enable ADC interrupt when conversions are complete
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0);	// Set input clock frequency prescaler value of 32 (8MHz/64 = 250KHz)
	
	ADCSRB |= (1 << ADTS1) | (1 << ADTS0);	// Set Timer0 Compare Match A as event for ADC Auto trigger
	
	DIDR0 = 0xff;							// Disable digital input buffer (Must be written to logic 1)
}

void adc_read(uint8_t channel) {
	
}