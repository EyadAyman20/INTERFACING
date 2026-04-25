#include "GPIO_interface.h"
#include "KPD.h"
#include "LCD.h"

void main(void)
{
    u8 key;

    u16 num1 = 0;
    u16 num2 = 0;
    u16 result = 0;

    char operation = 0;
    u8 state = 0;   // 0=num1, 1=op, 2=num2

    KPD_VidInit();
    LCD_Init();

    LCD_Clear();
    
    LCD_SetCursor(1,0);

    while(1)
    {
        key = KPD_u8GetKey();

        if(key == 0xFF)
            continue;

        /* RESET BUTTON */
        if(key == 'C')
        {
            num1 = num2 = result = 0;
            operation = 0;
            state = 0;

            LCD_Clear();
            LCD_SendString("Cleared");
            LCD_SetCursor(1,0);
            continue;
        }

        /* DIGITS */
        if(key >= '0' && key <= '9')
        {
            LCD_SendChar(key);

            if(state == 0)
            {
                num1 = num1 * 10 + (key - '0');
            }
            else if(state == 2)
            {
                num2 = num2 * 10 + (key - '0');
            }
        }

        /* OPERATOR */
        else if(key == '+' || key == '-' || key == '*' || key == '/')
        {
            operation = key;
            state = 2;

            LCD_SendChar(key);
        }

        /* EQUAL */
        else if(key == '=')
        {
            LCD_SetCursor(1,0);

            switch(operation)
            {
                case '+': result = num1 + num2; break;
                case '-': result = num1 - num2; break;
                case '*': result = num1 * num2; break;

                case '/':
                    if(num2 != 0)
                        result = num1 / num2;
                    else
                    {
                        LCD_SendString("Err Div0");
                        continue;
                    }
                    break;
            }

            LCD_SendString("= ");
            
            /* print result */
            if(result == 0)
            {
                LCD_SendChar('0');
            }
            else
            {
                u16 temp = result;
                u8 digits[5];
                s8 i = 0;

                while(temp > 0)
                {
                    digits[i++] = (temp % 10) + '0';
                    temp /= 10;
                }

                while(i--)
                {
                    LCD_SendChar(digits[i]);
                }
            }

            /* reset for next calc */
            num1 = result;
            num2 = 0;
            state = 2;
        }
    }
}