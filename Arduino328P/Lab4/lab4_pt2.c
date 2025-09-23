#include <avr/io.h>

#define F_CPU 16000000UL // UL - Unsigned long to fit in the 16000000 as a 32/64-bit integer
#include <util/delay.h>

int main(void)
{
    // PORTB|= (1<<5); // Makes bit 5 a 1 by OR, without interfering with other bits. Copies, modifies and writes 
    // UCSR0B = 0x1C; // 0b 0001 1100
    // UCSR0B |= (1<<3); // 1 left shifted to position 3. Enables TXer (Transmitter)
    UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << RXEN0);

    // UCSR0A |= (); // Mainly used for receiving data 
    // Data register UDRn is used to send data out

    // Put USART in UART mode
    UCSR0C &= ~(1 << UMSEL00); // Always a 1 is shifted and never a 0
    UCSR0C &= ~(1 << UMSEL01);

    // 8-bit data 
    // UCSR0C |= (1<<UCSZ00);
    // UCSR0C |= (1<<UCSZ01);
    UCSR0C |= ((1 << UCSZ00) | (1 << UCSZ01)); // Creates and ORs 2 masks in the right places. Can only do 2 at a time
    UCSR0B &= ~(1 << UCSZ02);

    // No parity 
    // UCSR0C &= ~(1<<UPM00);
    // UCSR0C &= ~(1<<UPM01);
    UCSR0C &= ~((1 << UPM00) | (1 << UPM01)); // Clears 2 bits at once. Can only do 2 at a time!
    
    // 1 Stop bit
    UCSR0C &= ~(1 << USBS0);

    // 9600 BAUD
    UCSR0A &= ~(1 << U2X0); // Not using BAUD rate doubler
    UBRR0 = 103;

	DDRB |= (1<<5); //Makes the PB5 an output pin (Yellow LED).
	char ch;

    while (1)
    {
		if(UCSR0A & (1<<RXC0)) //Check if character is available in the UART UDR0 register
		{
			ch = UDR0; //Read it out of the UART
			
			if(ch == 'n')
			{PORTB |= (1<<5);}
			
			else if(ch == 'f')
			{PORTB &= ~(1<<5);}
		}
        
    }

    return 0;
}
