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
#define setPoint 15000000 //15V wanted (10^6 factor)
#define clkfreq 8000000

static int32_t intError = 0;
static int32_t output = 0;
static uint32_t previousTime = 0;
static bool errorHasBeenCalc = false;

void calculateError(uint16_t measuredVolt) {

	uint32_t elapsedTime = 54; //micro seconds
	measuredVolt = measuredVolt * 10 * 10 * 10; //Make factor * 10^6 to match time
	int32_t propError = setPoint - measuredVolt; //Calculate the proportional error
	intError += propError * elapsedTime; //Calculate the integral error
	
	output = kp * propError + ki * intError; //Sum errors
	
	errorHasBeenCalc = true; //Set flag to true to adjust pi. Could just call pi adjustment function from here - no need for flags
}

//Returns whether the error has been calculated or not
bool returnErrorCalcFlag() {
	return errorHasBeenCalc;
}

//Resets the error calculated flag for after pi has been adjusted
void setErrorCalcFlag() {
	errorHasBeenCalc = false;
}

//Returns the total error
int32_t returnOutput() {
	return output;
}