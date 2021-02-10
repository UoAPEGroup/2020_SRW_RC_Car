/*
 * PiControllerActivity.c
 *
 * Created: 18/01/2021 2:00:23 PM
 * Author : Manoj Kumaraguru
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "adc.h"
#include "timer.h"
#include "pwm.h"
#include "PI_Control.h"

int main(void)
{
	//Initialise modules and ports
	DDRC |= (1<<PORTC2);
	adcInit();
	timerInit();
	pwmInit();
	sei();

    while (1) 
    {
		//Check if error has been calculated
		
		if(returnErrorCalcFlag()) {
			cli(); 
			setPWM(returnOutput()); //Adjust pwm through PI controller
			setErrorCalcFlag(); //Reset flag
			
			sei();
		}
		//PINC ^= (1<<PORTC2); //debug led
    }
}
