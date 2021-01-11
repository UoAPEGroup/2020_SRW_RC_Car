/*
 * timer0.h
 *
 * Created: 9/12/2020 12:03:00 pm
 *  Author: achu072
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

void timer0_init(uint8_t period, uint8_t duty_cycle);
void timer0_set_OCR0B(uint8_t value);



#endif /* TIMER0_H_ */