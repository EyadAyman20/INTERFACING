#include "STD_TYPES.h"
#include "GPIO.h"

void SevenSegment_init(u8 copy_u8port){
   GPIO_VidSetPortDirection( copy_u8port , GPIO_ALL_OUTPUT );
}
void SevenSegment_PrintNunmber(u8 number , u8 copy_u8port){
 GPIO_VidSetPortValue( copy_u8port , numbers[number]);
}

