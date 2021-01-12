/*
 * usart0.c
 *
 * Created: 16/12/2020 4:00:34 pm
 *  Author: achu072
 */ 

#include "common.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "usart0.h"
#include "timer_control.h"
#include "calc.h"

#define TX_BUFFER		20
#define RX_BUFFER		4
#define ASCII_OFF		48

static volatile uint8_t RX_counter  = 0;
static volatile uint8_t RX_data_buffer[RX_BUFFER];
static volatile bool usart0_TX_flag = false;

//set up asynchronous USART0, 8N1, no parity
void usart0_init(uint32_t BAUD)
{
	UCSR0A |= 0x00;															//clear all bits
	UCSR0B |= (1 << RXCIE0);												//enable RX complete interrupt
	//UCSR0B |= (1 << TXCIE0);												//enable TX complete interrupt
	//UCSR0B |= (1 << UDRIE0);												//enable TX data register empty interrupt
	UCSR0B |= (1 << RXEN0);													//receiver enable
	UCSR0B |= (1 << TXEN0);													//transmitter enable
	UCSR0C |= ((1 << UCSZ01) | (1 << UCSZ00));								//8-bit packet size
	UCSR0C &= ~(1 << UCPOL0);												//clear polarity bit - not used
	UBRR0 = F_CPU / (16 * BAUD) - 1;										//set UBRR
}

//transmit one byte of data
void usart0_transmit_byte(uint8_t byte)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {
		;
	}
	
	UDR0 = byte;
}

//transmit string
void usart0_transmit_string(char *string)
{
	for (uint8_t i = 0; i < strlen(string); i++) {
		usart0_transmit_byte(string[i]);
	}
}

//transmit formatted ADC data 
void usart0_transmit_data(uint32_t temp1, uint32_t temp2, uint32_t temp3, uint32_t isens, uint32_t vsens)
{
	char buffer_temp1[TX_BUFFER];						
	char buffer_temp2[TX_BUFFER];
	char buffer_temp3[TX_BUFFER];
	char buffer_isens[TX_BUFFER];
	char buffer_vsens[TX_BUFFER];
	
	sprintf(buffer_temp1, "TEMP1:	%ld\n\r", temp1);
	sprintf(buffer_temp2, "TEMP2:	%ld\n\r", temp2);
	sprintf(buffer_temp3, "TEMP3:	%ld\n\r", temp3);
	sprintf(buffer_isens, "ISENS:	%ld\n\r", isens);
	sprintf(buffer_vsens, "VSENS:	%ld\n\r\n\r", vsens);
	
	usart0_transmit_string("ADC_DATA\n\r--------\n\r");
	usart0_transmit_string(buffer_temp1);
	usart0_transmit_string(buffer_temp2);
	usart0_transmit_string(buffer_temp3);
	usart0_transmit_string(buffer_isens);
	usart0_transmit_string(buffer_vsens);
}

//transmit test data for generated PWM waves
void usart0_transmit_pwmtest()
{
	char test_message[500];
	sprintf(test_message,	"PWM_TEST\n\r"
							"--------\n\r"
							"RX_BUF		= %d%d%d\n\r"
							"DUTY_CYC	= %d\n\r"
							"OCR0B		= %d\n\r"
							"OCR2B		= %d\n\r\n\r",
				
							RX_data_buffer[0] - ASCII_OFF, 
							RX_data_buffer[1] - ASCII_OFF, 
							RX_data_buffer[2] - ASCII_OFF, 
							timer_control_get_duty(), 
							OCR0B, 
							OCR2B);
							
	usart0_transmit_string(test_message);
}

//set, clear,get usart0 TX flag
void usart0_set_TX_flag()
{
	usart0_TX_flag = true;
}

void usart0_clr_TX_flag()
{
	usart0_TX_flag = false;	
}

bool usart0_get_TX_flag()
{
	return usart0_TX_flag;
}

//on receive complete interrupt
ISR(USART0_RX_vect) {
	RX_data_buffer[RX_counter] = UDR0;										//record byte from usart0 on user TX
	RX_counter++;		
	
	if (RX_counter > 2) {
		RX_counter = 0;
		uint8_t duty_cycle = calc_make_duty_cycle(RX_data_buffer);
		timer_control_set_duty_on_user(duty_cycle);							//set duty cycle
	}
}