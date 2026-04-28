#include "EXT_INTERRUPT_interface.h"
#include "GPIO.h"
#include "BIT_MATH.h"
#include <avr/interrupt.h>

/* Callback pointers */
static void (*INT0_Callback)(void) = 0;
static void (*INT1_Callback)(void) = 0;

/* ================= INT0 ================= */

void EXT_INT0_Init(uint8_t sense)
{
    /* PD2 as input */
    GPIO_VidSetPinDirection(GPIO_PORTD, GPIO_PIN2, GPIO_INPUT);

    /* Enable pull-up */
    GPIO_VidSetPinValue(GPIO_PORTD, GPIO_PIN2, GPIO_HIGH);

    /* Clear ISC00, ISC01 */
    EICRA &= ~(0x03);

    /* Set sense mode */
    EICRA |= (sense << ISC00);
}

void EXT_INT0_Enable(void)
{
    EIMSK |= (1 << INT0);
}

void EXT_INT0_SetCallback(void (*ptr)(void))
{
    INT0_Callback = ptr;
}

/* ================= INT1 ================= */

void EXT_INT1_Init(uint8_t sense)
{
    /* PD3 as input */
    GPIO_VidSetPinDirection(GPIO_PORTD, GPIO_PIN3, GPIO_INPUT);

    /* Enable pull-up */
    GPIO_VidSetPinValue(GPIO_PORTD, GPIO_PIN3, GPIO_HIGH);

    /* Clear ISC10, ISC11 */
    EICRA &= ~(0x0C);

    /* Set sense mode */
    EICRA |= (sense << ISC10);
}

void EXT_INT1_Enable(void)
{
    SET_BIT(EIMSK, 1);
}
void EXT_INT1_Disable(void)
{
    CLR_BIT(EIMSK, 1);
}


void EXT_INT1_SetCallback(void (*ptr)(void))
{
    INT1_Callback = ptr;
}

/* ================= Global ================= */

void EXT_INT_GlobalEnable(void)
{
    SET_BIT(SREG,7);
}

void EXT_INT_DisableEnable(void)
{
    CLR_BIT(SREG,7);
}

/* ================= ISR ================= */

ISR(INT0_vect)
{
    if (INT0_Callback != 0)
        INT0_Callback();
}

ISR(INT1_vect)
{
    if (INT1_Callback)
        INT1_Callback();
}