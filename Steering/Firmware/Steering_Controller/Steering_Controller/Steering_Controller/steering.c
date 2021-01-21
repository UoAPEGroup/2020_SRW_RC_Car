/*
 * steering.c
 *
 * Created: 21/01/2021 11:22:30 am
 *  Author: npat692
 */ 

#include "steering.h"
#include "led.h"

void turn_start(){
	led_toggle();
	while(adc_val >= 1500){
		adc_val = adc_start();
	}
}
