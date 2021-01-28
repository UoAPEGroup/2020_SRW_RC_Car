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
#include "led.h"
#include "timer_control.h"
#include "adc.h"
#include "usart0.h"

int main(void)
{
	io_init();
	adc_init();
	usart0_init(9600);
	sei();
	
	usart0_transmit_start_up_msg();
	
    while (1) 
    {	
		if (adc_get_full_flag()) {
			adc_clr_full_flag();
			adc_convert_all();
			adc_make_averages();
		}		
		
		if (usart0_get_TX_reset_flag()) {
			usart0_clr_TX_reset_flag();
			if (get_overV_flag() || get_overC_flag() || get_overT1_flag() || get_overT2_flag() || get_overT3_flag()) {
				halt_safety_function();											
			} else {
				usart0_transmit_reset_msg();
			}
		} else if (usart0_get_TX_timer_flag()) {
			usart0_clr_TX_timer_flag();
			if (usart0_get_TX_send_data_flag()) {
				usart0_transmit_data();
				usart0_transmit_pwmtest();
			}
		}
	}
}

