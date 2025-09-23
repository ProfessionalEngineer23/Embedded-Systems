#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define TIME0 1000
#define TIME1 2000
#define TIME2 4000

//Forward function for 2 seconds
void forward() {
//Make PC3 AND PC1 high 
PORTC = 0x0A;     //0b 0000 1010	
_delay_ms(TIME1);
//Make PC3 AND PC1 low
PORTC = 0x00;     //0b 0000 0000	
_delay_ms(TIME1);}

//Forward function for 4 seconds
void forward1() 
{//Make PC3 AND PC1 high 
PORTC = 0x0A;     //0b 0000 1010	
_delay_ms(TIME2);
//Make PC3 AND PC1 low
PORTC = 0x00;     //0b 0000 0000	
_delay_ms(TIME2);}
		
//Function to make robot go reverse
void reverse()
{//Make PC2 AND PC0 high 
PORTC = 0x05;     //0b 0000 0101	
_delay_ms(TIME1);
//MAke PC3 AND PC1 low
PORTC = 0x00;     //0b 0000 0000	
_delay_ms(TIME1);}

//Funtion to make robot turn right
void right()
{		
//Make pc2 high make pc1 high
PORTC = 0x06;     //0b 0000 0110	
_delay_ms(TIME0);		
PORTC = 0x00;     //0b 0000 0000	
_delay_ms(TIME0);}
		
//Funtion to make robot 
void left()
{
//Make pc3 high make pc0 high
PORTC = 0x09;     //0b 0000 1001	
_delay_ms(TIME0);
PORTC = 0x00;     //0b 0000 0000	
_delay_ms(TIME0);}

void stop()
{
//Make PC3, PC2, PC1, PC0 high 
PORTC = 0x0F;     //0b 0000 1111	
_delay_ms(TIME1);
//Make PC3, PC2, PC1, PC0 low 
PORTC = 0x00;     //0b 0000 0000	
_delay_ms(TIME1);}
		
int main(void)
{
//Set the direction of the PC pins to be an output pin
DDRC = 0x0f; //0b 0000 1111
    
forward();
right();

forward();
left();

forward();
left();

forward1();
left();

forward();
left();

forward();
right();

forward();
reverse();
forward();

stop();
	
    return 0;
}

/*
_delay_ms() is a macro. It can only take in macros. 
This won't work: _delay_ms(t),
where t is a time variable initialized in the main function.

Is there any benefit in defining TIME0,1,2?
Does it make -02 (Medium Optimization) less effective when compiling?
Or does it make the code require more complex optimization?
How does optimization work??
*/