/*
 * calc.h
 *
 * Created: 11/01/2021 11:25:13 am
 *  Author: achu072
 */ 


#ifndef CALC_H_
#define CALC_H_

uint8_t calc_make_duty_cycle(uint8_t *buffer);
uint8_t calc_make_OCRnB(uint8_t period, uint8_t duty_cycle);
uint8_t calc_ascii_to_num(uint8_t ascii);



#endif /* CALC_H_ */