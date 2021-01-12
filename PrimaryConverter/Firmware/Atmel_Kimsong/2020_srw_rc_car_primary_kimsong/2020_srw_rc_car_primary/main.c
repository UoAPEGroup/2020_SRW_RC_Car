/*
 * 2020_srw_rc_car_primary.c
 *
 * Created: 9/12/2020 10:48:31 am
 * Author : Andrey Chukhraev
 */ 

#include "common.h"
#include "usart0.h"
#include "adc.h"
#include "timer1.h"

#include <avr/io.h>

int main(void)
{
	uint32_t adc_averages[] = {0};
	
	timer1_init();
	void adc_init();
	usart0_init(9600);
	
    while (1) {
		usart0_transmit_data(get_adc_averages(adc_averages)); //needs check
    }
}

