/*
 * usart0.h
 *
 * Created: 16/12/2020 4:00:44 pm
 *  Author: achu072
 */ 


#ifndef USART0_H_
#define USART0_H_

#include <stdbool.h>

void usart0_init(uint32_t BAUD);
void usart0_transmit_byte(uint8_t byte);
void usart0_transmit_string(char *string);
void usart0_transmit_data(uint32_t temp1, uint32_t temp2, uint32_t temp3, uint32_t isens, uint32_t vsens);
void usart0_transmit_pwmtest();
void usart0_set_TX_flag();
void usart0_clr_TX_flag();
bool usart0_get_TX_flag();

#endif /* USART0_H_ */