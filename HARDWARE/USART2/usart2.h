#ifndef _USART2_H
#define _USART2_H

#include "stm32f10x.h"
#include "sys.h"
#include "string.h"

#define  USART_RECE_MAX_LEN 200

void USART2_Init(u32 bound);
void USART2_Send_String(char * str);

#endif

