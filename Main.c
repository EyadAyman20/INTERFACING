/* 
 * File:   ????.c
 * Author: pc
 *
 * Created on April 28, 2026, 9:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Includes.h"
/*
 * 
 */

u8 Temp_Channel = ADC_CHANNEL_0;
volatile u16 Temp_Value = 0;
void ADC_READ(void)
{
    u16 adc = ADC; 
    Temp_Value = (adc * 500UL) / 1024;
}
int main(void) {
    ADC_VidInit(ADC_REF_AREF,ADC_PRESCALER_64,ADC_RESOLUTION_10BIT);
    LCD_Init();
    EXT_INT_GlobalEnable();
    ADC_VidEnableInterrupt();
    ADC_VidSetCallBack(ADC_READ);
    
    u8 temp_display[10];
    
    while(1)
    {
        Temp_Value = ADC_U16ReadChannel(Temp_Channel);
        LCD_Clear();
        LCD_SetCursor(0,0);
        LCD_SendString("T:");
        
        sprintf(temp_display, "%d", Temp_Value);
        LCD_SendString(temp_display);
        
        TIMER_VidDelay_ms(500);
    }
    
    return (EXIT_SUCCESS);
}

