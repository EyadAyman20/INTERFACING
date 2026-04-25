/* 
 * File:   KPD.h
 * Author: Eyad.Ayman
 *
 * Created on April 14, 2026, 11:05 AM
 */


#ifndef KPD_H
#define	KPD_H
#include "STD_TYPES.h"
#define KPD_PortDirection 0Xf0
#define KPD_Port GPIO_PORTD

#define KPD_Arr {{'7','8','9','/'},\
                 {'4','5','6','*'},\
                 {'1','2','3','-'},\
                 {'C','0','=','+'}}

#define KPD_Row1 GPIO_PIN0
#define KPD_Row2 GPIO_PIN1
#define KPD_Row3 GPIO_PIN2
#define KPD_Row4 GPIO_PIN3

#define KPD_Col1 GPIO_PIN4
#define KPD_Col2 GPIO_PIN5
#define KPD_Col3 GPIO_PIN6
#define KPD_Col4 GPIO_PIN7

#define KPD_ROWNum 4
#define KPD_COLNum 4
void KPD_VidInit(void);
u8 KPD_u8GetKey();

#endif	/* KPD_H */

