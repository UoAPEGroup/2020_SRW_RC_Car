/*
 * localEmbedded.c
 *
 * Created: 9/12/2020 2:54:10 pm
 * Author : Earlene
 */ 

#include <avr/io.h>
#include "timer.h"
#include "Calculations.h"
#include "adc.h"
#include "uart.h"
#include "interrupt.h"
#include "global.h"
#include "watchdog.h"

//#define F_CPU 800000UL
//#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
	watchdog_init(); //initialize the watchdog timer
	adc_init(); //initialize the adc
	interrupt_init(); //initialize the interrupt
	uart_init(9600); //initialize the uart
	
	
	sei(); //turn on global interrupts
	uint8_t offset = 0;
	
	//set output pins
	DDRD |= (1 << DDD3)|(1 << DDD5);
	DDRB |= (1 << DDB1);

	//stop all the timers
	GTCCR = ((1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC)); 
	
	setSpeedGrade(MIN_VOLTAGE);
	setInputV(10000);
	setDirection(true); // true = forward, false = backward
	updateDutyCycle();
	
	//initialize timers
	timer0_init(returnPeriodHalf(),returnLeftOnTime());  // PWm that controls the left FET driver
	timer2_init(returnPeriodHalf(),returnRightOnTime());  // PWM that controls the right FET driver
	timer1_init();
	
	TCNT0 = 0;   // setting offset
	TCNT2 = offset;  // setting offset(set to period to)

	GTCCR = 0;   // start all timers
	
	char hello[10];
	
    while (1)
    {
		if (arrayFull) {
		
		//turn off adc by turning off timer1
		TCCR1B &= ~(1 << CS10) | ~(1 << CS11) | ~(1 << CS12);
			
		//do calculations
		convertVoltageAndCurrent();
		
		//print on terminal to verify
		//uint16_t inputV = returnInputV();
		//sprintf(hello, "%u", inputV);
		//send_data(hello);
		
		//uint16_t inputI = returnInputI();
		//sprintf(hello, "%u", inputI);
		//send_data(hello);
		
		//turn on timer1 and set flag
		arrayFull = false;
		TCCR1B |= (1 << CS10) | (1 << CS11);
		
		}
		
		if (sendData) {
			
			averageVoltageAndCurrent();
			
			uint16_t inputV = returnAvgV();
			sprintf(hello, "%u", inputV);
			send_data(hello);
					
			uint16_t inputI = returnAvgI();
			sprintf(hello, "%u", inputI);
			send_data(hello);
			
			sendData = false;
		}
		
    }
}

