#include "key.h"

void KEY_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init(GPIOC,&GPIO_Structure);
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_15;
	GPIO_Init(GPIOA,&GPIO_Structure);
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_Structure);
}

