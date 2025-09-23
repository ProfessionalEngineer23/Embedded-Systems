	//B Toland
//03/04/25

#ifndef _MILLISMICRODELAY
#define _MILLISMICROSDELAY
#include <avr/io.h>

//This library uses Timer 2 on the AVR and assumes F_CPU of 16MHz
//All the functions (including micros()) are only accurate to 4uS.
void millisMicrosDelayInit(void);


//Immediately returns the number of milliseconds since boot
//Rolls over after approx 50 days.
uint32_t millis(void); 

//Immediately returns the number of microseconds since boot
//Rolls over after approx 70 mins.
uint32_t micros(void); 

//Delays (blocks) for the requested number of milliseconds.
//Uses the millis() function
//Does not return until the requested amount of millisecs has passed.
void delay(uint32_t requestedDelay);

#endif

