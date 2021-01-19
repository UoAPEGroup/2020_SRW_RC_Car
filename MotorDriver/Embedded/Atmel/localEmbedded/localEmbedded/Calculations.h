 /*
 * Calculations.h
 *
 * Created: 18/12/2020 12:06:08 pm
 *  Author: yxin683
 */ 


#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

//variables
static volatile uint8_t duty_cycle;
static volatile uint8_t dutyLHalf;
static volatile uint8_t dutyRHalf;

static volatile uint16_t dutyCycleVoltage;
static volatile uint16_t newVoltage;
static volatile uint16_t Vout;

static volatile uint16_t voltageValues;
static volatile uint16_t currentValues;

static volatile uint8_t count = 0;

//FLAGS
extern volatile bool arrayFull;

//functions
uint8_t returnDutyLHalf();
uint8_t returnDutyRHalf();
uint8_t returnPeriodHalf();
void updateDutyCycle();
void setDutyCycleVoltage(uint16_t vinD);
void setSpeedGrade(uint16_t speed);
void addCurrent(uint16_t adcCurrentReading);
void addVoltage(uint16_t adcVoltageReading);


#endif /* CALCULATIONS_H_ */