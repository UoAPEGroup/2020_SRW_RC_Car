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

//#define F_CPU 800000UL
//#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>

//in cV(centiVolt)
#define MAX_VOLTAGE 950
#define MID_VOLTAGE 700
#define MIN_VOLTAGE 500
#define STOP 0

int main(void)
{
	//turn on global interrupts
	interrupt_init();
	sei();
	uint8_t offset = 0;
	
	//set output pins
	DDRD |= (1 << DDD3)|(1 << DDD5);
	DDRB |= (1 << DDB1);

	//stop all the timers
	GTCCR = ((1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC)); 
	
	setSpeedGrade(MIN_VOLTAGE);
	setInputV(1000);
	setDirection(true); // true = forward, false = backward
	updateDutyCycle();
	
	
	//initialize timers
	timer0_init(returnPeriodHalf(),returnLeftOnTime());  // PWm that controls the left FET driver
	timer2_init(returnPeriodHalf(),returnRightOnTime());  // PWM that controls the right FET driver
	timer1_init();
	
	TCNT0 = 0;   // setting offset
	TCNT2 = offset;  // setting offset(set to period to)

	GTCCR = 0;   // start all timers
	
	//initalize the adc
	adc_init();
	
	uart_init(9600);
	char hello[10];
	
	uint16_t checkADC = adcConvert(930);
	
	sprintf(hello, "%lu", checkADC);
	
    while (1)
    {
		send_data(hello);
    }
}

