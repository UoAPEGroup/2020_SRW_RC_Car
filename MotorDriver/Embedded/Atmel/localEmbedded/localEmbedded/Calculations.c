/*
 * Calculations.c
 *
 * Created: 18/12/2020 12:05:14 pm
 *  Author: yxin683
 */ 

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define PERIODHALF 26 //half of the counts for the period
#define TOLERANCE 100
#define ARRAY_SIZE 10

//declare variables
static volatile uint8_t finalOnTime; //on time of the wave through the motor(in number of counts)
static volatile uint8_t leftOnTime; //on time of the left mosfets(in number of counts)
static volatile uint8_t rightOnTime; //on time of the right mosfets(in number of counts)

static volatile uint16_t inputV; //input voltage to the H-bridge
static volatile uint16_t inputI; //most recent current reading into the H-bridge
static volatile uint16_t speedGrade; //voltage wanted across motor, set with setSpeedGrade
static volatile bool forward; //determines whether the car is moving forward or backward

//store adc readings of voltage and current (taken every ms)
static volatile uint16_t voltageValues[ARRAY_SIZE];
static volatile uint16_t currentValues[ARRAY_SIZE];

//store calculated current and voltage values over the last second (last ten average values)
static volatile uint16_t recentVoltageValues[ARRAY_SIZE];
static volatile uint16_t recentCurrentValues[ARRAY_SIZE];

//FLAGS
extern volatile bool arrayFull = false;

//counters

static volatile uint8_t count = 0;

//store adc current and voltage readings in arrays

void addCurrent(uint16_t adcCurrentReading) {
	currentValues[count] = adcCurrentReading;
}

void addVoltage(uint16_t adcVoltageReading) {
	 voltageValues[count] = adcVoltageReading;	
	 count++;
	 //reset count when array fills up
	 if (count == 10) {
		count = 0;
		arrayFull = true;
	}
}

//returns the result of an ADC conversion in millivolts
uint16_t adcConvert(uint16_t adcValue) {
	uint16_t convertedValue = ((uint32_t)adcValue * 3300)/1024;
	
	return convertedValue;
}

void convertVoltageAndCurrent() {
	
}

void updateDutyCycle(){
	
		//if the input voltage to the H-bridge is greater than the voltage wanted across the motor:
		if(inputV > speedGrade){
			
			finalOnTime = (PERIODHALF*speedGrade)/inputV; //calculate the on time of the final wave across the motor
			
			if (forward){
				leftOnTime = (PERIODHALF + finalOnTime)/2; //set the on time of left fets
				rightOnTime = (PERIODHALF - finalOnTime)/2; //set the on time of the right fets
				}else{
				leftOnTime = (PERIODHALF - finalOnTime)/2; //set on time of the left fets
				rightOnTime = (PERIODHALF + finalOnTime)/2; //set the on time of the right fets
				}
			
		}else{
				//set the duty cycle to maximum if the input voltage to the H-bridge is less or equal than the voltage wanted across the motor:
				if(forward){
					leftOnTime = PERIODHALF - 1;
					rightOnTime = 1;
				}else{
					leftOnTime = 1;
					rightOnTime = PERIODHALF - 1;
				}
				
			}
}


void setInputV(uint16_t vinD) {
	inputV = vinD;
}

void setSpeedGrade(uint16_t speed){
	speedGrade = speed;
}

void setDirection(bool setForward){
	forward = setForward;
}

uint8_t returnLeftOnTime(){
	return leftOnTime;
}

uint8_t returnRightOnTime(){
	return rightOnTime;
}

uint8_t returnPeriodHalf(){
	return PERIODHALF;
}

uint16_t returnSpeedGrade() {
	return speedGrade;
}