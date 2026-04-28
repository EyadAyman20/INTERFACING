#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H

#include "STD_TYPES.h"

/* ========== Timer0 Modes ========== */
#define TIMER_NORMAL_MODE           0
#define TIMER_CTC_MODE              1
#define TIMER_FAST_PWM              2
#define TIMER_PHASE_CORRECT_PWM     3

/* ========== Clock Source / Prescaler ========== */
#define TIMER_NO_CLOCK              0
#define TIMER_NO_PRESCALER          1
#define TIMER_PRESCALER_8           2
#define TIMER_PRESCALER_64          3
#define TIMER_PRESCALER_256         4
#define TIMER_PRESCALER_1024        5

#define TIMER_EXTERNAL_FALLING      6
#define TIMER_EXTERNAL_RISING       7

/* PWM */
#define PWM_NON_INVERTING            1
#define PWM_INVERTING                2

/* APIs */
void TIMER_VidInit(u8 mode);
void TIMER_VidStart(u8 clock);
void TIMER_VidStop(void);

void TIMER_VidSetPreload(u8 value);
void TIMER_VidSetCompareMatch(u8 value);

void TIMER_VidEnableOVFInterrupt(void);
void TIMER_VidEnableCTCInterrupt(void);
void TIMER_VidDisableInterrupts(void);

void TIMER_VidSetOVFCallBack(void (*ptr)(void));
void TIMER_VidSetCTCCallBack(void (*ptr)(void));

void TIMER_VidDelay_ms(u32 delay);
void TIMER_VidDelay_us(u32 delay);

void TIMER_VidInitPWM(u8 mode, u8 oc_mode);
void TIMER_VidSetPWMDuty(u8 duty);

#endif