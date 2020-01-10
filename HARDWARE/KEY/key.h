#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

#define KEY0 PCin(5)
#define KEY1 PAin(15)
#define KEY2 PAin(0)

void KEY_Init(void);

#endif 

