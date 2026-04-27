/* 
 * File:   KPD.c
 * Author: pc
 *
 * Created on April 27, 2026, 12:12 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "KPD.h"
#include <util/delay.h>

void KPD_VoidInit(void)
{
    GPIO_VidSetPortDirection(KPD_Port , KPD_PortDirection);
    GPIO_VidSetPortValue(KPD_Port , KPD_PortValue);
}

u8 KPD_U8GetPressedKey(void)
{
  u8 Loc_U8PressedKey = 0xff;
    u8 Loc_U8KPDArr[KPD_ROWNum][KPD_COLNum] = KPD_Arr;
    u8 Loc_U8KPDColArr[KPD_COLNum] = {KPD_Col1 , KPD_Col2 , KPD_Col3 , KPD_Col4};
    u8 Loc_U8KPDRowArr[KPD_ROWNum] = {KPD_Row1 , KPD_Row2 , KPD_Row3 , KPD_Row4};
    
    for (u8 i = 0 ; i < KPD_COLNum; i++)
    {
        GPIO_VidSetPinValue(KPD_Port , Loc_U8KPDColArr[i] , GPIO_LOW);
        _delay_us(5);
        for (u8 j = 0 ; j < KPD_ROWNum; j++)
        {
            if(GPIO_U8GetPinValue(KPD_Port, Loc_U8KPDRowArr[j]) == GPIO_LOW)
            {
                _delay_ms(20);
                
            if(GPIO_U8GetPinValue(KPD_Port, Loc_U8KPDRowArr[j]) == GPIO_LOW)
                {
                    Loc_U8PressedKey = Loc_U8KPDArr[j][i];
                    
                    
                    while(GPIO_U8GetPinValue(KPD_Port, Loc_U8KPDRowArr[j]) == GPIO_LOW);
                    
                    GPIO_VidSetPinValue(KPD_Port , Loc_U8KPDColArr[i] , GPIO_HIGH);
                    return Loc_U8PressedKey;
                }
            }
        }
        
        GPIO_VidSetPinValue(KPD_Port , Loc_U8KPDColArr[i] , GPIO_HIGH);
    }
    
    return Loc_U8PressedKey;
}