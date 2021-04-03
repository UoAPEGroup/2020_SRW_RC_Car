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

#define PERIOD_MOTOR 255 //half of the counts for the period 30kHz
#define ROTLENGTH 21 //length of on rotation, perimeter of wheel in cm

#define ADC_ARRAY_SIZE 10
#define BL_ARRAY_SIZE 150
#define VCC_MV 3300
#define RESOLUTION 1024
#define CURRENT_OPAMP_GAIN 1467
#define CURRENT_SENSOR_GAIN_MV 400
#define CURRENT_SENSOR_OFFSET_MV 250
#define VOLTAGE_VD_MV 6100
#define MAXV 12000
#define MAXI 2500

#define RAMPTOLERANCE 10 
#define RAMPINCREMENT 10

//declare variables
static volatile uint8_t finalOnTime = 0; //on time of the wave through the motor(in number of counts)
static volatile uint8_t leftOnTime = 0; //on time of the left mosfets(in number of counts)
static volatile uint8_t rightOnTime = 0; //on time of the right mosfets(in number of counts)

static volatile uint16_t inputV = 0; //most recent input voltage to the H-bridge
static volatile uint16_t inputI = 0; //most recent current reading into the H-bridge
static volatile uint32_t motorI = 0; //most recent current flowing through the motor
static volatile uint16_t averageV = 0; //average voltage across one second, to be sent out via bluetooth
static volatile uint16_t averageI = 0; //average current across one second, to be sent out via bluetooth
static volatile uint32_t averagePower = 0;//average power consumption over one seconds, to be sent out via bluetooth

static volatile uint16_t speedGrade = 0; //voltage wanted across motor, set with setSpeedGrade(in use)
static volatile uint16_t requiredSpeedGrade = 0; //voltage required across motor, set with setSpeedGrade(new required)
static volatile bool requiredForward = true; //determines whether the car is moving forward or backward
static volatile bool forward = true; //determines whether the car is moving forward or backward

static volatile uint16_t realSpeed = 0; //result of real speed calculation in cm/s


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

// update current speed of car
void setSpeedGrade(uint16_t speed){
	speedGrade = speed;
}

// set the required speed of car
void setRequiredSpeedGrade(uint16_t newSpeed){
	requiredSpeedGrade = newSpeed;
}

// return required speed of car
uint16_t returnRequiredSpeedGrade() {
	return requiredSpeedGrade;
}

// set car direction
void setDirection(bool setForward){
	forward = setForward;
}

// set required car direction
void setRequiredDirection(bool setRequiredForward){
	requiredForward = setRequiredForward;
}

// add ADC current reading to array
void addCurrent(uint16_t adcCurrentReading) {
	currentValues[ADCReadingsCount] = adcCurrentReading;
}

// add ADC voltage reading to array
void addVoltage(uint16_t adcVoltageReading) {
	 voltageValues[ADCReadingsCount] = adcVoltageReading;	
	 ADCReadingsCount++;
	 
	 //reset count when array fills up
	 if (ADCReadingsCount == 10) {
		ADCReadingsCount = 0;
		arrayFull = true;
	}
}

// return ADC conversion result in millivolts
uint16_t adcConvert(uint16_t adcValue) {
	uint16_t convertedValue = ((uint32_t)adcValue * VCC_MV)/RESOLUTION;
	
	return convertedValue;
}

// convert adc voltage and current values to H-Bridge voltage and current
void convertVoltageAndCurrent() {
	
	// assumed input current range is 0 - 5A
	
	uint32_t totalC = 0;
	uint32_t totalV = 0;
	inputI = 0;
	
	// convert adc voltage/current readings back to H-Bridge values
	// take the average of ten readings
	
	for (uint8_t i = 0; i < 10; i++) {
		
		inputI = (((uint32_t)adcConvert(currentValues[i]) * 1000)/CURRENT_OPAMP_GAIN); // undo OpAmp gain
		inputI -= CURRENT_SENSOR_OFFSET_MV; // undo current sensor offset
		inputI = ((uint32_t)inputI * 1000)/CURRENT_SENSOR_GAIN_MV; //undo current sensor gain
		
		totalC += inputI;
		
		totalV += ((uint32_t)adcConvert(voltageValues[i]) * (VOLTAGE_VD_MV))/1000; // undo voltage divider gain

		}
	
	// update voltage and current readings
	inputI = totalC/ADC_ARRAY_SIZE;
	inputV = totalV/ADC_ARRAY_SIZE;
	
	///motorI = ((uint32_t)inputI * PERIOD_MOTOR)/finalOnTime;
	
	// update over voltage and over current flags
	if (inputI >= MAXI) {
		overCurrent = true;
		setRequiredSpeedGrade(STOP);
		//setSpeedGrade(STOP);
	}
	else {
		overCurrent = false;
	}
	
	if (inputV >= MAXV) {
		overVoltage = true;
		setRequiredSpeedGrade(STOP);
		//setSpeedGrade(STOP);
	}
	else {
		overVoltage = false;
	}
 	
	uint16_t preValI = inputI;
	uint16_t preValV = inputV;
	
	// shift recent current/voltage values into array [leaving space for 50 old values]
	
	for (uint8_t i = 0; i < BL_ARRAY_SIZE; i ++) {
		
		uint16_t currentValI = recentCurrentValues[i];
		uint16_t currentValV = recentVoltageValues[i];
		
		recentCurrentValues[i] = preValI;
		recentVoltageValues[i] = preValV;
		
		preValI = currentValI;
		preValV = currentValV;
		
	}
	
	recentValuesCount++;
	
	// after one second, set data send flag to true
	if (recentValuesCount == BL_ARRAY_SIZE) {
		sendData = true;
		recentValuesCount = 0;
	}
	
}

void averageVoltageAndCurrent() {
	
	// do a weight average where the weight is proportional to the number of values in the array
	// plder values have the least weight attached to them
	
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
	// update the speed of the car in increments to prevent current spikes
//	if ((!lostRemoteConnection) && (!overCurrent) && (!overVoltage) && (establishedConnection)) {
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
				if ((speedGrade) > RAMPTOLERANCE){
					setSpeedGrade(returnSpeedGrade() - RAMPINCREMENT);
				}else{
					setSpeedGrade(0);
				}
			}
		}
	//}
}

void updateDutyCycle(){

		// update the on time of the right and left PWM waves (which control the FETs)
		
		//if the input voltage to the H-bridge is greater than the voltage wanted across the motor:
		if(inputV != 0){
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
					setSpeedGrade(inputV);
					if(forward){
						leftOnTime = PERIOD_MOTOR - 1;
						rightOnTime = 1;
					}else{
						leftOnTime = 1;
						rightOnTime = PERIOD_MOTOR - 1;
					}
				
			}
		}else{
			leftOnTime = PERIOD_MOTOR/2;
			rightOnTime = PERIOD_MOTOR/2;
		}
			
			
		//calculate current flowing through motor using the inverse of the duty cycle
		//motorI = ((uint32_t)inputI * PERIOD_MOTOR)/finalOnTime;
		
}

void realSpeedCalc(){
	realSpeed = rotCount*ROTLENGTH;//assuming calculated every second, actual calculation (rotCount/seconds)*rotLength
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