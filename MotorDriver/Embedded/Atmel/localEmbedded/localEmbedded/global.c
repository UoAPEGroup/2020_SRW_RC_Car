/*
 * global.c
 *
 * Created: 19/01/2021 1:09:42 pm
 *  Author: Earlene
 */ 

#include <stdint.h>
#include <stdbool.h> 

//make sure these are true when running actual code
volatile bool lostRemoteConnection = false;
volatile bool overCurrent = false;
volatile bool overVoltage = false;
volatile bool establishedConnection = false;

volatile uint8_t rotCount = 0;
volatile uint8_t oneSecCounter = 0;