#include "adc.h"

int Angle_ADC_Value;

void ADC_DMA_Init(void){
	DMA_InitTypeDef DMA_Structure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_Structure.DMA_BufferSize=4096;
	DMA_Structure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_Structure.DMA_M2M=DMA_M2M_Disable;
	DMA_Structure.DMA_MemoryBaseAddr=(u32)&Angle_ADC_Value;
	DMA_Structure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_Structure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_Structure.DMA_Mode=DMA_Mode_Circular;
	DMA_Structure.DMA_PeripheralBaseAddr=(u32)&ADC1->CR1;
	DMA_Structure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_Structure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_Structure.DMA_Priority=DMA_Priority_High;
	
	DMA_Init(DMA1_Channel1,&DMA_Structure);
}

void Angle_ADC_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	ADC_InitTypeDef ADC_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72M/6=12MHz<<14MHz
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_Structure);
	
	ADC_DeInit(ADC1);
	
	ADC_Structure.ADC_ContinuousConvMode=DISABLE;//单次转换模式
	ADC_Structure.ADC_DataAlign=ADC_DataAlign_Right;//数据右对齐
	ADC_Structure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//不启动外部触发，使用内部软件转换
	ADC_Structure.ADC_Mode=ADC_Mode_Independent;//独立工作模式
	ADC_Structure.ADC_NbrOfChannel=1;//顺序进行规则转换的ADC通道的数目
	ADC_Structure.ADC_ScanConvMode=DISABLE;//单通道模式
	ADC_Init(ADC1,&ADC_Structure);
	
	ADC_DMACmd(ADC1,ENABLE);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_DMA_Init();
	
	ADC_ResetCalibration(ADC1);
	
	while(ADC_GetResetCalibrationStatus(ADC1));	
	
	ADC_StartCalibration(ADC1);
	
	while(ADC_GetCalibrationStatus(ADC1));
}

u16 Get_ADC(u8 ch){
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5);//adc1,采样时间239.5周期
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//使能指定的adc1的软件转换功能
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
	return ADC_GetConversionValue(ADC1);
}

u16 Get_ADC_Average(u8 ch,u8 times){
	u8 i;
	u16 value=0;
	for(i=0;i<times;i++){
		value+=Get_ADC(ch);
		delay_ms(5);
	}
	return value/times;
}

