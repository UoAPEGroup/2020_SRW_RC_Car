/*
 * 2020_srw_rc_car_primary.c
 *
 * Created: 9/12/2020 10:48:31 am
 * Author : Andrey Chukhraev
 */ 

#include "common.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "io.h"
#include "timer_control.h"
#include "adc.h"
#include "usart0.h"

int main(void)
{
	io_init();
	timer_control_init();
	adc_init();
	usart0_init(9600);
	sei();
	
    while (1) 
    {
		if (usart0_get_TX_flag()) {
			usart0_clr_TX_flag();
				if (usart0_get_TX_data_flag()) {
					usart0_transmit_data(1, 2, 3, 4, 5);
					usart0_transmit_pwmtest();
				}
		}
	}
}

