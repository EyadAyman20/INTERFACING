
#include "STD_TYPES.h"
#include "EXT_INTERRUPT_interface.h"
#include "LCD.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "GPIO.h"

static void (* INT0_CallBack)(void)=0;
static void (* INT1_CallBack)(void)=0;

void INT_PIN0 (u8 sense){
    GPIO_VidSetPinDirection(GPIO_PORTD,GPIO_PIN2,GPIO_INPUT);
    GPIO_VidSetPinValue(GPIO_PORTD,GPIO_PIN2,GPIO_HIGH);

    EICRA &=~(0x03);
    
    EICRA |=(sense<<ISC00) ;
}

void INT_PIN0_Enable (void){
     SET_BIT(EIMSK, INT0);
}

 
void INT_PIN0_CallBack (void (*ptr)(void))
{
    INT0_CallBack=ptr;
}
 
 
void INT_PIN1 (u8 sense)
{
    GPIO_VidSetPinDirection(GPIO_PORTD,GPIO_PIN3,GPIO_INPUT);
    GPIO_VidSetPinValue(GPIO_PORTD,GPIO_PIN3,GPIO_HIGH);
            EICRA &=~(0x0C);
    EICRA |=(sense<<ISC10) ;
}

 
 
void INT_PIN1_Enable (void){
      SET_BIT(EIMSK,INT1);
}

  
  
void INT_PIN1_CallBack (void (*ptr)(void))
{      
INT1_CallBack=ptr;
}
  
  
  
void INT_GLBL_ENABLE(void)
{
       SET_BIT(SREG,7);
}

void INT_GLBL_DISABLE(void)
{
       CLR_BIT(SREG,7);
}

      
ISR(INT0_vect)
 {
    if(INT0_CallBack!=0)
    {
        INT0_CallBack();
    }
}     
      
ISR(INT1_vect)
{
    if(INT1_CallBack!=0)
    {
        INT1_CallBack();
    }
}
