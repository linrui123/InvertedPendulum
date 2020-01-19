#include "encoder.h"

void Encoder_TIM5_Init(){
	GPIO_InitTypeDef GPIO_Structure;
	TIM_TimeBaseInitTypeDef TIMER_Structure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//
	GPIO_Structure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_Structure);
	
	TIMER_Structure.TIM_Period=65535;
	TIMER_Structure.TIM_Prescaler=0;
	TIMER_Structure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMER_Structure.TIM_CounterMode=TIM_CounterMode_CenterAligned1;//向上计数
	TIM_TimeBaseInit(TIM5,&TIMER_Structure);
	
	TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//编码器模式3
	
	TIM_ICStructInit(&TIM_ICInitStructure);//输入缺省值
	TIM_ICInitStructure.TIM_ICFilter=10;//设置滤波器长度
	TIM_ICInit(TIM5,&TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM5,0);
	TIM_Cmd(TIM5,ENABLE);
}

void Encoder_TIM3_Init(){
	GPIO_InitTypeDef GPIO_Structure;
	TIM_TimeBaseInitTypeDef TIMER_Structure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//
	GPIO_Structure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_Structure);
	
	TIMER_Structure.TIM_Period=65535;
	TIMER_Structure.TIM_Prescaler=0;
	TIMER_Structure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMER_Structure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIMER_Structure);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM3,0);
	TIM_Cmd(TIM3,ENABLE);
}

void TIM5_IRQHandler(void){
	if(TIM_GetITStatus(TIM5,TIM_FLAG_Update)==SET){//溢出中断
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);//清除中断标志位
	}
}

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3,TIM_FLAG_Update)==SET){
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

