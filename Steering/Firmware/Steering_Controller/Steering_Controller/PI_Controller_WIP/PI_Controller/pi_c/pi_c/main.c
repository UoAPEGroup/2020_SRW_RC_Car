/*
 * pi_c.c
 *
 * Created: 18/01/2021 10:52:43 am
 * Author : npat692
 */ 

#include "global.h"
#include "setup.h"
#include "pi_c.h"
#include "adc_pwm.h"

uint16_t adc_1;

ISR(TIMER2_COMPA_vect){
	loop();
}

int main(void)
{
	led_init();
	pwm_init();
	adc_init();
	timer2_init();
	setup();
	
	sei();
    /* Replace with your application code */
    while (1) {
		//analog_write(4000);
		//adc_1 = adc_read();
		
		
    }
}

