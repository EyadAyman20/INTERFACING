#include "KPD.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "STD_TYPES.h"
#include <util/delay.h>

void KPD_VidInit()
{
    GPIO_VidSetPortDirection(KPD_Port, KPD_PortDirection);
    GPIO_VidSetPortValue(KPD_Port, GPIO_ALL_HIGH);
}
u8 KPD_u8GetKey()
{
    u8 Loc_U8PressedKey = 0xff;
    u8 Loc_U8KPDArr[KPD_ROWNum][KPD_COLNum] = KPD_Arr;
    u8 Loc_U8KPDColArr[KPD_COLNum] = {KPD_Col1 , KPD_Col2 , KPD_Col3 , KPD_Col4};
    u8 Loc_U8KPDRowArr[KPD_ROWNum] = {KPD_Row1 , KPD_Row2 , KPD_Row3 , KPD_Row4};
    
    for (int i = 0 ; i < KPD_COLNum; i++)
    {
        GPIO_VidSetPinValue(KPD_Port , Loc_U8KPDColArr[i] , GPIO_LOW);
        
        for (int j = 0 ; j < KPD_ROWNum; j++)
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
