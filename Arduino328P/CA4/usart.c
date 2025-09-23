#include "usart.h"
#include <avr/io.h>
#define F_CPU 16000000UL  // UL - Unsigned long to fit in the 16000000 as a 32/64-bit integer
#include <util/delay.h>

/*****************************************************
 * Initialize USART for 9600 baud, 8 data bits, no parity, 1 stop bit (8N1)
 ****************************************************/
void usartInit(void){
    // PORTB|= (1<<5); // Makes bit 5 a 1 by OR, without interfering with other bits. Copies, modifies and writes 
    // UCSR0B = 0x1C; // 0b 0001 1100
    // UCSR0B |= (1<<3); // 1 left shifted to position 3. Enables TXer (Transmitter)
    UCSR0B |= (1 << TXEN0); //Enabling transmit pin
	UCSR0B |= (1 << RXEN0); //Enabling receive pin 

   
    // Data register UDRn is used to send data out
    // Put USART in UART mode
    UCSR0C &= ~(1 << UMSEL00); // Always a 1 is shifted and never a 0
    UCSR0C &= ~(1 << UMSEL01);

    // 8-bit data 
    UCSR0C |= ((1 << UCSZ00) | (1 << UCSZ01)); // Creates and ORs 2 masks in the right places. Can only do 2 at a time
    UCSR0B &= ~(1 << UCSZ02);

    // No parity 
    UCSR0C &= ~((1 << UPM00) | (1 << UPM01)); // Clears 2 bits at once. Can only do 2 at a time!
    
    // 1 Stop bit
    UCSR0C &= ~(1 << USBS0);

    // 9600 BAUD
    UCSR0A &= ~(1 << U2X0); // Not using BAUD rate doubler
    UBRR0 = 103;
}
/*****************************************************
 * Send a single character via USART
 ****************************************************/
void usartSendChar(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for the transmit buffer to be empty
    UDR0 = c; // Load character into the buffer
}
/*****************************************************
 * Send a string via USART
 ****************************************************/
void usartSendString(char str[])
{
    uint8_t i = 0;
    while (str[i] != '\0') // Loop until the null terminator is reached
    {
        usartSendChar(str[i]);
        i++;
    }
}
/*****************************************************
 * Check if a character has been received
 ****************************************************/
uint8_t usartCharReceived(void)
{
    return UCSR0A & (1 << RXC0);
}
/*****************************************************
 * Read the received character from the buffer
 ****************************************************/
char usartReadChar(void)
{
    while (!(UCSR0A & (1 << RXC0))); // Wait until a character is available
    return UDR0; // Read and return the received character
}

// UCSR0A |= (); // Mainly used for receiving data
//uint8_t - Unsigned integer of length 8 bits.