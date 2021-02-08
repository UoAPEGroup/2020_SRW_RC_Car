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
	adcInit();
	timerInit();
	pwmInit();
	sei();

    while (1) 
    {
		if(returnErrorCalcFlag()) {
			setPWM(returnOutput());
			setErrorCalcFlag();
		}
    }
}
