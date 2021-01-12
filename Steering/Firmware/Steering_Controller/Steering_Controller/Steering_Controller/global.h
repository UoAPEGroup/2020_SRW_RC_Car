/*
 * global.h
 *
 * Created: 11/01/2021 10:06:53 am
 *  Author: npat692
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

// Global Variables
#define F_CPU 8000000UL
#define BAUD_RATE 9600
#define VREF 5000

// STATE Definitions
#define STATIONARY_STR 0
#define LEFT_HALF 1
#define LEFT_FULL 2
#define RIGHT_HALF 3
#define RIGHT_FULL 4

// Motor Controller 
#define STATE_INT_H PORTC |= (1 << PC5)
#define STATE_INT_L PORTC &=~ (1 << PC5)

#define DRT_FWD PORTC |= (1 << PC4)
#define DRT_BCK PORTC &=~ (1 << PC4)

#define SPD_0_H PORTC |= (1 << PC2)
#define SPD_0_H PORTC &=~ (1 << PC2)

#define SPD_1_H PORTC |= (1 << PC3)
#define SPD_1_H PORTC &=~ (1 << PC3)

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


#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#endif /* GLOBAL_H_ */