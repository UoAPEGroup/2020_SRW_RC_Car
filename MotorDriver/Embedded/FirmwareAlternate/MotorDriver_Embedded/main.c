/*
 * MotorDriver_Embedded.c
 *
 * Created: 20/01/2021 12:17:24 pm
 * Author : cmcd407
 */ 

#include <avr/io.h>

#include "PWM_Driver.h"


///////////////		MAIN		///////////////
int main(void)
{
	Init_PWM(100,200);
	
	OCR0A = 200;
	OCR0B = 50;
	
    ///////////////		LOOP		///////////////
    while (1) 
    {
    }
}

