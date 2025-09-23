#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "usart.h"


int main(void)
{
		usartInit();
		
		//Use the 1.1V Bandgap as the voltage reference 
		ADMUX |= (1<<REFS1);
		ADMUX |= (1<<REFS0);
		
		//Select ADC channel 5
		ADMUX &= ~(1<<MUX3);
		ADMUX |= (1<<MUX2);
		ADMUX &= ~(1<<MUX1);
		ADMUX |= (1<<MUX0);
		
		//Prescale ADC clock by 128 => 125Khz Clock 
		ADCSRA |= (1<<ADPS2);
		ADCSRA |= (1<<ADPS1);
		ADCSRA |= (1<<ADPS0);
		
		//Enable the ADC
		ADCSRA |= (1<<ADEN);
	
		uint16_t adcCode;
		char str[100];
		float voltage;
		
		while(1)
		{
			ADCSRA |= (1<<ADSC);
			
			while(ADCSRA & (1<<ADSC))
			{
				//ADSC bit is a one
			}
			
			//Read the ADC code
			adcCode = ADC;
			
			voltage = adcCode / 1023.0 * 1.1;
			float temperature = voltage * 100.0;
			sprintf(str, "Temp: %.2f C\n", temperature);

			
			usartSendString(str);
			
			_delay_ms(1000);
		}
		
		return 0;
}
