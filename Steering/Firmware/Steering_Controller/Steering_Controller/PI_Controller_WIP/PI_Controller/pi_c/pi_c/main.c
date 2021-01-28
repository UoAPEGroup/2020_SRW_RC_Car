/*
 * pi_c.c
 *
 * Created: 18/01/2021 10:52:43 am
 * Author : npat692
 */ 

#include "global.h"
#include "setup.h"
#include "pi_c.h"
#include "adc_pwm.h"
#include "uart.h"

#include <stdio.h>
#include <string.h>

char input_buffer[20];
uint16_t adc_1;


ISR(TIMER2_COMPA_vect){
	//loop();
	adc_1 = adc_read();
	sprintf(input_buffer, "Input:	%i \n\r", adc_1);
	usart0_transmit_string(input_buffer);
}

int main(void)
{
	led_init();
	pwm_init();
	adc_init();
	timer2_init();
	setup();
	usart0_init(9600);
	sei();
    /* Replace with your application code */
    while (1) {
		//analog_write(4000);
		//adc_1 = adc_read();
		//_delay_ms(1000);
		
		
    }
}

