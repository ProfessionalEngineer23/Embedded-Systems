#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "../include/usart.h"
#include <stdio.h>

uint8_t distanceFlag = 0;
uint16_t startCount = 0, stopCount = 0;

ISR(TIMER1_CAPT_vect)
{
	if(TCCR1B & (1<<ICES1)) //Rising edge
	{
		TCCR1B &= ~(1<<ICES1);
		startCount = ICR1;
	}
	else //Falling edge
	{
		TCCR1B |= (1<<ICES1);
		stopCount = ICR1;
		distanceFlag = 1;
	}
	
	//captureFlag = 1;
}

int main(void)
{
	char str[10];

	// Timer 1 in normal mode, rising edge
	// Set up for rising edge capture
	TCCR1B |= (1 << ICES1);
	
	//Send IRQ to CPU on input capture
	TIMSK1 |= (1<<ICF1);
	sei();

	// Prescaler of 8. F_CPU 16Mhz. 
	//Timer clock 2Mhz
	//Timer tick 0.5uS
	TCCR1B |= (1 << CS11);

	usartInit();
	
	uint16_t pulseTime = 0, distance = 0;
	
	DDRD |= (1<<7);
	DDRB &= ~(1<<0);

	while(1)
	{
		//Trigger pulse
		PORTD |= (1<<7);
		_delay_us(10);
		PORTD &= ~(1<<7);
		
		//Wait for sensor to finish
		_delay_ms(500);
		
		if(distanceFlag == 1)
		{
			distanceFlag = 0;
			
			pulseTime = (stopCount - startCount)/2;
			
			distance = pulseTime/58;
			
			sprintf(str, "%u\n", distance);
			usartSendString(str);
		}
		//_delay_ms(10);
	}

	return 0;
}