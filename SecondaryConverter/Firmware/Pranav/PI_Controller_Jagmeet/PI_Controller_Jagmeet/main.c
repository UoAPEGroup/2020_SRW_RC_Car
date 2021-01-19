/*
 * PI_Controller_Jagmeet.c
 *
 * Created: 18/01/2021 12:00:29 pm
 * Author : pgul065
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 800000UL


int main(void)
{
	
	//Provided Code---
	double Kp = 2;
	double Ki = 5;
	double Kd = 1;
	
	unsigned long currentTime, previousTime;
	double elapsedTime;
	double error;
	double lastError;
	double input, output, setPoint;
	double cumError, rateError;
	
	
	void setup(){
		setPoint = 0;
	}
	
	void loop(){
		input = analogRead(A0);
		output = computePID(input);
		_delay_ms(100);
		analogWrite(3, output);
	}
	
	double computePID(double inp){
		currentTime = millis();
		elapsedTime = (double)(currentTime - previousTime);
		
		error = setPoint - inp;
		cumError += error*elapsedTime;
		rateError = (error - lastError)/elapsedTime;
		
		double out = Kp*error + Ki*cumError + Kd*rateError;
		
		lastError = error;
		previousTime = currentTime;
		
		return out;
	}
	//---
	
    while (1) 
    {
    }
}


void adc_init(){
	
	//ADMUX = 0b01000010; //Setting reference voltage to be  AVcc, Reading from pin ADC2.
	ADMUX |= ((1 << REFS0) | (1 << MUX1));
	//ADCSRA = 0b10000101; //Enabling the ADC, Setting the Pre-scaler to 32.
	ADCSRA |= ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS0));
	//ADCSRB = 0b00000000; //Setting ADC to free running mode.
	
}


uint16_t adc_read(uint8_t channel){
	//Clearing the register that stores the channel selection and setting it to the one provided.
	ADMUX &= 0xF0;
	ADMUX |= channel;
	
	//Starting an ADC conversion
	ADCSRA |= (1 << ADSC);
	
	//Polling for conversion to finish.
	while ((ADCSRA & (1 << ADIF)) == 0) {
		; //If ADIF bit is not 0, wait until it becomes 0
	}
	
	//Returning the ADC result stored in the registers.
	return ((ADCL << 0) | (ADCH << 8));
}

double adc_convert(uint16_t value){
	
	double voltageVal;
	
	voltageVal = ((uint32_t)value * 5)/(double)1024;
	
	return voltageVal;
}



void timer0_init()
{
	//TCCR0A = 0b01000010; //WGM0[2..0] should be set to 010 for CTC mode
	//TCCR0B = 0b00000011; //When running we need to load 011 to CS0[2..0] for a prescaler of 64
	//OCR0A = 12; //Loading OCR0A with 124 to get a period of 10ms - Trying to change to 1ms
	//Enabling the Output Compare Match A Interrupt
	//TIMSK0 |= (1<<OCIE0A);
	
}

bool timer0_checkAndClearCompare()
{
	//Checking if the timer has overflowed - reached 124
	if((TIFR0 & (1<<OCF0A)) != 0){
		//Clearing the overflow flag
		TIFR0 |= (1 << OCF0A);
		return true;
	}
	
	return false;

}