/*
 * PWM_Peripheral.c
 *
 * Created: 20/01/2021 12:18:41 pm
 *  Author: cmcd407
 */ 

#include "PWM_Driver.h"

///////////////		Defines			///////////////
#define PWM_OUTPUT_PIN	PD5


///////////////		Functions		///////////////

void Init_PWM(uint8_t Duty_Cycle_Percentage, uint8_t Max_Period)
{
	/*
		Phase Correct PWM Mode:
			Bottom->Top->Bottom pattern
			Bottom:		Where the count switches to up-counting, at 0x00
			Top:		Where the count switches to down-counting, at OCRA
		
		With a timing of:
			Period Count		= (Top->Bottom) + (Bottom->Top)
			Duty Cycle Count	= (Value->Bottom) + (Bottom->Value)
		
		Where the timing values are:
			Frequency			= (fcpu / prescaler) / (2*(top - bottom))
			Period				= 1 / Frequency
			Duty Cycle			= percentage (0->1) * period count
			
		Thus if fcpu = 8 MHz then for a frequency of 40 kHz...
			Prescaler = 1, bottom = 0, top = 100
			Period				= 1/40 kHz = 25 ms
			Thus duty cycle granularity is 1/200 = 0.5% 
	*/
	
	DDRD |= (1 << PWM_OUTPUT_PIN);			// set OC0B pin to output
	
	
	TCCR0A |= (1 << COM0B1);				// clear OC0B on compare match on up-count, set on down-count
	
	OCR0A = Max_Period;						// Set the TOP
	OCR0B = Find_Duty_Cycle_Period(Duty_Cycle_Percentage, Max_Period);	// Set the COMPARE
	
	TCCR0A |= (1 << WGM00);					// set mode as PWM phase correct (OCRA as top)
	TCCR0B |= (1 << WGM02);					//
	
	// Activate timer:
	TCCR0B |= (1 << CS00);					// set prescaler as 1
}






uint8_t Find_Duty_Cycle_Period(uint8_t Duty_Cycle_Percentage, uint8_t Max_Period)
{
	if (Duty_Cycle_Percentage > 100) {Duty_Cycle_Percentage = 100;}
	
	uint8_t Duty_Cycle_Period = (uint8_t)(((uint16_t)(Max_Period) * (Duty_Cycle_Percentage))/100);
	
	
	if (Duty_Cycle_Period >= Max_Period) {
		return Max_Period;
	} else {
		return Duty_Cycle_Period;
	}
	
}
