/*
 * timer1.c
 *
 * Created: 12/15/2020 1:10:37 PM
 *  Author: Kimsong Lor
 */ 

void timer1_init() {
	TCCR1B |= (1<<WGM12); //CTC mode OCR1A as top
	TCCR1B |= (1<<CS11) | (1<<CS10); //64 prescaling
	
	TIMSK1 |= (1<<TOIE1); //Overflow Interrupt Enable
	
	OCR1A = 51; //0.1us overflow time
}