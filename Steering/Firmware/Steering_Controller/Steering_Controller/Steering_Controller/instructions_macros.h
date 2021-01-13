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
#define HALF_L_BLOW_S 0b00101001 // Half Left Turn and Backward Low Speed
#define HALF_L_BMED_S 0b00101010 // Half Left Turn and Backward Medium Speed
#define HALF_L_BHIGH_S 0b00101100 // Half Left Turn and Backward High Speed

#define FULL_L_BLOW_S 0b01001001 // Full Left Turn and Backward Low Speed
#define FULL_L_BMED_S 0b01001010 // Full Left Turn and Backward Medium Speed
#define FULL_L_BHIGH_S 0b01001100 // Full Left Turn and Backward High Speed


/*
#define STATIONARY 0x40 // Stationary

// FORWARD
#define HALF_L_NO_S 0x41 // Half Left Turn and No Speed
#define HALF_L_FLOW_S 0x42 // Half Left Turn and Forward Low Speed
#define HALF_L_FMED_S 0x43 // Half Left Turn and Forward Medium Speed
#define HALF_L_FHIGH_S 0x44 // Half Left Turn and Forward High Speed

#define FULL_L_NO_S 0x45 // Full Left Turn and No Speed
#define FULL_L_FLOW_S 0x46 // Full Left Turn and Forward Low Speed
#define FULL_L_FMED_S 0x47 // Full Left Turn and Forward Medium Speed
#define FULL_L_FHIGH_S 0x48 // Full Left Turn and Forward High Speed

// BACKWARD
#define HALF_L_BLOW_S 0x50 // Half Left Turn and Backward Low Speed
#define HALF_L_BMED_S 0x51 // Half Left Turn and Backward Medium Speed
#define HALF_L_BHIGH_S 0x52 // Half Left Turn and Backward High Speed

#define FULL_L_BLOW_S 0x53 // Full Left Turn and Backward Low Speed
#define FULL_L_BMED_S 0x54 // Full Left Turn and Backward Medium Speed
#define FULL_L_BHIGH_S 0x55 // Full Left Turn and Backward High Speed
*/


#endif /* INSTRUCTIONS_MACROS_H_ */