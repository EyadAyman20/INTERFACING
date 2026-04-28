#define F_CPU 8000000UL

#include "TIMER_interface.h"
#include "GPIO.h"
#include "BIT_MATH.h"
#include <avr/interrupt.h>

static void (*TIMER_OVF_CallBack)(void) = 0;
static void (*TIMER_CTC_CallBack)(void) = 0;

/* ========== INIT ========== */

void TIMER_VidInit(u8 mode)
{
    TCCR0A = 0;
    TCCR0B = 0;

    switch (mode)
    {
        case TIMER_NORMAL_MODE:
            break;

        case TIMER_CTC_MODE:
            SET_BIT(TCCR0A, 1); /* WGM01 */
            break;
    }
}

/* ========== START / STOP ========== */

void TIMER_VidStart(u8 clock)
{
    TCCR0B &= 0xF8;
    TCCR0B |= clock;
    sei();
}

void TIMER_VidStop(void)
{
    TCCR0B &= 0xF8;
}

/* ========== TIMER CONTROL ========== */

void TIMER_VidSetPreload(u8 value)
{
    TCNT0 = value;
}

void TIMER_VidSetCompareMatch(u8 value)
{
    OCR0A = value;
}

/* ========== INTERRUPTS ========== */

void TIMER_VidEnableOVFInterrupt(void)
{
    SET_BIT(TIMSK0, 0);
}

void TIMER_VidEnableCTCInterrupt(void)
{
    SET_BIT(TIMSK0, 1);
}

void TIMER_VidDisableInterrupts(void)
{
    CLR_BIT(TIMSK0, 0);
    CLR_BIT(TIMSK0, 1);
}

/* ========== CALLBACKS ========== */

void TIMER_VidSetOVFCallBack(void (*ptr)(void))
{
    TIMER_OVF_CallBack = ptr;
}

void TIMER_VidSetCTCCallBack(void (*ptr)(void))
{
    TIMER_CTC_CallBack = ptr;
}

/* =========================================================
   FIXED FOR 1 MHz CLOCK
   ========================================================= */

/* ========== MICROSECOND DELAY ========== */
/*
At 1 MHz:
- tick = 1 ?s (no prescaler)
- OCR0A = 0 gives ~1 ?s cycle (0..0)
*/

void TIMER_VidDelay_us(u32 delay)
{
    TIMER_VidInit(TIMER_CTC_MODE);

    OCR0A = 0; // 1 ?s per compare match at 1 MHz

    while (delay--)
    {
        TCNT0 = 0;
        SET_BIT(TIFR0, 1);
        TIMER_VidStart(TIMER_NO_PRESCALER);

        while (GET_BIT(TIFR0, 1) == 0);

        TIMER_VidStop();
    }
}

/* ========== MILLISECOND DELAY ========== */
/*
At 1 MHz:
We choose prescaler = 64
tick = 64 ?s

1 ms ? 15.625 ticks ? use OCR0A = 15
(16 ticks ? 64 ?s = 1024 ?s ? 1.024 ms)
*/

void TIMER_VidDelay_ms(u32 delay)
{
    TIMER_VidInit(TIMER_CTC_MODE);

    OCR0A = 15; // calibrated for 1MHz @ prescaler 64

    while (delay--)
    {
        TCNT0 = 0;
        SET_BIT(TIFR0, 1);
        TIMER_VidStart(TIMER_PRESCALER_64);

        while (GET_BIT(TIFR0, 1) == 0);

        TIMER_VidStop();
    }
}

/* ========== PWM ========== */

void TIMER_VidInitPWM(u8 mode, u8 oc_mode)
{
    GPIO_VidSetPinDirection(GPIO_PORTD, GPIO_PIN6, GPIO_OUTPUT);

    TCCR0A = 0;
    TCCR0B = 0;

    if (mode == TIMER_FAST_PWM)
    {
        SET_BIT(TCCR0A, 0);
        SET_BIT(TCCR0A, 1);
    }
    else if (mode == TIMER_PHASE_CORRECT_PWM)
    {
        SET_BIT(TCCR0A, 0);
    }

    if (oc_mode == PWM_NON_INVERTING)
    {
        SET_BIT(TCCR0A, 7);
    }
    else
    {
        SET_BIT(TCCR0A, 7);
        SET_BIT(TCCR0A, 6);
    }
}

/* ========== DUTY ========== */

void TIMER_VidSetPWMDuty(u8 duty)
{
    if (duty <= 100)
    {
        OCR0A = (duty * 255UL) / 100;
    }
}

/* ========== ISR ========== */

ISR(TIMER0_OVF_vect)
{
    if (TIMER_OVF_CallBack)
        TIMER_OVF_CallBack();
}

ISR(TIMER0_COMPA_vect)
{
    if (TIMER_CTC_CallBack)
        TIMER_CTC_CallBack();
}