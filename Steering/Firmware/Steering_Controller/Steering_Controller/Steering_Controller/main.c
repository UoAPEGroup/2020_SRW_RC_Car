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

int test;

ISR(USART0_RX_vect){
	test = UDR0;
	PORTB ^= (1<<5);

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

