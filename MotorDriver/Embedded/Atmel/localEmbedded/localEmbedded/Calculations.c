/*
 * Calculations.c
 *
 * Created: 18/12/2020 12:05:14 pm
 *  Author: yxin683
 */ 

#include <stdint.h>
#include <stdbool.h>

#define PERIODHALF 26
#define TOLERANCE 500
 

//declare variables
static volatile uint8_t dutyCycleNum = 0; //on time of the wave through the motor
static volatile uint8_t dutyLHalf = 0; //on time of the left mosfets
static volatile uint8_t dutyRHalf = 0; //on time of the right mosfets

static volatile uint16_t dutyCycleVoltage = 0; //input voltage to the H-bridge
static volatile uint16_t newVoltage = 0; //most recent voltage reading into the H-bridge
static volatile uint16_t Vout = 0; //voltage wanted across motor, set with setSpeedGrade
static volatile bool forward = true; //determines whether the car is moving forward or backward


uint8_t returnDutyLHalf(){
	return dutyLHalf;	
}

uint8_t returnDutyRHalf(){
	return dutyRHalf;
}

uint8_t returnPeriodHalf(){
	return PERIODHALF;
}

void updateDutyCycle(){
		if(dutyCycleVoltage > Vout){
			
			dutyCycleNum = (PERIODHALF*Vout)/dutyCycleVoltage;
			
			if (forward){
				dutyLHalf = (PERIODHALF/2) + (dutyCycleNum/2);
				dutyRHalf = (PERIODHALF/2) - (dutyCycleNum/2);
				}else{
				dutyLHalf = (PERIODHALF/2) - (dutyCycleNum/2);
				dutyRHalf = (PERIODHALF/2) + (dutyCycleNum/2);
			}
			}else{
				//set the duty cycle to maximum
				dutyLHalf = PERIODHALF - 1;
				dutyRHalf = 1;
			}
}
void setDutyCycleVoltage(uint16_t vinD) {
	dutyCycleVoltage = vinD;
}

void setSpeedGrade(uint16_t speed){
	Vout = speed;
}

// void checkDifference(uint16_t newVoltage){	
//}