#include "show.h"
#include "oled.h"
#include "delay.h"
#include "string.h"
#include "encoder.h"

extern int Encoder_Left;
extern int Encoder_Right;
extern int Speed;
extern int pulse;
extern int tpwm;

extern int Angle_ADC_Value;

void OLED_Show(void){
	u8 str[10];

	OLED_ShowString(0,0,(u8 *)"code:",8,10);
	myitoa(Encoder_Left,(char *)str);
	OLED_ShowString(45,0,(u8 *)str,8,10);
	myitoa(Encoder_Right,(char *)str);
	OLED_ShowString(90,0,(u8 *)str,8,10);

	
	OLED_ShowString(0,1,(u8 *)"SetPulse:",8,10);
	myitoa(pulse,(char *)str);
	OLED_ShowString(80,1,(u8 *)str,8,5);
	
	OLED_ShowString(0,2,(u8 *)"tpwm:",8,10);
	myitoa(tpwm,(char *)str);
	OLED_ShowString(80,2,(u8 *)str,8,5);
	
	OLED_ShowString(0,3,(u8 *)"ADC:",8,10);
	myitoa(Angle_ADC_Value,(char *)str);
	OLED_ShowString(80,3,(u8 *)str,8,10);
}

