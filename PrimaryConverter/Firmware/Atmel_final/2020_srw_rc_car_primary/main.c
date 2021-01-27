/*
 * 2020_srw_rc_car_primary.c
 *
 * Created: 9/12/2020 10:48:31 am
 * Author : Andrey Chukhraev & Kimsong Lor
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
	//timer_control_init();
	adc_init();
	usart0_init(9600);
	sei();
	
	usart0_transmit_start_up_msg();
	
    while (1) 
    {			
		if (usart0_get_TX_reset_flag	()) {
			usart0_clr_TX_reset_flag();
			usart0_transmit_reset_msg();
		} else if (usart0_get_TX_timer_flag()) {
			usart0_clr_TX_timer_flag();
			if (usart0_get_TX_send_data_flag()) {
				usart0_transmit_data();
				usart0_transmit_pwmtest();
			}
		}
	}
}

