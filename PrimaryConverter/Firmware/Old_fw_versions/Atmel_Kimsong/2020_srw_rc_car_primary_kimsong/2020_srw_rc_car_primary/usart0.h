/*
 * usart0.h
 *
 * Created: 16/12/2020 4:00:44 pm
 *  Author: achu072
 */ 


#ifndef USART0_H_
#define USART0_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void usart0_init(uint32_t BAUD);
void usart0_transmit_byte(uint8_t byte);
void usart0_transmit_string(char *string);
void usart0_transmit_data(uint32_t arr[]);
//void usart0_transmit_pwmtest();


#endif /* USART0_H_ */