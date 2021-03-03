/*
 * inputStates.h
 *
 * Created: 18/01/2021 3:34:38 PM
 *  Author: htom380
 */ 


#ifndef INPUTSTATES_H_
#define INPUTSTATES_H_

/********************* Control Value Bit Macros ********************/

#define FUTURE 7
#define FULL 6
#define HALF 5
#define TURN 4
#define DRT 3
#define SPEED_HIGH 2
#define SPEED_MED 1
#define SPEED_LOW 0


/*******************************************************************/


//-----------------------------------------------------------------//


/*********************** STEERING THRESHOLDS ***********************/
// 200mV Interval for everything except Straight
#define ADC_STR_FULL_L 1200
#define ADC_STR_HALF_L 1000
#define ADC_STR_STRGHT 700
#define ADC_STR_HALF_R 500
#define ADC_STR_FULL_R 300

/*******************************************************************/


//-----------------------------------------------------------------//


/************************* STEERING STATES *************************/

#define STR_FULL_L 0
#define STR_HALF_L 1
#define STR_STRGHT 2
#define STR_HALF_R 3
#define STR_FULL_R 4

/*******************************************************************/



//-----------------------------------------------------------------//



/********************* ACCELERATION STATES *************************/

#define ACCEL_NONE 0
#define ACCEL_LOW 1
#define ACCEL_MEDIUM 2
#define ACCEL_HIGH 3


//-----------------------------------------------------------------//


/*********************** DIRECTION STATES **************************/

#define FORWARD 0
#define REVERSE 1

/*******************************************************************/

#endif /* INPUTSTATES_H_ */