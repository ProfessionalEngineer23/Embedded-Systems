#include <avr/io.h>
#include "pwm.h"

/*****************************************************
 * This function is to initialize Timer0 for fast PWM mode
 ****************************************************/
void initPWM()
{
    // Set Timer0 to Fast PWM mode
    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    
    // Non-inverting mode for both OC0A and OC0B
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);

    // Set prescaler to 8
    TCCR0B |= (1 << CS01);

    // Set PD5 and PD6 as output for motor control
    DDRD |= (1 << PD5) | (1 << PD6);

    // Initial speed: 78% left, 65% right (example values)
    OCR0A = 200; 
    OCR0B = 165;
}

/*****************************************************
 * This function sets PWM duty cycle for both motors
 ****************************************************/

void setMotorSpeed(uint8_t leftSpeed, uint8_t rightSpeed)
{
    OCR0A = leftSpeed;   // Left motor on PD6 (OC0A)
    OCR0B = rightSpeed;  // Right motor on PD5 (OC0B)
}

