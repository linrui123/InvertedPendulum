#include "oled.h"
#include "delay.h"
#include "oledfont.h"
#include "bmp.h"
#include "string.h"
#include "usart2.h"

#define Max_Column 128
#define Max_Row    64
u8 OLED_GRAM[128][8];	

void IIC_Start(void){
	OLED_CLK_Set();
	OLED_SDA_Set();
	OLED_SDA_Clr();
	OLED_CLK_Clr();
}
void IIC_Stop(void){
	OLED_CLK_Set();
	OLED_SDA_Clr();
	OLED_SDA_Set();
}
void IIC_Write_Cmd(u8 IIC_Cmd){
	IIC_Start();
	IIC_Write_Byte(0x78);//Slave Address,SA0=0
	IIC_Wait_Ack();
	IIC_Write_Byte(0x00);//写命令
	IIC_Wait_Ack();
	IIC_Write_Byte(IIC_Cmd);
	IIC_Wait_Ack();
	IIC_Stop();
}
void IIC_Write_Data(u8 IIC_Data){
	IIC_Start();
	IIC_Write_Byte(0x78);
	IIC_Wait_Ack();
	IIC_Write_Byte(0x40);//写数据
	IIC_Wait_Ack();
	IIC_Write_Byte(IIC_Data);
	IIC_Wait_Ack();
	IIC_Stop();
}
void IIC_Write_Byte(u8 IIC_Byte){
	u8 i,data,m;
	data=IIC_Byte;
	OLED_CLK_Clr();
	for(i=0;i<8;i++){
		m=data;
		m=m&0x80;
		if(m==0x80){
			OLED_SDA_Set();
		}else{
			OLED_SDA_Clr();
		}
		data=data<<1;
		OLED_CLK_Set();
		OLED_CLK_Clr();
	}
}
void IIC_Wait_Ack(void){
	OLED_CLK_Set();
	OLED_CLK_Clr();
}

void OLED_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_15;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_Structure);
	GPIO_SetBits(GPIOG,GPIO_Pin_8);
	GPIO_SetBits(GPIOG,GPIO_Pin_15);
	
	delay_ms(200);
	
	OLED_Write_Byte(0xae,OLED_CMD);//关闭显示
	
	OLED_Write_Byte(0x40,OLED_CMD);//设置列低地址
	OLED_Write_Byte(0xB0,OLED_CMD);//设置列高地址
	
	OLED_Write_Byte(0xc8,OLED_CMD);//
	
	OLED_Write_Byte(0x81,OLED_CMD);//设置对比度
	OLED_Write_Byte(0xff,OLED_CMD);
	
	OLED_Write_Byte(0xa1,OLED_CMD);
	
	OLED_Write_Byte(0xa6,OLED_CMD);
	
	OLED_Write_Byte(0xa8,OLED_CMD);//设置驱动路数
	OLED_Write_Byte(0x1f,OLED_CMD);
	
	OLED_Write_Byte(0xd3,OLED_CMD);
	OLED_Write_Byte(0x00,OLED_CMD);
	
	OLED_Write_Byte(0xd5,OLED_CMD);
	OLED_Write_Byte(0xf0,OLED_CMD);
	
	OLED_Write_Byte(0xd9,OLED_CMD);
	OLED_Write_Byte(0x22,OLED_CMD);
	
	OLED_Write_Byte(0xda,OLED_CMD);
	OLED_Write_Byte(0x02,OLED_CMD);
	
	OLED_Write_Byte(0xdb,OLED_CMD);
	OLED_Write_Byte(0x49,OLED_CMD);
	
	OLED_Write_Byte(0x8d,OLED_CMD);
	OLED_Write_Byte(0x14,OLED_CMD);
	
	OLED_Write_Byte(0xaf,OLED_CMD);
	OLED_Clear();
}

void OLED_Write_Byte(u8 data,u8 cmd){
	if(cmd){
		IIC_Write_Data(data);
	}else{
		IIC_Write_Cmd(data);
	}
}

void OLED_Clear(void){
	u8 i,n;
	for(i=0;i<8;i++){
		OLED_Write_Byte(0xb0+i,OLED_CMD);
		OLED_Write_Byte(0x00,OLED_CMD);//列低地址
		OLED_Write_Byte(0x10,OLED_CMD);//列高地址
		for(n=0;n<128;n++)OLED_Write_Byte(0,OLED_DATA);
	}
}

void OLED_Set_Pos(unsigned char x, unsigned char y){
	OLED_Write_Byte(0xb0+y,OLED_CMD);
	OLED_Write_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_Write_Byte((x&0x0f),OLED_CMD);
}

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size){
	u8 c=0,i;
	c=chr-' ';
	if(x>Max_Column-1){x=0;y=y+2;}
	if(Char_Size==16){
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++){
			OLED_Write_Byte(F8X16[c*16+i],OLED_DATA);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++){
			OLED_Write_Byte(F8X16[c*16+i+8],OLED_DATA);
		}
	}else{
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++){
			OLED_Write_Byte(F6x8[c][i],OLED_DATA);
		}
	}
}

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size,u8 str_len){
	u8 j=0;

	while(chr[j]!='\0'){
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x+=8;
		if(x>128){
			x=0;
			y+=2;
		}
		j++;
	}
	
	while(j<str_len){  //消除多余位数
		OLED_ShowChar(x,y,' ',Char_Size);
		x+=8;
		if(x>128){
			x=0;
			y+=2;
		}
		j++;
	}
}

char * myitoa(int num,char *str){                //10进制
	int i,d;
	int flag=0;
	char *ptr=str;
	if(!num){
		*ptr++=0x30;
		*ptr=0;
		return str;
	}
	if(num<0){
		*ptr++='-';
		num=-num;
	}
	for(i=10000;i>0;i=i/10){
		d=num/i;
		if(d||flag){
			*ptr++=(char)(0x30+d);
			num=num-d*i;
			flag=1;
		}
	}
	*ptr=0;
	return str;
}

