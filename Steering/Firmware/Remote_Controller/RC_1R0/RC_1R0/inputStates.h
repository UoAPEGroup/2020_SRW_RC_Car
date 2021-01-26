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
#define HIGH 2
#define MEDIUM 1
#define LOW 0


/*******************************************************************/

/************************* STEERING STATES *************************/

#define STR_FULL_L 0
#define STR_MED_L 1
#define STR_STRGHT 2
#define STR_MED_R 3
#define STR_HARD_R 4

/*******************************************************************/



//-----------------------------------------------------------------//



/********************* ACCELERATION STATES *************************/

#define ACCEL_NONE
#define ACCEL_LOW
#define ACCEL_MEDIUM
#define ACCEL_HIGH

#endif /* INPUTSTATES_H_ */