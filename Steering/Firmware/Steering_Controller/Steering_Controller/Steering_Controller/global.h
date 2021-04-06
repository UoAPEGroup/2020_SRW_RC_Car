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
#define VREF 3300
#define ADC_RES 1024

// PI Controller 
#define K_P 0.3 // Proportional Gain
#define K_I 0.1 // Integral Gain
#define MAX_LIMIT 3300 
#define MIN_LIMIT 0
#define SAMPLING_TIME 0.001

// Steering Motor Control
#define IN_1_ON TCCR1A |= (1 << COM1A1)
#define IN_1_OFF TCCR1A &=~ (1 << COM1A1)

#define IN_2_ON TCCR0A |= (1 << COM0A1)
#define IN_2_OFF TCCR0A &=~ (1 << COM0A1)

#define CHECK_IN_1  (TCCR0A & (1 << COM0A1))
#define CHECK_IN_2  (TCCR1A & (1 << COM1A1))

// Set point variable for PI Controller
volatile int16_t set_point_angle;
uint16_t turn_range;

// Duty cycle to set PWM
volatile int16_t t_on;

// Timeout Counter
#define STATE_CONNECT_COUNT 500 // in ms
#define MAX_TIMEOUT_COUNT 500 // in ms
volatile uint8_t timeout_count;

// Calibration timer
volatile uint8_t calibration_count;
#define CALIBRATION_MAX 200

#endif /* GLOBAL_H_ */