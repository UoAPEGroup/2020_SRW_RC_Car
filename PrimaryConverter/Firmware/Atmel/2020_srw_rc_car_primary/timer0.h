/*
 * timer0.h
 *
 * Created: 9/12/2020 12:03:00 pm
 *  Author: Andrey Chukhraev
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

void timer0_init(uint8_t period);
void timer0_set_OCR0B(uint8_t value);



#endif /* TIMER0_H_ */