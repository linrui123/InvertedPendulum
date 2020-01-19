#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

#define KEY0 PEin(2)
#define KEY1 PEin(3)
#define KEY2 PEin(4)

void KEY_Init(void);

#endif 

