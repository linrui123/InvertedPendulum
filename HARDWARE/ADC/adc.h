#ifndef _ADC_H
#define _ADC_H

#include "sys.h"
#include "delay.h"

void Angle_ADC_Init(void);
u16 Get_ADC(u8 ch);
u16 Get_ADC_Average(u8 ch,u8 times);
void ADC_DMA_Init(void);

#endif

