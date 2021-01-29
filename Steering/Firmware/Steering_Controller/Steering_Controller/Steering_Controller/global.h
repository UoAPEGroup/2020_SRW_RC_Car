/*
 * global.h
 *
 * Created: 11/01/2021 10:06:53 am
 *  Author: npat692
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

// Global Variables
#define F_CPU 8000000UL
#define BAUD_RATE 9600
#define VREF 5000
#define ADC_RES 1024

// PI Controller 
#define K_P 0.8
#define K_I 1
#define MAX_LIMIT 5000
#define MIN_LIMIT 0
#define SAMPLING_TIME 0.001

// Steering Motor Control
#define IN_1_ON TCCR0A |= (1 << COM0A1)
#define IN_1_OFF TCCR0A &=~ (1 << COM0A1)

#define IN_2_ON TCCR1A |= (1 << COM1A1)
#define IN_2_OFF TCCR1A &=~ (1 << COM1A1)

// STATE Definitions
#define STATIONARY_STATE 0
#define ACTIVE_STATE 1

#define STRAIGHT 1
#define LEFT_HALF 2
#define LEFT_FULL 3
#define RIGHT_HALF 4
#define RIGHT_FULL 5

// Motor Controller 
#define STATE_INT_H PORTC |= (1 << PC5)
#define STATE_INT_L PORTC &=~ (1 << PC5)

// STATE INTERRUPT TRIGGER
#define STATE_INT_TOGGLE PORTC ^= (1 << PC5)

#define DRT_FWD PORTC &=~ (1 << PC4)
#define DRT_BCK PORTC |= (1 << PC4)

#define SPD_0_H PORTC |= (1 << PC2)
#define SPD_0_L PORTC &=~ (1 << PC2)

#define SPD_1_H PORTC |= (1 << PC3)
#define SPD_1_L PORTC &=~ (1 << PC3)

char input_data;
uint8_t system_state;
uint8_t turn_state;


#endif /* GLOBAL_H_ */