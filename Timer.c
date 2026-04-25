#include "TIMER_INTERFACE.h"
#include "GPIO.h"
#include "INTERRUPT.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void TIMER0_VidInit(u8 mode)
{
	switch(mode)
	{
		case TIMER_MODE_NORMAL:
			CLR_BIT(TCCR0 , WGM01);
			CLR_BIT(TCCR0 , WGM00);
		break;

		case TIMER_MODE_CTC:
			SET_BIT(TCCR0 , WGM01);
			CLR_BIT(TCCR0 , WGM00);
		break;
	}
}


void TIMER0_VidStart(u8 clock)
{
	
	TCCR0 &= 0xF8;

	
	TCCR0 |= clock;
}


 
void TIMER0_VidStop(void)
{
	CLR_BIT(TCCR0 , CS00);
	CLR_BIT(TCCR0 , CS01);
	CLR_BIT(TCCR0 , CS02);
}


void TIMER0_VidSetPreload(u8 value)
{
	TCNT0 = value;
}


void TIMER0_VidSetCompareMatch(u8 value)
{
	OCR0 = value;
}

void TIMER0_VidEnableOverflowInterrupt(void)
{
	sei();
	SET_BIT(TIMSK , TOIE0);
}
void TIMER0_VidEnableCTCInterrupt(void)
{
	sei();
	SET_BIT(TIMSK , OCIE0);
}
void TIMER0_VidDisableInterrupt(void)
{
	CLR_BIT(TIMSK , TOIE0);
	CLR_BIT(TIMSK , OCIE0);
}