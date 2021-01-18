/*
 * PiControllerActivity.c
 *
 * Created: 18/01/2021 2:00:23 PM
 * Author : Manoj
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "main.h"

#define kp 1
#define ki 1
#define setPoint 5
#define clkfreq 8000000

static uint32_t intError = 0;
static uint32_t overflowCount = 0;
static uint32_t previousTime = 0;
static uint32_t output = 0;
static bool errorHasBeenCalc = false;

int main(void)
{
	adcInit();
	timerInit();
	pwmInit();

    while (1) 
    {
		if(errorHasBeenCalc) {
			setPWM(output);
			errorHasBeenCalc = false;
		}
    }
}

ISR(ADC_vect){
	uint16_t measuredVolt = ADC;
	measuredVolt = (uint32_t)(measuredVolt) * 5/1024;
	calculatePiVals(measuredVolt);
}

void calculatePiVals(uint16_t measuredVolt) {
	uint32_t currentTime = overflowCount * 65536 / clkfreq + TCNT1 / clkfreq;
	uint32_t elapsedTime = currentTime - previousTime;

	
	uint16_t error = setPoint - measuredVolt;
	intError += intError * elapsedTime;
	
	output = kp * error + ki * intError;
	previousTime = currentTime;
	errorHasBeenCalc = true;
}

void adcInit(){
	DDRC &= ~(1<<PC0);
	ADMUX = 0b01000000;
	ADCSRA = 0b11111000;
	ADCSRB = 0;	
}

void timerInit(){
	TCCR1A = 0;
	TCCR1B = 0b00001000;
	TIMSK1 |= (1<<TOIE1);
	OCR1A = 65535;
}

ISR(TIMER1_OVF_vect) {
	overflowCount++;
}

void pwmInit(){}

void setPWM(uint32_t error) {}