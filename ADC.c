/****************************************************/ 
/*  File Name     : ADC_program.c                    */
/*  Target        : ATmega328P                       */
/****************************************************/

#include "ADC.h"
#include "BIT_MATH.h"

/* ========== ADC Registers (ATmega328P) ========== */
#define ADMUX   (*(volatile u8*)0x7C)
#define ADCSRA  (*(volatile u8*)0x7A)
#define ADCSRB  (*(volatile u8*)0x7B)
#define ADCL    (*(volatile u8*)0x78)
#define ADCH    (*(volatile u8*)0x79)
#define ADC     (*(volatile u16*)0x78)
#define DIDR0   (*(volatile u8*)0x7E)
#define SREG    (*(volatile u8*)0x5F)

/* ========== Bits ========== */
#define REFS0   6
#define REFS1   7
#define ADLAR   5

#define ADEN    7
#define ADSC    6
#define ADIE    3

/* ========== Callback Pointer ========== */
static void (*ADC_CallBack)(void) = 0;

/* ========== ADC Initialization ========== */
void ADC_VidInit(u8 Copy_u8Ref,
                 u8 Copy_u8Prescaler,
                 u8 Copy_u8Resolution)
{
    /* -------- Reference Voltage -------- */
    ADMUX &= ~(0xC0);

    switch (Copy_u8Ref)
    {
        case ADC_REF_AREF:
            break;

        case ADC_REF_AVCC:
            SET_BIT(ADMUX, REFS0);
            break;

        case ADC_REF_INTERNAL_1V1:
            SET_BIT(ADMUX, REFS0);
            SET_BIT(ADMUX, REFS1);
            break;
    }

    /* -------- Resolution -------- */
    if (Copy_u8Resolution == ADC_RESOLUTION_8BIT)
        SET_BIT(ADMUX, ADLAR);
    else
        CLR_BIT(ADMUX, ADLAR);

    /* -------- Prescaler -------- */
    ADCSRA &= 0xF8;
    ADCSRA |= Copy_u8Prescaler;

    /* -------- Enable ADC -------- */
    SET_BIT(ADCSRA, ADEN);
}

/* ========== 10-bit Read (Polling) ========== */
u16 ADC_U16ReadChannel(u8 Copy_u8Channel)
{
    /* Select channel safely */
    ADMUX = (ADMUX & 0xE0) | (Copy_u8Channel & 0x07);

    /* Disable digital input (optional but good) */
    SET_BIT(DIDR0, Copy_u8Channel);

    /* Start conversion */
    SET_BIT(ADCSRA, ADSC);

    /* Wait */
    while (GET_BIT(ADCSRA, ADSC));

    return ADC;
}

/* ========== 8-bit Read (Polling) ========== */
u8 ADC_U8ReadChannel(u8 Copy_u8Channel)
{
    ADMUX = (ADMUX & 0xE0) | (Copy_u8Channel & 0x07);

    SET_BIT(DIDR0, Copy_u8Channel);

    SET_BIT(ADCSRA, ADSC);

    while (GET_BIT(ADCSRA, ADSC));

    return ADCH;
}

/* ========== Interrupt Control ========== */
void ADC_VidEnableInterrupt(void)
{
    SET_BIT(ADCSRA, ADIE);
    SET_BIT(SREG, 7);   /* Global Interrupt */
}

void ADC_VidDisableInterrupt(void)
{
    CLR_BIT(ADCSRA, ADIE);
}

/* ========== Callback Setter ========== */
void ADC_VidSetCallBack(void (*ptr)(void))
{
    ADC_CallBack = ptr;
}

/* ========== ADC ISR ========== */
void __vector_21(void) __attribute__((signal));
void __vector_21(void)
{
    if (ADC_CallBack)
        ADC_CallBack();
}