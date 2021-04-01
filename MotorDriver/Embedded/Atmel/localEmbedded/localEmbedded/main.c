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
#include "validate.h"

#define F_CPU 8000000
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>


int main(void)
{
// 	watchdog_init(); //initialize the watchdog timer (note: currently resulting in an error)

	//initialization functions
 	adc_init(); //initialize adc
 	stChangeInterrupt_init(); //initialize state change interrupt 
	encoderInterrupt_init();//initialize speed calculation interrupt
	uart_init(9600); //initialize uart at baud rate 9600
		
 	sei(); //turn on global interrupts
	  	
	//set output pins
	DDRD |= (1 << DDD3)|(1 << DDD5)|(1 << DDD4);
	DDRB |= (1 << DDB1);

	//set input pins
	DDRC &= ~(1 << DDC5) | ~(1 << DDC4) | ~(1 << DDC3); 
	DDRD &= ~(1 << DDD2); //INT0
	
	//initialize ADC/misc timer
	timer1_init(); // samples input voltage and current readings via ADC
	timer3_init(); // checks safety connection parameters (connection established & lost remote connection) and is a one second counter
 
	char transmitValue[10];
	
    while (1)
    {
		// 
 		if (arrayFull) {

			TCCR1B &= ~(1 << CS10) | ~(1 << CS11); // stop ADC sampling
			
 			convertVoltageAndCurrent();	// calculate voltage/current/power at H-Bridge and set over-voltage and over-current flags
			ramp(); // update the current speed requirement via a 10mV ramp
			updateDutyCycle(); // calculate on time for PWM waves
			
			TCCR1B |= (1 << CS10) | (1 << CS11); // restart ADC sampling
			
			GTCCR = ((1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC));  //stop all timers
			
			//re-initialize PWM timers
			timer0_init(returnFinalPeriod(),returnLeftOnTime());  // set values for PWM that controls the left FET driver
			timer2_init(returnFinalPeriod(),returnRightOnTime());  // set values PWM that controls the right FET driver

			TCNT0 = 0; // setting offset for left PWM
			TCNT2 = 0; // setting offset for right PWM
			
			GTCCR = 0; // start timers
			 		
 			//checkADC(); //stops the ADC interrupt (i.e., sampling) and prints out current/voltage values. Uses a 500ms delay (but no sampling is happening in this time).
			 
			arrayFull = false;

 		}
		 
		 if(oneSecCounter >= 25){//run every second
			 
			//calculate car speed and restart one second counter
			PORTD ^= (1 << DDD4);
			realSpeedCalc();
			rotCount = 0;
			oneSecCounter = 0;		 
		 }
		 
		 
		if (sendData) {//every 1s. Note that checkADC and checkInterrupt can't run simultaneously due to the 500 ms delay in checkADC.

			//stop ADC sampling
			TCCR1B &= ~(1 << CS10) | ~(1 << CS11);
			
			//checkInterrupt();
			
			// calculate the average voltage and current over the last second 
			averageVoltageAndCurrent();
			
			//checkTransmission();
			
			// send calculation values through uart 
			checkAvgCalc();
			sendData = false;
			
			// restart ADC sampling
			TCCR1B |= (1 << CS10) | (1 << CS11);
			
		}
    }
}

