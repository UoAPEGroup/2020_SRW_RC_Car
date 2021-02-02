/*
 * RC_1R0.c
 *
 * Created: 22/12/2020 10:48:28 AM
 * Author : htom380
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "timer0.h"
#include "global.h"
#include "uart.h"
#include "controlSend.h"

volatile uint8_t transmitTimerCounter = 0;											// This counter checks if enough time has passed for BLE transmission to occur

ISR(TIMER0_COMPA_vect) {
	if (transmitTimerCounter < 5) {
		transmitTimerCounter++;
	}
	else {
		set_RTS_flag(true);															// Set RTS true for BLE transmission
	}
};

int main(void)
{
	adc_init();
	usart_init(DEFAULT_BAUD_RATE);
	timer0_init();
    interrupt_init();
	
	sei();
	
	
    while (1) 
    {
    }
}

