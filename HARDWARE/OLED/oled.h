#ifndef _OLED_H
#define _OLED_H

#include "stm32f10x.h"
#include "stdlib.h"

#define OLED_CLK_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define OLED_CLK_Set() GPIO_SetBits(GPIOC,GPIO_Pin_6)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_7)
#define OLED_SDA_Set() GPIO_SetBits(GPIOC,GPIO_Pin_7)

#define OLED_CMD 0 //Ð´ÃüÁî
#define OLED_DATA 1 //Ð´Êý¾Ý

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Write_Cmd(u8 IIC_Cmd);
void IIC_Write_Data(u8 IIC_Data);
void IIC_Write_Byte(u8 IIC_Byte);
void IIC_Wait_Ack(void);

void OLED_Init(void);
void OLED_Clear(void);
void OLED_Write_Byte(u8 data,u8 cmd);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size,u8 str_len);
char * myitoa(int num,char *str);
#endif

