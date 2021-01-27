/*
 * calc.h
 *
 * Created: 11/01/2021 11:25:13 am
 *  Author: Andrey Chukhraev & Kimsong Lor
 */ 


#ifndef CALC_H_
#define CALC_H_

uint8_t calc_make_duty_cycle(uint8_t *buffer);
uint8_t calc_make_OCRnB(uint8_t period, uint8_t duty_cycle);
uint8_t calc_ascii_to_num(uint8_t ascii);

/*from Kimsong's functions.h below this line*/
uint32_t calc_make_average(uint32_t *arr);						//calculate the average value of the values in an array
uint32_t calc_make_mA(uint32_t mV);								//calculate mA value with use of mV value from adc read/convert functions
uint32_t calc_make_temp(uint32_t mV);							//calculate temp(degree) value with use of mV value from the adc read/convert functions



#endif /* CALC_H_ */