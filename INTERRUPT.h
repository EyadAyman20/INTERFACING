#ifndef INTURRUPT_H
#define INTURRUPT_H
#include "GPIO_interface.h"

#include <avr/io.h>


#define INT_LOW 0
#define INT_AnyChange 1
#define INT_RisingEdge 2
#define INT_FallingEdge 3




void INT_PIN0 (u8 sense);
void INT_PIN1 (u8 sense);


void INT_PIN0_Enable (void);
void INT_PIN1_Enable (void);


void INT_PIN0_CallBack (void (*ptr)(void));
void INT_PIN1_CallBack (void (*ptr)(void));



void INT_GLBL_ENABLE(void);
void INT_GLBL_DISABLE(void);

#endif