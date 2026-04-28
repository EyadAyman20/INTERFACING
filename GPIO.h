#ifndef GPIO_H
#define GPIO_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* ================== Register Definitions (ATmega328P) ================== */

/* PORTB */
#define PORTB   *((volatile u8*)0x25)
#define DDRB    *((volatile u8*)0x24)
#define PINB    *((volatile u8*)0x23)

/* PORTC */
#define PORTC   *((volatile u8*)0x28)
#define DDRC    *((volatile u8*)0x27)
#define PINC    *((volatile u8*)0x26)

/* PORTD */
#define PORTD   *((volatile u8*)0x2B)
#define DDRD    *((volatile u8*)0x2A)
#define PIND    *((volatile u8*)0x29)

/* ================== Macros ================== */

#define GPIO_OUTPUT     1
#define GPIO_INPUT      0

#define GPIO_HIGH       1
#define GPIO_LOW        0

#define GPIO_ALL_OUTPUT 0xFF
#define GPIO_ALL_INPUT  0x00

#define GPIO_ALL_HIGH   0xFF
#define GPIO_ALL_LOW    0x00

/* Ports */
#define GPIO_PORTB 0
#define GPIO_PORTC 1
#define GPIO_PORTD 2

/* Pins */
#define GPIO_PIN0 0
#define GPIO_PIN1 1
#define GPIO_PIN2 2
#define GPIO_PIN3 3
#define GPIO_PIN4 4
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN7 7

/* ================== Prototypes ================== */

void GPIO_VidSetPinDirection(u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Direction);
void GPIO_VidSetPinValue(u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Value);
void GPIO_VidSetPortDirection(u8 Copy_U8Port, u8 Copy_U8Direction);
void GPIO_VidSetPortValue(u8 Copy_U8Port, u8 Copy_U8Value);
void GPIO_VidTogglePinValue(u8 Copy_U8Port, u8 Copy_U8Pin);

u8   GPIO_U8GetPinValue(u8 Copy_U8Port, u8 Copy_U8Pin);
u8   GPIO_U8GetPortValue(u8 Copy_U8Port);

#endif