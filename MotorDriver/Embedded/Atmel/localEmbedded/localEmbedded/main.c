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

#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>


int main(void)
{
// 	watchdog_init(); //initialize the watchdog timer
 	adc_init(); //initialize the adc
 	stChangeInterrupt_init(); //initialize the state change interrupt
	encoderInterrupt_init();//initialize encoder interrupt
	uart_init(9600); //initialize the uart
		
 	sei(); //turn on global interrupts
	  	
	//set output pins
	DDRD |= (1 << DDD3)|(1 << DDD5)|(1 << DDD4);
	DDRB |= (1 << DDB1);
	

	//set input pins
	DDRC &= ~(1 << DDC5) | ~(1 << DDC4) | ~(1 << DDC3); //THREE PINS
	DDRD &= ~(1 << DDD2); //INT0

	//stop all the timers
	//GTCCR = ((1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC)); 
	
// 	setSpeedGrade(STOP);
// 	setInputV(10000);
// 	setDirection(true); // true = forward, false = backward
// 	updateDutyCycle();
// 	
// 	//initialize timers
// 	timer0_init(returnFinalPeriod(),returnLeftOnTime());  // PWm that controls the left FET driver
// 	timer2_init(returnFinalPeriod(),returnRightOnTime());  // PWM that controls the right FET driver
	//initialize timers
	//timer0_init(132, 62);  // PWm that controls the left FET driver
	//timer2_init(132, 20); // PWM that controls the right FET driver
	
	timer1_init();
	timer3_init();
// 	
// 	TCNT0 = 0;   // setting offset
// 	TCNT2 = 0;  // setting offset(set to period to)
// 
// 	GTCCR = 0;   // start all timers
	
	char transmitValue[10];
	
    while (1)
    {
		
 		if (arrayFull) {//every 10.5 ms
			 
// 			GTCCR = ((1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC));  //stop all the timers
			TCCR1B &= ~(1 << CS10) | ~(1 << CS11);
			
 			convertVoltageAndCurrent();	//calculate input/output voltage, and set flags for overcurrent/overvoltage	
			ramp();
			updateDutyCycle();
			
			TCCR1B |= (1 << CS10) | (1 << CS11);
			
			GTCCR = ((1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC));  //stop all the timers
			
			//re-initialize timers
			timer0_init(returnFinalPeriod(),returnLeftOnTime());  // PWm that controls the left FET driver
			timer2_init(returnFinalPeriod(),returnRightOnTime());  // PWM that controls the right FET driver

			TCNT0 = 0;   // setting offset
			TCNT2 = 0;  // setting offset(set to period to)
			
			GTCCR = 0;   // start all timers
			 		
 			//checkADC(); //stops the ADC interrupt (i.e., sampling) and prints out current/voltage values. Uses a 500ms delay (but no sampling is happening in this time).
			 
			arrayFull = false;

 		}
		 
		 if(oneSecCounter >= 100){//run every second
			//calculate speed and clear counter
			PORTD ^= (1 << DDD4);	
			realSpeedCalc();
			rotCount = 0;
			oneSecCounter = 0;		 
		 }
		 
		 
		if (sendData) {//every 1s. Note that checkADC and checkInterrupt can't run simultaneously due to the 500 ms delay in checkADC.
			

			//stop ADC sampling
			TCCR1B &= ~(1 << CS10) | ~(1 << CS11);
			//checkInterrupt();
			averageVoltageAndCurrent();
			//checkTransmission();
			checkAvgCalc();
			sendData = false;
			//start ADC sampling again
			TCCR1B |= (1 << CS10) | (1 << CS11);
			
		}
    }
}

