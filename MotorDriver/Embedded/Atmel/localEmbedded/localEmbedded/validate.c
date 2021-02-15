/*
 * validate.c
 *
 * Created: 27/01/2021 11:17:18 am
 *  Author: Earlene
 */ 
#include "uart.h"
#include "global.h"
#include "Calculations.h"
#include "interrupt.h"

#define F_CPU 8000000
#define ARRAY_SIZE 50
#include <util/delay.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>

static volatile uint16_t count = 0;

void checkADC() {//send converted values to UART
	
	TCCR1B &= ~(1 << CS10) | ~(1 << CS11) | ~(1 << CS12); //turn off adc sampling
	convertVoltageAndCurrent();
	
	char transmitValue[ARRAY_SIZE];
		
	uint16_t voltageValue = returnInputV(); //PC1, ADC1
	uint16_t currentValue = returnInputI(); //PC0, ADC0

	sprintf(transmitValue, "%u", currentValue);
	send_data(transmitValue);
	
	sprintf(transmitValue, "%u", voltageValue);
	send_data(transmitValue);
	
	_delay_ms(500);
	
	arrayFull = false;
	TCCR1B |= (1 << CS10) | (1 << CS11); //turn on adc sampling
	
}

void checkInterrupt() {
	
	char transmitValue[ARRAY_SIZE];
	//Sig0 = PC3, Sig1 = PC4, Dir = PC5
	uint16_t speedVoltage = returnSpeedGrade();
	sprintf(transmitValue, "%u", speedVoltage);
	send_data(transmitValue);
	
	bool direction = returnDirection();
	sprintf(transmitValue, "%d", direction);
	send_data(transmitValue);
	
	
}

void checkSafety() {
	
}

void checkTransmission() {
	char transmitValue[ARRAY_SIZE];
	
	sprintf(transmitValue, "%u", count);
	send_data(transmitValue);
	
	count++;
}

void checkAvgCalc() {
	char transmitValue[ARRAY_SIZE];
	
	uint16_t voltage = returnAvgV();
	uint16_t current = returnAvgI();
	bool direction = returnDirection();
	uint16_t speedGrade = returnRequiredSpeedGrade();
	
	switch(speedGrade) {
		case STOP:
		speedGrade = 0;
		break;
		
		case MIN_VOLTAGE:
		speedGrade = 1;
		break;

		case MID_VOLTAGE:
		speedGrade = 2;
		break;

		case MAX_VOLTAGE:
		speedGrade = 3;
		break;
	}
	
	
	sprintf(transmitValue, "%s%u%s%u%s%u%s%u%s%u%s%u%s%u%s%s", "M", voltage, "V", current, "A", direction, "D", speedGrade, "G", overVoltage,"O", overCurrent,"C", establishedConnection,"E", "N");
	send_data(transmitValue);

}