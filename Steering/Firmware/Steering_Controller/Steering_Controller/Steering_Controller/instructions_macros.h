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

// STRAIGHT FORWARD
#define STRAIGHT_FLOW_S 0b00000001
#define STRAIGHT_FMED_S 0b00000010
#define STRAIGHT_FHIGH_S 0b00000100

// STRAIGHT BACKWARD
#define STRAIGHT_BLOW_S 0b00001001
#define STRAIGHT_BMED_S 0b00001010
#define STRAIGHT_BHIGH_S 0b00001100

// ------------------------------------
// LEFT TURN 
// ------------------------------------
#define HALF_L_NO_S 0b00100000 // Half Left Turn and No Speed
#define FULL_L_NO_S 0b01000000 // Full Left Turn and No Speed

// HALF LEFT TURN AND FORWARD 
#define HALF_L_FLOW_S 0b00100001 // Half Left Turn and Forward Low Speed
#define HALF_L_FMED_S 0b00100010 // Half Left Turn and Forward Medium Speed
#define HALF_L_FHIGH_S 0b00100100 // Half Left Turn and Forward High Speed

// FULL LEFT TURN AND FORWARD 
#define FULL_L_FLOW_S 0b01000001 // Full Left Turn and Forward Low Speed
#define FULL_L_FMED_S 0b01000010 // Full Left Turn and Forward Medium Speed
#define FULL_L_FHIGH_S 0b01000100 // Full Left Turn and Forward High Speed

// HALF LEFT TURN AND BACKWARD
#define HALF_L_BLOW_S 0b00101001 // Half Left Turn and Backward Low Speed
#define HALF_L_BMED_S 0b00101010 // Half Left Turn and Backward Medium Speed
#define HALF_L_BHIGH_S 0b00101100 // Half Left Turn and Backward High Speed

// FULL LEFT TURN AND BACKWARD
#define FULL_L_BLOW_S 0b01001001 // Full Left Turn and Backward Low Speed
#define FULL_L_BMED_S 0b01001010 // Full Left Turn and Backward Medium Speed
#define FULL_L_BHIGH_S 0b01001100 // Full Left Turn and Backward High Speed

// ------------------------------------
// RIGHT TURN
// ------------------------------------
#define HALF_R_NO_S 0b00110000 // Half Right Turn and No Speed
#define FULL_R_NO_S 0b01010000 // Full Right Turn and No Speed

// HALF RIGHT TURN AND FORWARD
#define HALF_R_FLOW_S 0b00110001 // Half Right Turn and Forward Low Speed
#define HALF_R_FMED_S 0b00110010 // Half Right Turn and Forward Medium Speed
#define HALF_R_FHIGH_S 0b00110100 // Half Right Turn and Forward High Speed

// FULL RIGHT TURN AND FORWARD
#define FULL_R_FLOW_S 0b01010001 // Full Right Turn and Forward Low Speed
#define FULL_R_FMED_S 0b01010010 // Full Right Turn and Forward Medium Speed
#define FULL_R_FHIGH_S 0b01010100 // Full Right Turn and Forward High Speed

// HALF RIGHT TURN AND BACKWARD
#define HALF_R_BLOW_S 0b00111001 // Half Right Turn and Backward Low Speed
#define HALF_R_BMED_S 0b00111010 // Half Right Turn and Backward Medium Speed
#define HALF_R_BHIGH_S 0b00111100 // Half Right Turn and Backward High Speed

// FULL LEFT TURN AND BACKWARD
#define FULL_R_BLOW_S 0b01011001 // Full Right Turn and Backward Low Speed
#define FULL_R_BMED_S 0b01011010 // Full Right Turn and Backward Medium Speed
#define FULL_R_BHIGH_S 0b01011100 // Full Right Turn and Backward High Speed

#endif /* INSTRUCTIONS_MACROS_H_ */