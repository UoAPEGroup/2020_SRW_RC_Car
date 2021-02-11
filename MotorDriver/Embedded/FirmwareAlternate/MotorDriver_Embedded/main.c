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
	//Init_PWM(50, 100);
	//
	//OCR0A = 100;
	//OCR0B = 50;
	
	Init_PWM_Fixed_Top(50);
	
    ///////////////		LOOP		///////////////
    while (1) 
    {
    }
}

