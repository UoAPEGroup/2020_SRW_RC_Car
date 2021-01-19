 /*
 * Calculations.h
 *
 * Created: 18/12/2020 12:06:08 pm
 *  Author: yxin683
 */ 


#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

//variables
static volatile uint8_t finalOnTime;
static volatile uint8_t leftOnTime;
static volatile uint8_t rightOnTime;

static volatile uint16_t inputV;
static volatile uint16_t recentInputV;
static volatile uint16_t speedGrade;

static volatile uint16_t voltageValues;
static volatile uint16_t currentValues;

static volatile uint8_t count = 0;

//FLAGS
extern volatile bool arrayFull;

//functions
uint8_t returnLeftOnTime();
uint8_t returnRightOnTime();
uint8_t returnPeriodHalf();
void updateDutyCycle();
void setInputV(uint16_t vinD);
void setSpeedGrade(uint16_t speed);
void addCurrent(uint16_t adcCurrentReading);
void addVoltage(uint16_t adcVoltageReading);


#endif /* CALCULATIONS_H_ */