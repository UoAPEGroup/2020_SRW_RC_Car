/*
 * RC_1R0.c
 *
 * Created: 22/12/2020 10:48:28 AM
 * Author : htom380
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "adc.h"
#include "timer0.h"
#include "global.h"
#include "uart.h"
#include "controlSend.h"
#include "interrupt.h"

volatile uint8_t transmitTimerCounter = 0;											// This counter checks if enough time has passed for BLE transmission to occur

ISR(TIMER0_COMPA_vect) {
	if (transmitTimerCounter < 50) {
		transmitTimerCounter++;
	}
	else {
		set_RTS_flag(true);															// Set RTS true for BLE transmission
		usart0_transmit_byte(get_instruction_byte());
		//usart0_transmit_string("hello\r\n");
		transmitTimerCounter = 0;
	}
}



int main(void)
{
	adc_init();
	usart_init(DEFAULT_BAUD_RATE);
	timer0_init();
    //interrupt_init();
	
	sei();
/*	cli();*/
    while (1) 
    {
		//str_data_conversion();
		//accel_data_conversion();
		instructionSend();
		
    }
}

