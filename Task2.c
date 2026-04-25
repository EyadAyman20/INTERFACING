// /*
//  * File:   Task2.c
//  * Author: Eyad.Ayman
//  *
//  * Created on April 15, 2026, 11:15 AM
//  */


// #include <xc.h>
// #include "GPIO_interface.h"
// void main(void) {
    
//     GPIO_VidSetPortDirection(GPIO_PORTB, 0x01);
    
//     GPIO_VidSetPortValue(GPIO_PORTB, 0x02);

//     while(1)
//     {
//     while(GPIO_U8GetPinValue(GPIO_PORTB, GPIO_PIN1) == GPIO_LOW)
//     {
//          GPIO_VidSetPinValue(GPIO_PORTB, GPIO_PIN0, GPIO_HIGH);
//     }
//     GPIO_VidSetPinValue(GPIO_PORTB, GPIO_PIN0, GPIO_LOW);

//     }
//     return;
// }
