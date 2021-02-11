/*
 * global.h
 *
 * Created: 19/01/2021 1:09:56 pm
 *  Author: Earlene
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_VOLTAGE 9500
#define MID_VOLTAGE 7000
#define MIN_VOLTAGE 5000
#define STOP 0

#define REQUIRED_INTERRUPT_COUNT 4

extern volatile bool lostRemoteConnection;
extern volatile bool overCurrent;
extern volatile bool overVoltage;
extern volatile bool establishedConnection;

extern volatile uint8_t rotCount;


#endif /* GLOBAL_H_ */