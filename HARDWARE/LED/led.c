#include "led.h"
#include "delay.h"

void LED_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_8;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Structure);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_2;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_Structure);
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
}

void LED_indicate(void){
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	delay_ms(100);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	delay_ms(100);
}

