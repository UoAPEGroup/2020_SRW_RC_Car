/*
 * global.c
 *
 * Created: 19/01/2021 1:09:42 pm
 *  Author: Earlene
 */ 

#include <stdint.h>
#include <stdbool.h> 

extern volatile bool lostRemoteConnection = true;
extern volatile bool overCurrent = true;
extern volatile bool overVoltage = true;