#include "actions.h"
#include "usart.h"
#include "pwm.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define TIME0 100
#define TIME1 1600
#define TIME2 2000

static uint8_t autonomousMode = 0; // 0 = manual, 1 = autonomous

// LED control based on updated wiring
// Front lights: PB4 (left = D12), PB3 (right = D11)
void frontLightsON()  { PORTB |= (1 << PB4) | (1 << PB3); }
void frontLightsOFF() { PORTB &= ~((1 << PB4) | (1 << PB3)); }

// Back lights: PB2 (left = D10), PB1 (right = D9)
void backLightsON()   { PORTB |= (1 << PB2) | (1 << PB1); }
void backLightsOFF()  { PORTB &= ~((1 << PB2) | (1 << PB1)); }

void forward(uint8_t speed) {
    PORTC = 0x0A;
    setMotorSpeed(speed - 5, speed);
}

void reverse(uint8_t speed) {
    PORTC = 0x05;
    setMotorSpeed(speed - 5, speed);
    backLightsON();
    PORTB |= (1 << PB5);  // Turn buzzer ON — let user turn it OFF manually
}

void right(uint8_t speed) {
    PORTC = 0x06;
    setMotorSpeed(speed - 5, speed);
    PORTB |= (1 << PB3) | (1 << PB1); // Right blinkers ON — let user turn them OFF
}

void left(uint8_t speed) {
    PORTC = 0x09;
    setMotorSpeed(speed - 5, speed);
    PORTB |= (1 << PB4) | (1 << PB2); // Left blinkers ON
}


void stop(void) {
    PORTC &= ~(0x0F);
    PORTB &= ~((1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4));
    PORTB &= ~(1 << PB5); // stops buzzer
}

void stall() {
    PORTC = 0x0F;
    _delay_ms(TIME1);
    PORTC = 0x00;
    _delay_ms(TIME1);
}

void dance() {
    uint8_t speed = 200;
    right(speed);
    _delay_ms(TIME1);
    stop(); _delay_ms(TIME2);
    forward(speed);
    _delay_ms(TIME2);
    stop(); _delay_ms(TIME2);
    left(speed);
    _delay_ms(TIME1);
    stop(); _delay_ms(TIME2);
}

void actionChoice(char ch) 
{
    static uint8_t currentSpeed = 200;

    switch (ch) {
        case '0': stop(); break;
        case '1': currentSpeed = 100; break;
        case '2': currentSpeed = 120; break;
        case '3': currentSpeed = 140; break;
        case '4': currentSpeed = 160; break;
        case '5': currentSpeed = 180; break;
        case '6': currentSpeed = 200; break;
        case '7': currentSpeed = 220; break;
        case '8': currentSpeed = 240; break;
        case '9': currentSpeed = 255; break;
        case 'q': currentSpeed = 255; break;

        case 'F': forward(currentSpeed); break;
        case 'B': reverse(currentSpeed); break;
        case 'L': left(currentSpeed); break;
        case 'R': right(currentSpeed); break;
        case 'S': stop(); break;

        case 'n': PORTB |= (1 << PB5); break;
        case 'o': PORTB &= ~(1 << PB5); break;

        case 'V': PORTB |= (1 << PB5); break;
        case 'v': PORTB &= ~(1 << PB5); break;

        case 'K': dance(); break;
        case 'k': stop(); break;

        case 'W': frontLightsON(); break;
        case 'w': frontLightsOFF(); break;
        case 'U': backLightsON(); break;
        case 'u': backLightsOFF(); break;

        case 'C': // Enable autonomous mode
            autonomousMode = 1;
            break;

        case 'c': // Disable autonomous mode
            autonomousMode = 0;
            stop(); // Optional: stop movement immediately
            break;
    }
}

uint8_t isAutonomousEnabled(void) {
    return autonomousMode;
}
