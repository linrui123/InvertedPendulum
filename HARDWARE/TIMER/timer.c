#include "timer.h"

void TIM1_Init(u16 arr,u16 psc){
	TIM_TimeBaseInitTypeDef TIM_Structure;
	NVIC_InitTypeDef NVIC_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_Structure.TIM_ClockDivision=0;
	TIM_Structure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Structure.TIM_Period=arr;
	TIM_Structure.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM1,&TIM_Structure);
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	
	NVIC_Structure.NVIC_IRQChannel=TIM1_UP_IRQn;
	NVIC_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Structure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_Structure);
	
	TIM_Cmd(TIM1,ENABLE);
}

