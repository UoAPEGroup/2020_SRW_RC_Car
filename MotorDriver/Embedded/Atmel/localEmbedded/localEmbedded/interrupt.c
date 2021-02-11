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

static volatile uint16_t interruptCount = 0;
static volatile uint8_t consecutiveChange = 0;



ISR(INT0_vect) {
	
	DDRB |= (1 << DDB0);
	PORTB ^= (1 << 0);
	
	//read any state changes and set variables as needed
	//PC3 - PC5
	
	interruptCount++;

	if ((PINC & (1 << PINC5)) == (1 << PINC5)) {
		setRequiredDirection(true);
		//setDirection(true); //set direction as forward if pinc3 is high
	}
	else {
		setRequiredDirection(false);
		//setDirection(false);
	}
	
	//read the speed pins and set the speed grade accordingly
	
	if ((!lostRemoteConnection) && (!overCurrent) && (!overVoltage) && establishedConnection) {
		
		
		if ((PINC & (1 << PINC4)) == (1 << PINC4)) {
			
			//if (11) then:
			if ((PINC & (1 << PINC3)) == (1 << PINC3)) {
				setRequiredSpeedGrade(STOP);
				//setSpeedGrade(STOP);
			}
		
			//if (10) then:
			else {
				setRequiredSpeedGrade(MIN_VOLTAGE);
				//setSpeedGrade(MIN_VOLTAGE);
			}	
		}
	
		else {
			
			//if (01) then:
			if ((PINC & (1 << PINC3)) == (1 << PINC3)) {
				setRequiredSpeedGrade(MID_VOLTAGE);
				//setSpeedGrade(MID_VOLTAGE);
			}
		
			//if (00) then:
			else {
				setRequiredSpeedGrade(MAX_VOLTAGE);
				//setSpeedGrade(MAX_VOLTAGE);
			}
		
		}
		
	}
		
}

void resetInterruptCount() {
	interruptCount = 0;
}

uint16_t returnInterruptCount() {
	return interruptCount;
}

//timer3 compare match 3
ISR(TIMER3_COMPA_vect) {
	
	TIFR3 |= (1 << TOV3);
	
	DDRB |= (1 << DDB1);
	PORTB ^= (1 << DDB1);
	
	if (returnInterruptCount() >= (REQUIRED_INTERRUPT_COUNT)) {
		lostRemoteConnection = false;
		
		if (!establishedConnection) {
			consecutiveChange++;
			if (consecutiveChange >= 15) {
				establishedConnection = true;
			}
		}
		
	}
	else { //if contact is lost, stop the car
		lostRemoteConnection = true; //set lost remote connection flag to true
		establishedConnection = false;
		consecutiveChange = 0;
		setRequiredSpeedGrade(STOP);
	}
	
	resetInterruptCount();

}

//set up external interrupt on INT0 pin
void interrupt_init() {
	
	EICRA |= (1 << ISC00);
	EIMSK |= (1 << INT0);
}




