/*
 * 2020_srw_rc_car_primary.c
 *
 * Created: 9/12/2020 10:48:31 am
 * Author : Andrey Chukhraev & Kimsong L
 or
 */ 

#include "common.h"

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "io.h"
#include "led.h"
#include "timer_control.h"
#include "adc.h"
#include "usart0.h"

int main(void)
{	
	//wdt_reset();
																																											
	io_init();
	adc_init();
	usart0_init(9600);
	sei();
	
	//test
	usart0_transmit_start_up_msg();	
	
	usart0_set_TX_reset_flag();
	usart0_clr_TX_send_data_flag();
	timer_control_update_next_duty(0);						//ramp duty cycle down to zero first
	timer_control_init();
	
	usart0_set_TX_send_data_flag();																						//ask user to confirm system is ready to start by pressing a button	
	//test
	
    while (1) 
    {	
		//cli();
		//wdt_reset();
		//wdt_enable(WDTO_8S);																								//enable watchdog timer with 8s time-out
		//sei();
		
		if (adc_get_full_flag()) {																							//if all 50 ADC samples have been taken -> convert data -> average each channel
			adc_clr_full_flag();
			adc_convert_all();
			adc_make_averages();																							
		}		
		
		if (usart0_get_TX_reset_flag()) {																					//check if user entered a RESET command
			usart0_clr_TX_reset_flag();
			if (get_overV_flag() || get_overC_flag() || get_overT1_flag() || get_overT2_flag() || get_overT3_flag()) {		//if any safety flags set -> halt instead -> show halt message and over v, i, t1, t2 or t3 
				halt_safety_function();											
			} else {
				usart0_transmit_reset_msg();																				//if no safety flag triggered -> transmit reset message
			}
		} else if (usart0_get_TX_timer_flag()) {																			//check if time to transmit data via usart
			usart0_clr_TX_timer_flag();
			if (usart0_get_TX_send_data_flag()) {																			//if user requested data transmission with BEGIN command -> transmit data
				
				usart0_transmit_data();
				usart0_transmit_pwmtest();											
			}
		}		
		
		//wdt_reset();
	}
}

