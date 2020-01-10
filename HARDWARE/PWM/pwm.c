#include "pwm.h"

void TIM4_PWM_Init(u16 arr,u16 psc){
	GPIO_InitTypeDef GPIO_Structure;
	TIM_TimeBaseInitTypeDef TIMER_Structure;
	TIM_OCInitTypeDef TIM_OCStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Structure);
	
	TIMER_Structure.TIM_Period=arr;
	TIMER_Structure.TIM_Prescaler=psc;
	TIMER_Structure.TIM_ClockDivision=0;
	TIMER_Structure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIMER_Structure);
	
	TIM_OCStructure.TIM_OCMode=TIM_OCMode_PWM1;//PWM1:CNT<CCRx为有效电平,PWM2:CNT>CCRx为有效电平
	TIM_OCStructure.TIM_OCPolarity=TIM_OCPolarity_High;//极性：有效电平为高电平
	TIM_OCStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse=0;
	TIM_OC1Init(TIM4,&TIM_OCStructure);
	TIM_OC2Init(TIM4,&TIM_OCStructure);
//	TIM_OC3Init(TIM4,&TIM_OCStructure);
//	TIM_OC4Init(TIM4,&TIM_OCStructure);
		
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	TIM_Cmd(TIM4,ENABLE);
}

