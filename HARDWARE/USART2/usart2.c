#include "usart2.h"

u16 USART_RECE_STA=0;
u8 USART_RECE_BUF[USART_RECE_MAX_LEN];

void USART2_Init(u32 bound){
	GPIO_InitTypeDef GPIO_Structure;
	USART_InitTypeDef USART_Structure;
	NVIC_InitTypeDef NVIC_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_2;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Structure);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_Structure);
	
	NVIC_Structure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Structure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Structure);
	
	USART_Structure.USART_BaudRate=bound;
	USART_Structure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Structure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Structure.USART_Parity=USART_Parity_No;
	USART_Structure.USART_StopBits=USART_StopBits_1;
	USART_Structure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_Structure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
}

void USART2_IRQHandler(void){
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
		res=USART_ReceiveData(USART2);
		if((USART_RECE_STA&0x8000)==0){
			if(USART_RECE_STA&0x4000){
				if(res!=0x0a)USART_RECE_STA=0;
				else USART_RECE_STA|=0x8000;
			}else{
				if(res==0x0d)USART_RECE_STA|=0x4000;
				else{
					USART_RECE_BUF[USART_RECE_STA&0x3fff]=res;
					USART_RECE_STA++;
					if(USART_RECE_STA>USART_RECE_MAX_LEN){
						USART_RECE_STA=0;
					}
				}
			}
		}
	}
}

void USART2_Send_String(char * str){
	u8 t=strlen(str);
	u8 i;
	for(i=0;i<t;i++){
		USART_SendData(USART2,str[i]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
}

