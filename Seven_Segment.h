/* 
 * File:   Seven_Segment.h
 * Author: Eyad.Ayman
 *
 * Created on April 15, 2026, 9:19 AM
 */

#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H
#include "STD_TYPES.h"
#include "GPIO_interface.h"

void SevenSegment_init(u8 copy_u8port);
void SevenSegment_PrintNunmber(u8 number , u8 copy_u8port);

#endif	/* SEVEN_SEGMENT_H */

