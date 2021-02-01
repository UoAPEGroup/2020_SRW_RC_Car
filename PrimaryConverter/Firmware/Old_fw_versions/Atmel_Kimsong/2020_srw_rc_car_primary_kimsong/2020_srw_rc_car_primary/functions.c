/*
 * functions.c
 *
 * Created: 12/14/2020 2:43:37 PM
 *  Author: Kimsong Lor
 */ 

#include "functions.h"
#include "adc.h"

uint32_t calc_average(uint32_t arr[]) {
	uint32_t temp = 0;
	for(uint8_t i = 0; i < SAMPLING_SIZE; i++) {
		temp = temp + arr[i];
	}
	uint32_t result = (uint32_t)(temp/SAMPLING_SIZE);
	return result;
}

uint32_t calc_mA(uint32_t mV) { //needs update
	return 0;
}

uint32_t cal_temp(uint32_t mV) { //needs update
	return 0;
}