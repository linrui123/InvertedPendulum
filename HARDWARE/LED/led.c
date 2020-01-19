#include "led.h"
#include "delay.h"

void LED_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Structure);
	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);
}

void LED_indicate(void){
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	delay_ms(100);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	delay_ms(100);
}

