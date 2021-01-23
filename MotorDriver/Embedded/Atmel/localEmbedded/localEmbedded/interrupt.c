/*
 * interrupt.c
 *
 * Created: 19/01/2021 10:10:13 pm
 *  Author: Earlene
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Calculations.h"
#include "global.h"

static volatile uint8_t interruptCount = 0;

ISR(INT0_vect) {
	
	DDRB |= (1 << DDB0);
	PORTB ^= (1 << 0);
	
	//read any state changes and set variables as needed
	//PC3 - PC5
	
	if ((PINC & (1 << PINC5)) == (1 << PINC5)) {
		setDirection(true); //set direction as forward if pinc3 is high
	}
	else {
		setDirection(false);
	}
	
	//read the speed pins and set the speed grade accordingly
	
	if (!lostRemoteConnection && !overCurrent && !overVoltage) {
	
		if ((PINC & (1 << PINC4)) == (1 << PINC4)) {
		
			//if (11) then:
			if ((PINC & (1 << PINC3)) == (1 << PINC3)) {
				setSpeedGrade(MAX_VOLTAGE);
			}
		
			//if (10) then:
			else {
				setSpeedGrade(MID_VOLTAGE);
			}	
		}
	
		else {
		
			//if (01) then:
			if ((PINC & (1 << PINC3)) == (1 << PINC3)) {
				setSpeedGrade(MIN_VOLTAGE);
			}
		
			//if (00) then:
			else {
				setSpeedGrade(STOP);
			}
		
		}
		
		}
		
	interruptCount++;
	
}

//set up external interrupt on INT0 pin
void interrupt_init() {
	
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);
}