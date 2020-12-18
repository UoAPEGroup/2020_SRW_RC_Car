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
static volatile uint8_t dutyCycleNum = 0; 
static volatile uint8_t dutyLHalf = 0;
static volatile uint8_t dutyRHalf = 0;

static volatile uint16_t dutyCycleVoltage = 0; 
static volatile uint16_t newVoltage = 0;
static volatile uint16_t Vout = 0; //set with setSpeedGrade
static volatile bool forward = true;


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