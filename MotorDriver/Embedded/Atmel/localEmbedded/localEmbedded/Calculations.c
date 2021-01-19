/*
 * Calculations.c
 *
 * Created: 18/12/2020 12:05:14 pm
 *  Author: yxin683
 */ 

#include <stdint.h>
#include <stdbool.h>

#define PERIODHALF 26 //half of the counts for the period
#define TOLERANCE 500
#define ARRAY_SIZE 10

//declare variables
static volatile uint8_t finalOnTime = 0; //on time of the wave through the motor(in number of counts)
static volatile uint8_t leftOnTime = 0; //on time of the left mosfets(in number of counts)
static volatile uint8_t rightOnTime = 0; //on time of the right mosfets(in number of counts)

static volatile uint16_t inputV = 0; //input voltage to the H-bridge
static volatile uint16_t recentInputV = 0; //most recent voltage reading into the H-bridge
static volatile uint16_t speedGrade = 0; //voltage wanted across motor, set with setSpeedGrade
static volatile uint8_t forward = 1; //determines whether the car is moving forward or backward

//create arrays
static volatile uint16_t voltageValues[ARRAY_SIZE];
static volatile uint16_t currentValues[ARRAY_SIZE];

static volatile uint8_t count = 0;

//FLAGS
extern volatile bool arrayFull = false;

//store adc current and voltage readings in arrays

void addCurrent(uint16_t adcCurrentReading) {
	currentValues[count] = adcCurrentReading;
}

void addVoltage(uint16_t adcVoltageReading) {
	 voltageValues[count] = adcVoltageReading;	
	 
	 //reset count when array fills up
	 if (count == 9) {
		count = 0;
		arrayFull = true;
	}
}

void updateDutyCycle(){
	
		//if the input voltage to the H-bridge is greater than the voltage wanted across the motor:
		if(inputV > speedGrade){
			
			finalOnTime = (PERIODHALF*speedGrade)/inputV; //calculate the on time of the final wave across the motor
			
			if (forward == 1){
				leftOnTime = (PERIODHALF/2) + (finalOnTime/2); //set the on time of left fets
				rightOnTime = (PERIODHALF/2) - (finalOnTime/2); //set the on time of the right fets
				}else{
				leftOnTime = (PERIODHALF/2) - (finalOnTime/2); //set on time of the left fets
				rightOnTime = (PERIODHALF/2) + (finalOnTime/2); //sset the on time of the right fets
				}
			
		}else{
				//set the duty cycle to maximum
				leftOnTime = PERIODHALF - 1;
				rightOnTime = 1;
			}
}
void setInputV(uint16_t vinD) {
	inputV = vinD;
}

void setSpeedGrade(uint16_t speed){
	speedGrade = speed;
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