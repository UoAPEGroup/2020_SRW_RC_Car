/*
 * uart.h
 *
 * Created: 11/01/2021 10:05:51 am
 *  Author: npat692
 */ 


#ifndef UART_H_
#define UART_H_

#include "global.h"
#include "control.h"

void uart_init();
void tx_debug();
void check_timeout();
void stall_control();
void reset_timeout();

// UART Debugging 
void usart0_transmit_byte(uint8_t byte);
void usart0_transmit_string(char *string);

#endif /* UART_H_ */