#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
    //Set the direction of the PB5 pin to be an output pin
    DDRB = 0x38; //0b 0011 1000
    DDRD = 0x07; //0b 0000 0111
    
    while(1) 
    {
/*
        //Make PB3 and PD0 high
        PORTB = 0x08; //0b 0000 1000
		PORTD = 0x01; //0b 0000 0001 
        _delay_ms(500);
		//Make PB3 and PD0 low
		PORTB = 0x00; //0b 0000 0000
		PORTD = 0x00; //0b 0000 0000
		_delay_ms(500);
		*/
        //Make PB5 and PD0 high RED
        PORTB = 0x20; //0b 0010 0000	
        PORTD = 0x01; //0b 0000 0001
        _delay_ms(2000);
        //Make PB5 and PD0 low
        PORTB = 0x00; //0b 0000 0000
        _delay_ms(100);
    
        //Make PB3 high GREEN
        PORTB = 0x08 ; //0b 0000 1000
		//Make PD0 high RED
		PORTD = 0x01; //0b 0000 0001 
		_delay_ms(6000);
        //Make PB3 low
        PORTB = 0x00; //0b 0000 0000 
		_delay_ms(100);
        
		//Make PB4 high ORANGE and PD0 high 
		PORTB = 0x10; //0b 0001 0000
		PORTD = 0x01; //0b 0000 0001
		_delay_ms(2000);//Make PB4 low
		PORTB = 0x00; //0b 0000 0000 
		_delay_ms(100);
        
	    //Make PB5 and PD0 high Both RED
        PORTB = 0x20; //0b 0010 0000
	    PORTD = 0x01; //0b 0000 0001 
        _delay_ms(2000);
        //Make Pd0 low
	    PORTD = 0x00; //0b 0000 0000 
        _delay_ms(100);

        //Make PD2 high GREEN and PB5 high RED
	    PORTD = 0x04; //0b 0000 0100 
		PORTB = 0x20; //0b 0010 0000	
        _delay_ms(6000);
        //Make PD2 and PB5 low
	    PORTD = 0x00; //0b 0000 0000 
        _delay_ms(100);

        //Make PD1 high ORANGE and PB5 high RED
		PORTD = 0x02; //0b 0000 0010 
		PORTB = 0x20; //0b 0010 0000
		_delay_ms(2000);
        //Make PD1 and PB5 low
		PORTD = 0x00; //0b 0000 0000 
		PORTB = 0x20; //0b 0000 0000
		_delay_ms(100);

       	}
    return 0;
}