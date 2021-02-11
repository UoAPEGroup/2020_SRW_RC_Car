/*
 * PWM_Driver.h
 *
 * Created: 20/01/2021 12:20:22 pm
 *  Author: cmcd407
 *
 * Use:
 *
 *
 *
 */ 

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

///////////////		Includes		///////////////
#include <avr/common.h>
#include <avr/io.h>


///////////////		Functions		///////////////

/* Initialise PWM */
void Init_PWM(uint8_t Duty_Cycle_Percentage, uint8_t Max_Period);

/* Initialise PWM, but with output to OCR0A and fixed top of 255 */
void Init_PWM_Fixed_Top(uint8_t Duty_Cycle_Percentage);


/* Find */
uint8_t Find_Duty_Cycle_Period(uint8_t Duty_Cycle_Percentage, uint8_t Max_Period);

/* */




#endif /* PWM_DRIVER_H_ */