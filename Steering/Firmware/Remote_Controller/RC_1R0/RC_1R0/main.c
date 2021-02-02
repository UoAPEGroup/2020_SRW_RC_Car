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



int main(void)
{
	adc_init();
	
    sei();
	
	
    while (1) 
    {
    }
}

