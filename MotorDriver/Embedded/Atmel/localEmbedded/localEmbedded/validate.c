/*
 * validate.c
 *
 * Created: 27/01/2021 11:17:18 am
 *  Author: Earlene
 */ 
#include "uart.h"
#include "Calculations.h"
#include <string.h>
#include <stdio.h>

void checkADC() {//send converted values to UART
	
	char transmitVoltage[10];
	char transmitCurrent[10];
	
	uint16_t voltageValue = returnInputV(); //PC1, ADC1
	uint16_t currentValue = returnInputI(); //PC0, ADC0

	sprintf(transmitCurrent, "%u", currentValue);
	send_data(transmitCurrent);
	
	sprintf(transmitCurrent, "%u", voltageValue);
	send_data(transmitCurrent);
}

void checkInterrupt() {
	
}

void checkSafety() {
	
}