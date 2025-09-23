// ultrasonic.c

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../include/ultrasonic.h"

// --- Internal Variables ---
volatile uint8_t distanceFlag = 0;
volatile uint16_t startCount = 0, stopCount = 0;

// --- ISR: Input Capture Handler (TIMER1) ---
ISR(TIMER1_CAPT_vect)
{
    if (TCCR1B & (1 << ICES1)) {
        startCount = ICR1;
        TCCR1B &= ~(1 << ICES1); // Switch to falling edge
    } else {
        stopCount = ICR1;
        TCCR1B |= (1 << ICES1);  // Switch back to rising edge
        distanceFlag = 1;
    }
}

// --- Ultrasonic Sensor Initialization ---
void ultrasonicInit(void)
{
    DDRD |= (1 << PD7);    // TRIG = output
    DDRB &= ~(1 << PB0);   // ECHO = input

    TCCR1A = 0;
    TCCR1B = (1 << ICES1) | (1 << CS11); // Rising edge first, prescaler = 8
    TIMSK1 = (1 << ICIE1);               // Enable Input Capture Interrupt
    sei(); // Enable global interrupts
}

// --- Get Distance in cm ---
uint16_t getDistance(void)
{
    distanceFlag = 0;
    TCNT1 = 0; // Reset timer

    // Send 10us trigger pulse
    PORTD |= (1 << PD7);
    _delay_us(10);
    PORTD &= ~(1 << PD7);

    uint32_t timeout = 0;
    while (!distanceFlag && timeout++ < 60000) {
        _delay_us(1);
    }

    if (distanceFlag) {
        uint16_t pulseWidth = stopCount - startCount;
        pulseWidth /= 2; // 0.5us per count
        return pulseWidth / 58; // Convert to cm
    }

    return 999; // Timeout: No echo
}
