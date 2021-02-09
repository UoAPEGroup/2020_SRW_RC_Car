/*
 * uart.c
 *
 * Created: 12/01/2021 11:00:53 AM
 *  Author: htom380
 */ 

// Initialise USART for transmission and transmission interrupts.


void usart_init(uint32_t baud_val) {
	cli();														// Disable global interrupts for UART init.
	
	UBRR0 = F_CPU/(baud_val)*16 - 1;								// Set UART Baud Rate
	
	UCSR0B |= (1 << TXEN0);										// Enable UART transmission
	//UCSR0B |= (1 << RXEN0);									// Enable UART receiver

	UCSR0B |= (1 << TXCIE0);										// Enable interrupt when a Tx operation is complete
	sei();														// Re-enable global interrupts
}

void usart_transmit(char byte) {
	while ( !(UCSR0A & ( 1 << UDRE0)) ) {
		
	}
	UDR0 = byte;
}

//#define UBRR0_VAL F_CPU/(BAUD_RATE)*16 - 1								// UBRR0 value required to set Baud Rate of UART
