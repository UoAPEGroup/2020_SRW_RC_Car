/*
 * PI_Control.h
 *
 * Created: 2/02/2021 4:57:07 AM
 *  Author: Manoj Kumaraguru
 */ 

#include <stdbool.h>

#ifndef PI_CONTROL_H_
#define PI_CONTROL_H_

void calculateError(uint16_t measuredVolt);
bool returnErrorCalcFlag();
void setErrorCalcFlag();
int32_t returnOutput();



#endif /* PI_CONTROL_H_ */