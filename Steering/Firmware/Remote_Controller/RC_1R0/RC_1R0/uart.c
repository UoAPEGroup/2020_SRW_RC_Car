/*
 * uart.c
 *
 * Created: 12/01/2021 11:00:53 AM
 *  Author: htom380
 */ 

// Initialise USART for transmission and transmission interrupts.
void usart_init() {
	cli();														// Disable global interrupts for UART init.
	
	UBRR0 = UBRR0_VAL;											// Set UART Baud Rate
	
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