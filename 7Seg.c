#include "STD_TYPES.h"
#include "GPIO.h"
#include "7Seg.h"

u8 numbers[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                  0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void SevenSegment_init(u8 copy_u8port){
   GPIO_VidSetPortDirection( copy_u8port , GPIO_ALL_OUTPUT );
}
void SevenSegment_PrintNunmber(u8 number , u8 copy_u8port){
 GPIO_VidSetPortValue( copy_u8port , numbers[number]);
}

