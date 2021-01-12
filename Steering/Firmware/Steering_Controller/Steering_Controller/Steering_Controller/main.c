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

char test;

ISR(USART0_RX_vect){
	test = UDR0;
	if (test == 97){
		PORTB ^= (1<<5);
	}
	tx_debug();
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

