/*
 * uart.h
 *
 * Created: 12/01/2021 11:00:27 AM
 *  Author: htom380
 */ 


#ifndef UART_H_
#define UART_H_

#include "global.h"

#define UBRR0_VAL F_CPU/(BAUD_RATE)*16 - 1								// UBRR0 value required to set Baud Rate of UART

void usart_init();
void usart_transmit(char byte);



#endif /* UART_H_ */