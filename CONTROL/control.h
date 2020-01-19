#ifndef _CONTROL_H
#define _CONTROL_H

#include "stm32f10x.h"
#include "sys.h"

void Motor_Init(void);
void Set_Pulse(void);
int PID_Position(int Encoder_Left_Num,int Current_Setpulse);
void Set_Direction(u8 dir);
void Limit_PWM(void);
void Set_PWM(void);
int myabs(int a);
int ReadEncoder(u8 ch);

#endif

