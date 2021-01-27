/*
 * functions.h
 *
 * Created: 12/14/2020 2:50:23 PM
 *  Author: Kimsong Lor
 */ 

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdint.h>

uint32_t calc_average(uint32_t *arr); //calculate the average value of the values in an array
uint32_t calc_mA(uint32_t mV); //calculate mA value with use of mV value from adc read/convert functions
uint32_t cal_temp(uint32_t mV); //calculate temp(degree) value with use of mV value from the adc read/convert functions

#endif /* FUNCTIONS_H_ */