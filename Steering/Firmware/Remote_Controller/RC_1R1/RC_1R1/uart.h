/*
 * uart.h
 *
 * Created: 12/01/2021 11:00:27 AM
 *  Author: htom380
 */ 


#ifndef UART_H_
#define UART_H_

#include "global.h"



void usart_init(uint32_t baud_val);
void usart_transmit(char byte);
void usart0_transmit_string(char *string);
void usart0_transmit_byte(uint8_t byte);



#endif /* UART_H_ */