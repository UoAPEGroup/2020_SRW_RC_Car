/*
 * uart.h
 *
 * Created: 28/01/2021 12:14:12 pm
 *  Author: npat692
 */ 


#ifndef UART_H_
#define UART_H_

#include "global.h"

void usart0_init(uint32_t BAUD);
void usart0_transmit_byte(uint8_t byte);
void usart0_transmit_string(char *string);



#endif /* UART_H_ */