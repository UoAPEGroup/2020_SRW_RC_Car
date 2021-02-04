/*
 * Calculations.c
 *
 * Created: 18/12/2020 12:05:14 pm
 *  Author: yxin683
 */ 

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "global.h"
#include "interrupt.h"

#define PERIOD_MOTOR 32 //half of the counts for the period 30kHz

#define ADC_ARRAY_SIZE 10
#define BL_ARRAY_SIZE 150
#define VCC_MV 5000
#define RESOLUTION 1024
#define CURRENT_OPAMP_GAIN 1470
#define CURRENT_SENSOR_GAIN_MV 400
#define CURRENT_SENSOR_OFFSET_MV 250
#define VOLTAGE_VD_MV 3703

#define RAMPTOLERANCE 3000
#define RAMPINCREMENT 2000

//declare variables
static volatile uint8_t finalOnTime = 0; //on time of the wave through the motor(in number of counts)
static volatile uint8_t leftOnTime = 0; //on time of the left mosfets(in number of counts)
static volatile uint8_t rightOnTime = 0; //on time of the right mosfets(in number of counts)

static volatile uint16_t inputV = 0; //most recent input voltage to the H-bridge
static volatile uint16_t inputI = 0; //most recent current reading into the H-bridge
static volatile uint16_t motorI = 0; //most recent current flowing through the motor
static volatile uint16_t averageV = 0; //average voltage across one second, to be sent out via bluetooth
static volatile uint16_t averageI = 0; //average current across one second, to be sent out via bluetooth
static volatile uint32_t averagePower = 0;//average power consumption over one seconds, to be sent out via bluetooth

static volatile uint16_t speedGrade = 0; //voltage wanted across motor, set with setSpeedGrade(in use)
static volatile uint16_t requiredSpeedGrade = 0; //voltage required across motor, set with setSpeedGrade(new required)
static volatile bool requiredForward = true; //determines whether the car is moving forward or backward
static volatile bool forward = true; //determines whether the car is moving forward or backward

//store adc readings of voltage and current (taken every ms)
static volatile uint16_t voltageValues[ADC_ARRAY_SIZE];
static volatile uint16_t currentValues[ADC_ARRAY_SIZE];

//store calculated current and voltage values over the last second (last ten average values)
static volatile uint16_t recentVoltageValues[BL_ARRAY_SIZE];
static volatile uint16_t recentCurrentValues[BL_ARRAY_SIZE];

//FLAGS
volatile bool arrayFull = false;
volatile bool sendData = false;

//counters

static volatile uint8_t ADCReadingsCount = 0;
static volatile uint8_t recentValuesCount = 0;

//store adc current and voltage readings in arrays

void setSpeedGrade(uint16_t speed){
	speedGrade = speed;
}

void setRequiredSpeedGrade(uint16_t newSpeed){
	requiredSpeedGrade = newSpeed;
}

uint16_t returnRequiredSpeedGrade() {
	return requiredSpeedGrade;
}
void setDirection(bool setForward){
	forward = setForward;
}

void setRequiredDirection(bool setRequiredForward){
	requiredForward = setRequiredForward;
}

void addCurrent(uint16_t adcCurrentReading) {
	currentValues[ADCReadingsCount] = adcCurrentReading;
}

void addVoltage(uint16_t adcVoltageReading) {
	 voltageValues[ADCReadingsCount] = adcVoltageReading;	
	 ADCReadingsCount++;
	 //reset count when array fills up
	 if (ADCReadingsCount == 10) {
		ADCReadingsCount = 0;
		arrayFull = true;
	}
}

//returns the result of an ADC conversion in millivolts
uint16_t adcConvert(uint16_t adcValue) {
	uint16_t convertedValue = ((uint32_t)adcValue * VCC_MV)/RESOLUTION;
	
	return convertedValue;
}

void convertVoltageAndCurrent() {
	//assuming range being read is 0 - 5A, convert back to original current value
	uint32_t totalC = 0;
	uint32_t totalV = 0;
	inputI = 0;
	
	//take the average of ten current readings and ten voltage readings
	for (uint8_t i = 0; i < 10; i++) {
		
		inputI = (((uint32_t)adcConvert(currentValues[i]) * 1000)/CURRENT_OPAMP_GAIN); //undo OpAmp gain
		inputI -= CURRENT_SENSOR_OFFSET_MV; //undo current sensor offset
		inputI = ((uint32_t)inputI * 1000)/CURRENT_SENSOR_GAIN_MV; //undo current sensor gain
		
		totalC += inputI;
		
		totalV += ((uint32_t)adcConvert(voltageValues[i]) * (VOLTAGE_VD_MV))/1000; //undo voltage divider gain

		}
		
	inputI = totalC/ADC_ARRAY_SIZE;
	inputV = totalV/ADC_ARRAY_SIZE;
	
	//check for overvoltage and overcurrent scenarios. A note: how do we limit the current flow through the motor, when considering the inverse of the duty cycle? 
	
	if (inputI >= 3000) {
		overCurrent = true;
		setSpeedGrade(STOP);
	}
	else {
		overCurrent = false;
	}
	
	if (inputV >= 12000) {
		overVoltage = true;
		setSpeedGrade(STOP);
	}
	else {
		overVoltage = false;
	}
 	
	uint16_t preValI = inputI;
	uint16_t preValV = inputV;
	
	//shift recent current/voltage values into an array [leaving space for 50 old values], note: what happens during first iteration?
	for (uint8_t i = 0; i < BL_ARRAY_SIZE; i ++) {
		
		uint16_t currentValI = recentCurrentValues[i];
		uint16_t currentValV = recentVoltageValues[i];
		
		recentCurrentValues[i] = preValI;
		recentVoltageValues[i] = preValV;
		
		preValI = currentValI;
		preValV = currentValV;
		
	}
	
	recentValuesCount++;
	
	//after one second 
	if (recentValuesCount == BL_ARRAY_SIZE) {
		sendData = true;
		recentValuesCount = 0;
	}
	
}

