#define F_CPU 16000000UL
#include <util/delay.h>
#include "config.h"

void setupPins(void)
{
    // Motor direction pins on PORTC
    DDRC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

    // PWM motor pins
    DDRD |= (1 << PD5) | (1 << PD6);

    // Lights and buzzer/debug LED
    DDRB |= (1 << PB5);  // Buzzer/Debug (D13)
    DDRB |= (1 << PB3) | (1 << PB4);  // Front LEDs
    DDRB |= (1 << PB1) | (1 << PB2);  // Back LEDs

    // Ultrasonic sensor
    DDRD |= (1 << PD7);   // TRIG = output
    DDRB &= ~(1 << PB0);  // ECHO = input

    _delay_ms(50);
}
