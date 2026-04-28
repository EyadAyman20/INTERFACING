#ifndef KPD_H_
#define KPD_H_

#include"STD_TYPES.h"
#include"GPIO.h"
#include"Includes.h"

#define KPD_PortDirection 0xF0
#define KPD_PortValue 0xFF
#define KPD_Port GPIO_PORTD

#define KPD_Arr {{'1','2','3','A'}, {'4','5','6','B'} , {'7','8','9','C'} , {'*' , '0' , '#' , 'D'}}

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

void KPD_VoidInit(void);

u8 KPD_U8GetPressedKey(void);



#endif