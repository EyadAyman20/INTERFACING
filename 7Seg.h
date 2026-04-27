#ifndef SEVENSEG_INTERFACE_H
#define SEVENSEG_INTERFACE_H

#include "STD_TYPES.h"


u8 numbers[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                  0x6D, 0x7D, 0x07, 0x7F, 0x6F};
/* ===================== APIs ===================== */
void SEVENSEG_VidInit(u8 Copy_U8Port);
void SEVENSEG_VidDisplayNumber(u8 Copy_U8Port, u8 Copy_U8Number);

#endif