void averageVoltageAndCurrent() {
	
	//do a weight average where the weight is proportional to the number of values in the array
	//Older values have the least weight attached to them
	
	uint32_t totalAverageV= 0;
	uint32_t totalAverageI = 0;
	uint8_t countUp = 0;
	uint16_t sumOfWeights = 0;
	
	for (uint8_t i = BL_ARRAY_SIZE - 1; i > 0; i--) {
		totalAverageV += (uint32_t)i * recentVoltageValues[countUp]; //weight is the number in array, inverted (i.e., most recent value has highest weight, which is the array size)
		totalAverageI += (uint32_t)i * recentCurrentValues[countUp];
		
		sumOfWeights += i; //denominator of the average, equivalent to the summation of all the weights added to the array
		countUp++;
	}
	
	averageV = totalAverageV/(uint32_t)sumOfWeights;
	averageI = totalAverageI/(uint32_t)sumOfWeights;
	
	averagePower = ((uint32_t)averageI * averageV)/1000; //average power, in mWatts

}

uint16_t returnSpeedGrade() {
	return speedGrade;
}

bool returnDirection() {
	return forward;
}


void ramp(){
	if ((!lostRemoteConnection) && (!overCurrent) && (!overVoltage) && (establishedConnection)) {
		if(forward == requiredForward){	
			if(requiredSpeedGrade > speedGrade){
				if ((requiredSpeedGrade - speedGrade) > RAMPTOLERANCE){
					setSpeedGrade(returnSpeedGrade() + RAMPINCREMENT);
				}else{
					setSpeedGrade(requiredSpeedGrade);
				}
			}else{
				if ((speedGrade - requiredSpeedGrade) > RAMPTOLERANCE){
					setSpeedGrade(returnSpeedGrade() - RAMPINCREMENT);
				}else{
					setSpeedGrade(requiredSpeedGrade);
				}
			}
		}else{
			if (speedGrade == 0){
				forward = requiredForward;
				setSpeedGrade(returnSpeedGrade() + RAMPINCREMENT);
			}else{
				if((requiredSpeedGrade - speedGrade) > RAMPTOLERANCE){
					setSpeedGrade(returnSpeedGrade() - RAMPINCREMENT);
				}else{
					setSpeedGrade(0);
				}
			}
		}
	}
}

void updateDutyCycle(){

	
		//if the input voltage to the H-bridge is greater than the voltage wanted across the motor:
		if(inputV > speedGrade){
			
			finalOnTime = ((uint32_t)PERIOD_MOTOR*speedGrade)/inputV; //calculate the on time of the final wave across the motor
			
			if (forward){
				leftOnTime = (PERIOD_MOTOR + finalOnTime)/2; //set the on time of left fets
				rightOnTime = (PERIOD_MOTOR - finalOnTime)/2; //set the on time of the right fets
				}else{
				leftOnTime = (PERIOD_MOTOR - finalOnTime)/2; //set on time of the left fets
				rightOnTime = (PERIOD_MOTOR + finalOnTime)/2; //set the on time of the right fets
				}
			
		}else{
				//set the duty cycle to maximum if the input voltage to the H-bridge is less or equal than the voltage wanted across the motor:
				if(forward){
					leftOnTime = PERIOD_MOTOR - 1;
					rightOnTime = 1;
				}else{
					leftOnTime = 1;
					rightOnTime = PERIOD_MOTOR - 1;
				}
				
			}
			
		//calculate current flowing through motor using the inverse of the duty cycle
		//motorI = ((uint32_t)inputI * PERIOD_MOTOR)/finalOnTime;
		
}


void setInputV(uint16_t vinD) {
	inputV = vinD;
}


uint8_t returnLeftOnTime(){
	return leftOnTime;
}

uint8_t returnRightOnTime(){
	return rightOnTime;
}

uint8_t returnFinalPeriod(){
	return PERIOD_MOTOR;
}

uint16_t returnInputI() {
	return inputI;
}

uint16_t returnInputV() {
	return inputV;
}

uint16_t returnAvgV() {
	return averageV;
}

uint16_t returnAvgI() {
	return averageI;
}


uint32_t returnAvgP() {
	return averagePower;
}