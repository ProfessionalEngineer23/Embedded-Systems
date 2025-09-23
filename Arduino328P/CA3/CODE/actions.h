#ifndef ACTIONS_H_
#define ACTIONS_H_

#include <stdint.h>

void SpeedControl(char ch);

/*****************************************************
 * Function prototypes for robot motion control
 ****************************************************/
void forward(uint8_t speed);
void reverse(uint8_t speed);
void right(uint8_t speed);
void left(uint8_t speed);
void stop(void);
void stall(void);
void dance(void);

/*****************************************************
 * Function prototypes for light control
 ****************************************************/
void frontLightsON(void);
void frontLightsOFF(void);
void backLightsON(void);
void backLightsOFF(void);

/*****************************************************
 * Function prototype for command handler
 ****************************************************/
void actionChoice(char c);

/*****************************************************
 * Function prototype autonomous mode/ obstacle avoidance
 ****************************************************/
uint8_t isAutonomousEnabled(void);


#endif
