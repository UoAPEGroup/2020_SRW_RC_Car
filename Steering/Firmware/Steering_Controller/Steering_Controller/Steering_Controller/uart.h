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

#endif /* UART_H_ */