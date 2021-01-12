/*
 * Steering_Controller.c
 *
 * Created: 11/01/2021 10:04:20 am
 * Author : npat692
 */ 

#include "global.h"
#include "adc.h"
#include "timer.h"
#include "uart.h"
#include "control.h"
#include "instructions_macros.h"



ISR(USART0_RX_vect){
	input_data = UDR0;
	if (input_data == STATIONARY){
		PORTB ^= (1<<5);
	}
	tx_debug(input_data);
	read_data(input_data);
}

int main(void)
{
    uart_init();
	sei();
	
	DDRB |= (1 << 5);
	PORTB |= (1 << 5);
    while (1) 
    {
		
    }
}

