#include "encoder.h"

void Encoder_TIM5_Init(){
	GPIO_InitTypeDef GPIO_Structure;
	TIM_TimeBaseInitTypeDef TIMER_Structure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//
	GPIO_Structure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Structure);
	
	TIMER_Structure.TIM_Period=65536-1;
	TIMER_Structure.TIM_Prescaler=0;
	TIMER_Structure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMER_Structure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5,&TIMER_Structure);
	
	TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM5,&TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	TIM_SetCounter(TIM5,0);
	TIM_Cmd(TIM5,ENABLE);
}

void Encoder_TIM3_Init(){
	GPIO_InitTypeDef GPIO_Structure;
	TIM_TimeBaseInitTypeDef TIMER_Structure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//
	GPIO_Structure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Structure);
	
	TIMER_Structure.TIM_Period=65536-1;
	TIMER_Structure.TIM_Prescaler=0;
	TIMER_Structure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMER_Structure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIMER_Structure);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM3,0);
	TIM_Cmd(TIM3,ENABLE);
}

