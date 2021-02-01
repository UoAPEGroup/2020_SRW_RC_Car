/*
 * PI_Control.h
 *
 * Created: 2/02/2021 4:57:07 AM
 *  Author: Manoj Kumaraguru
 */ 


#ifndef PI_CONTROL_H_
#define PI_CONTROL_H_

void calculatePiVals(uint16_t measuredVolt);
bool returnErrorCalcFlag();
bool setErrorCalcFlag();



#endif /* PI_CONTROL_H_ */