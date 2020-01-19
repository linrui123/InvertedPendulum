#include "control.h"
#include "key.h"
#include "oled.h"
#include "usart2.h"
#include "adc.h"

int Encoder_Left=0;
int Encoder_Right=0;
int speed=0,pulse=0;
float error_c=0,error_l=0,error_ll=0,sum_error=0;
float P=50,I=300,D=0;
int pwm=0,tpwm;

int Angle_Value;

void TIM1_UP_IRQHandler(void){
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
//		Encoder_Left=TIM_GetCounter(TIM5);
		Encoder_Right=ReadEncoder(3);
		PCout(1)=!PCout(1);
		tpwm=PID_Position(Encoder_Right,pulse);//限幅7200
		Limit_PWM();
		Set_PWM();
//		Angle_Value=Get_ADC_Average(8,15);
	}
}

int myabs(int a){
	int temp;
	if(a<0)temp=-a;
	else temp=a;
	return temp;
}

void Motor_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Structure);
}

void Set_Direction(u8 dir){
	if(dir==1){
		GPIO_SetBits(GPIOB,GPIO_Pin_4);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);//1轮
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);//2轮
	}
	else{
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
	}
}

void Set_Pulse(void){
	if(KEY0==0){pulse+=10;}
	if(KEY1==0){pulse-=10;}
	if(pulse<0){pulse=0;}
	if(pulse>600){pulse=600;}
}

int PID_Position(int Encoder_Num,int Current_Setpulse){//增量式PID
	int ierror;
	int increase;
	ierror=Encoder_Num-Current_Setpulse;
//	increase=P*(ierror-error_l)+I*error_l;
	increase=P*(ierror-error_l)+I*error_l+D*(ierror-2*error_l+error_ll);
	error_l=ierror;
	error_ll=error_l;
	return increase;
}

void Limit_PWM(void){
	int PWM_Limit=7100;
	if(tpwm<-PWM_Limit)tpwm=-PWM_Limit;
	if(tpwm>PWM_Limit)tpwm=PWM_Limit;
}

void Set_PWM(void){
//	if(tpwm>0){
//		Set_Direction(1);
//	}
//	else {
//		Set_Direction(0);
//	}
	TIM_SetCompare1(TIM4,myabs(tpwm));
}

int ReadEncoder(u8 ch){
	int result;
	switch(ch){
		case 3:result=TIM_GetCounter(TIM3);TIM_SetCounter(TIM3,0);break;
		case 5:result=TIM_GetCounter(TIM5);TIM_SetCounter(TIM5,0);break;
		default:result=0;break;
	}
	if(result>60000)result=65535-result;
	return result;
}

