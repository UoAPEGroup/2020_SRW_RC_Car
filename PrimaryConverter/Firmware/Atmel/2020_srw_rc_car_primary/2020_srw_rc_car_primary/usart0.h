/*
 * usart0.h
 *
 * Created: 12/18/2020 10:32:06 AM
 *  Author: Kimsong Lor
 */ 


#ifndef USART0_H_
#define USART0_H_

#include "common.h"

#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void uart0_init(uint32_t baud_rate); //initializes UART, input baud_rate
void uart0_transmit_byte(char byte); //Transmit a byte
void uart0_transmit_array(char* msg); //Transmit each byte using uart0_transmit_byte(char byte)

#endif /* USART0_H_ */