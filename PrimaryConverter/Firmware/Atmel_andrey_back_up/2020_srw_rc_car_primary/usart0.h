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
void usart0_transmit_reset_msg();
void usart0_transmit_halt_msg();
void usart0_transmit_start_up_msg();
void usart0_transmit_system_ready_msg();
void usart0_echo_user_command();
void usart0_clr_RX_buffer();
void usart0_set_TX_timer_flag();
void usart0_clr_TX_timer_flag();
bool usart0_get_TX_timer_flag();
void usart0_set_TX_send_data_flag();
void usart0_clr_TX_send_data_flag();
bool usart0_get_TX_send_data_flag();
void usart0_set_TX_reset_flag();
void usart0_clr_TX_reset_flag();
bool usart0_get_TX_reset_flag();
void usart0_set_TX_system_active_flag();
void usart0_clr_TX_system_active_flag();
bool usart0_get_TX_system_active_flag();
void usart0_clr_TX_all_flags();

#endif /* USART0_H_ */