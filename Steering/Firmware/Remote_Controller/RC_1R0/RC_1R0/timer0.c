/*
 * timer0.c
 *
 * Created: 12/01/2021 11:27:03 AM
 *  Author: htom380
 */ 

void timer0_init(){
	
	TCCR0A |= (1 << WGM01);															// Set Timer to CTC mode
	TCCR0B |= (1 << CS01) | (1 << CS00);												// Set prescaler to 64
	OCR0A = 124;																		// Set timer overflow at 1ms
	
}