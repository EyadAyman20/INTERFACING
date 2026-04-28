#ifndef EXT_INTERRUPT_H
#define EXT_INTERRUPT_H

#include <avr/io.h>

/* Sense modes */
#define EXT_LOW_LEVEL          0
#define EXT_ANY_LOGICAL_CHANGE 1
#define EXT_FALLING_EDGE       2
#define EXT_RISING_EDGE        3

/* APIs */
void EXT_INT0_Init(uint8_t sense);
void EXT_INT1_Init(uint8_t sense);

void EXT_INT0_Enable(void);
void EXT_INT1_Enable(void);

void EXT_INT0_SetCallback(void (*ptr)(void));
void EXT_INT1_SetCallback(void (*ptr)(void));

void EXT_INT_GlobalEnable(void);
void EXT_INT_GlobalDisable(void);


#endif