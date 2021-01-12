/*
 * instructions_macros.h
 *
 * Created: 12/01/2021 1:50:57 pm
 *  Author: npat692
 */ 


#ifndef INSTRUCTIONS_MACROS_H_
#define INSTRUCTIONS_MACROS_H_


/* 
==================================
Bit Instructions 
==================================
 
| FUTURE | FULL | HALF | TURN (L/R) | DRT (FWD/BWD) | HIGH | MED | LOW |
*/

#define STATIONARY 0b00000000 // Stationary 

// FORWARD
#define HALF_L_NO_S 0b00100000 // Half Left Turn and No Speed
#define HALF_L_FLOW_S 0b00100001 // Half Left Turn and Forward Low Speed
#define HALF_L_FMED_S 0b00100010 // Half Left Turn and Forward Medium Speed
#define HALF_L_FHIGH_S 0b00100100 // Half Left Turn and Forward High Speed

#define FULL_L_NO_S 0b01000000 // Full Left Turn and No Speed
#define FULL_L_FLOW_S 0b01000001 // Full Left Turn and Forward Low Speed
#define FULL_L_FMED_S 0b01000010 // Full Left Turn and Forward Medium Speed
#define FULL_L_FHIGH_S 0b01000100 // Full Left Turn and Forward High Speed

// BACKWARD
#define FULL_L_NO_S 0b01001000 // Full Left Turn and No Speed
#define HALF_L_BLOW_S 0b00101001 // Half Left Turn and Backward Low Speed
#define HALF_L_BMED_S 0b00101010 // Half Left Turn and Backward Medium Speed
#define HALF_L_BHIGH_S 0b00101100 // Half Left Turn and Backward High Speed

#define FULL_L_BLOW_S 0b01001001 // Full Left Turn and Backward Low Speed
#define FULL_L_BMED_S 0b01001010 // Full Left Turn and Backward Medium Speed
#define FULL_L_BHIGH_S 0b01001100 // Full Left Turn and Backward High Speed


#endif /* INSTRUCTIONS_MACROS_H_ */