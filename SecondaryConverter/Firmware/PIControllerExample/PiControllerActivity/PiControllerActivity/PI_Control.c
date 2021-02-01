/*
 * PI_Control.c
 *
 * Created: 2/02/2021 4:53:03 AM
 *  Author: Manoj Kumaraguru
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "PI_Control.h"
#include "timer.h"

#define kp 1
#define ki 1
#define setPoint 15000
#define clkfreq 8000000

static int32_t intError = 0;
static int32_t output = 0;
static uint32_t previousTime = 0;
static bool errorHasBeenCalc = false;

void calculateError(uint16_t measuredVolt) {
	uint32_t currentTime = returnOverflowCount() * 65536 / clkfreq + TCNT1 / clkfreq;
	uint32_t elapsedTime = currentTime - previousTime;

	
	int32_t error = setPoint - measuredVolt;
	intError += error * elapsedTime;
	
	output = kp * error + ki * intError;
	previousTime = currentTime;
	errorHasBeenCalc = true;
}

bool returnErrorCalcFlag() {
	return errorHasBeenCalc;
}

void setErrorCalcFlag() {
	errorHasBeenCalc = false;
}

int32_t returnOutput() {
	return output;
}