#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#include <stdint.h>

/*****************************************************
 * This function is to initialize Timer0 for fast PWM mode
 ****************************************************/
void initPWM(void);

/*****************************************************
 * This function sets PWM duty cycle for both motors separately
 ****************************************************/
void setMotorSpeed(uint8_t leftSpeed, uint8_t rightSpeed);

#endif
