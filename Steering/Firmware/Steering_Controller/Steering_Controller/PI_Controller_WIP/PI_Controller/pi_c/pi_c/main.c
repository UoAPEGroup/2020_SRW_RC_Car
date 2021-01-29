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
#include "uart.h"

char input_buffer[20];

ISR(TIMER2_COMPA_vect){
	pi_controller();
}

int main(void)
{
	led_init();
	pwm_init();
	adc_init();
	timer2_init();
	setup();
	usart0_init(9600);
	sei();
    while (1) {

    }
}

