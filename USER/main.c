#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "pwm.h"
#include "key.h"
#include "oled.h"
#include "string.h"
#include "stdlib.h"
#include "timer.h"
#include "encoder.h"
#include "control.h"
#include "show.h"
#include "usart2.h"
#include "adc.h"

int main(void)
{
	LED_Init();
	KEY_Init();
	delay_init();
	USART2_Init(115200);
	OLED_Init();
	Encoder_TIM3_Init();
//	Encoder_TIM5_Init();
	TIM4_PWM_Init(7199,99);//计数7200下,周期10ms,10kHz
	TIM1_Init(99,7199);//计时10ms
//	Angle_ADC_Init();
//	Motor_Init();
	
	
  while(1)
	{
		OLED_Show();
		LED_indicate();//工作灯指示
		Set_Pulse();
//		TIM_SetCompare1(TIM4,7000);//right
//		TIM_SetCompare2(TIM4,1000);//left
	}
}

