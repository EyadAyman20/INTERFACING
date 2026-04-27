#include "TIMER_interface.h"
#include "GPIO.h"
#include "EXT_INTERRUPT_interface.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void TIMER_VidInit(u8 mode)
{
	switch(mode)
	{
		case TIMER_NORMAL_MODE:
			CLR_BIT(TCCR0A , WGM01);
			CLR_BIT(TCCR0A , WGM00);
		break;

		case TIMER_CTC_MODE:
            CLR_BIT(TCCR0B , WGM02);
			SET_BIT(TCCR0A , WGM01);
			CLR_BIT(TCCR0A , WGM00);
		break;
	}
}


void TIMER_VidStart(u8 clock)
{
	
	TCCR0B &= 0xF8;

	
	TCCR0B |= clock;
}


 
void TIMER_VidStop(void)
{
	CLR_BIT(TCCR0B , CS00);
	CLR_BIT(TCCR0B , CS01);
	CLR_BIT(TCCR0B , CS02);
}


void TIMER_VidSetPreload(u8 value)
{
	TCNT0 = value;
}


void TIMER_VidSetCompareMatch(u8 value)
{
	OCR0A = value;
}

void TIMER_VidEnableOverflowInterrupt(void)
{
	sei();
	SET_BIT(TIMSK0 , TOIE0);
}
void TIMER_VidEnableCTCInterrupt(void)
{
	sei();
	SET_BIT(TIMSK0 , OCIE0A);
}
void TIMER_VidDisableInterrupt(void)
{
	CLR_BIT(TIMSK0 , TOIE0);
	CLR_BIT(TIMSK0 , OCIE0A);
}
