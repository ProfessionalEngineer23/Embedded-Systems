#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "../include/usart.h"
#include "../include/pwm.h"
#include "../include/millisMicrosDelay.h"
#include "../include/ultrasonic.h"
#include "../include/config.h"

// --- Movement functions (local definitions only) ---
void forward(void)
{
    PORTC = 0x0A;
    setMotorSpeed(255, 255); // Full speed
}

void left(void)
{
    PORTC = 0x09;
    setMotorSpeed(255, 255); // Full speed
}

void right(void)
{
    PORTC = 0x06;
    setMotorSpeed(255, 255); // Full speed
}

void stop(void)
{
    PORTC = 0x00;
    setMotorSpeed(0, 0); // Stop motors
}

// --- Main Program ---
int main(void)
{
    initPWM();              // From pwm.c
    setupPins();            // From config.c
    usartInit();            // From usart.c
    ultrasonicInit();       // From ultrasonic.c
    millisMicrosDelayInit();// From millisMicrosDelay.o

    delay(500); // Warmup

    char buffer[32];

    while (1)
    {
        uint16_t distance = getDistance();

        if (distance < 400) {
            sprintf(buffer, "Distance: %u cm\r\n", distance);
            usartSendString(buffer);
        } else {
            usartSendString("No echo\r\n");
        }

        if (distance < 50) // Obstacle detected
        {
            stop();
            delay(300);

            uint8_t direction = rand() % 2;
            uint16_t turnDuration = 1800;

            if (direction == 0) {
                left();
            } else {
                right();
            }

            delay(turnDuration);
            stop();
            delay(300);
        }
        else if (distance < 400)
        {
            forward();
        }
        else
        {
            stop();
        }

        delay(100);
    }
}
