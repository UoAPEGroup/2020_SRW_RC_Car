/*
 * functions.c
 *
 * Created: 12/14/2020 2:43:37 PM
 *  Author: Kimsong Lor
 */ 

#include "functions.h"
#include "adc.h"

uint8_t calc_average(uint8_t arr[]) {
	uint16_t temp = 0;
	for(uint8_t i = 0; i < SAMPLING_SIZE; i++) {
		temp = temp + arr[i];
	}
	uint8_t result = (uint8_t)(temp/SAMPLING_SIZE);
	return result;
}