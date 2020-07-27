#include "stm32f10x.h"
#include "USART.h"
#include "ht16xx.h"
//#include "stm32f10x.h"
extern void Delayus(__IO uint32_t nTime);


const uint8_t Lcd_Seg[10]={LCD_D_0,LCD_D_1,LCD_D_2,LCD_D_3,LCD_D_4,LCD_D_5,LCD_D_6,LCD_D_7,LCD_D_8,LCD_D_9};

/*
    PB12 HT1621B CS
    PB13 HT1621B RD
    PB14 HT1621B WR
    PB15 HT1621B DAT
*/
#define    HT_CS_SET    GPIOB->BSRR=GPIO_Pin_12
#define    HT_RD_SET    GPIOB->BSRR=GPIO_Pin_13
#define    HT_WR_SET    GPIOB->BSRR=GPIO_Pin_14
#define    HT_DA_SET    GPIOB->BSRR=GPIO_Pin_15

#define    HT_CS_RESET  GPIOB->BRR=GPIO_Pin_12
#define    HT_RD_RESET  GPIOB->BRR=GPIO_Pin_13
#define    HT_WR_RESET  GPIOB->BRR=GPIO_Pin_14
#define    HT_DA_RESET  GPIOB->BRR=GPIO_Pin_15



void HT_Port_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	

	GPIO_SetBits(GPIOB, GPIO_Pin_11);//set 1
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
}


//void HT_Write(uint8_t lcdbuf, uint8_t lcdbit)
//{
//uint8_t i=0;	
//for (i=0;i<lcdbit;i++)
//	{
//		HT_WR_RESET;
//		Delayus(100);
////		HT_DA_RESET;
////		Delayus(100);
//		if(lcdbuf&0x80)
//		{
//			HT_DA_SET;
//		}
//		else
//		{
//			HT_DA_RESET;
//		}
//		Delayus(100);
//		lcdbuf<<=1;
//		Delayus(100);
//		HT_WR_SET;
//		Delayus(100);
//	}
//}

//void HT_Config(void)
//{
//	HT_Port_Config();
//	HT_CS_RESET;
//	Delayus(100);
//	HT_Write(0x80,3);// 100 Command
//	HT_Write(0x18,9);//ON Chip RC
//	HT_Write(0x29,9);//1/3 bias 4 Com
//	HT_Write(0x01,9);//SYS EN 
//	HT_Write(0x03,9);//EN BIAS Generator
//	
//	Delayus(100);
//	HT_CS_SET;
//	
//}

//void HT_Test(void)
//{
//	HT_CS_SET;
//	Delayus(100);
//	HT_CS_RESET;
//	Delayus(100);
//	HT_Write(0xA0,3);//101  Dat
//	HT_Write(0x00,7);//1st ADDR
//	HT_Write(0xFf,4);//00
//	HT_Write(0x00,4);//01
//	HT_Write(0xFF,4);//02
//	HT_Write(0x00,4);//03
//	HT_Write(0xFF,4);//04
//	HT_Write(0x00,4);//05
//	HT_Write(0xFF,4);//06
//	HT_Write(0x00,4);//07
//	HT_Write(0xFF,4);//08
//	HT_Write(0x00,4);//09
//	HT_Write(0xFF,4);//10
//	HT_Write(0x00,4);//09
//	HT_Write(0xFF,4);//12
//	HT_CS_SET;
//	Delayus(100);
//}

//void HT_Update_Number(uint16_t num)
//{
//uint8_t tab[6]={0xff,0xff,0xff,0xff,0xff,0xff};
//uint8_t i;

//if(num>=1000)
//{
//tab[0] = Lcd_Seg[(num%1000/100)];
//tab[1] = (Lcd_Seg[(num%1000/100)]<<4)|(LCDBASE_DP<<4) ;//"1"
//}
//else
//{
//tab[0] = Lcd_Seg[(num%1000/100)];
//tab[1] = (Lcd_Seg[(num%1000/100)]<<4) ;
//}
//tab[2] = Lcd_Seg[(num%100/10)];
//tab[3] = (Lcd_Seg[(num%100/10)]<<4)|(LCDBASE_DP<<4) ;//"."
//tab[4] = Lcd_Seg[(num%10)];
//tab[5] = (Lcd_Seg[(num%10)]<<4)|(LCDBASE_DP<<4) ;//"mhz"

//	HT_CS_SET;
//	Delayus(100);
//	HT_CS_RESET;
//	Delayus(100);
//	HT_Write(0xA0,3);
//	HT_Write(0x00,7);
//  for(i=0;i<6;i++)
//	{
//		HT_Write(tab[i],4);
//		HT_Write(0x00,4);
//	}
//	//HT_Write(0xff,4);//"FM"
//	HT_CS_SET;
//	Delayus(100);
//}
///*---------------Low---------------------
//uint8_t buf 
//uint8_t len
//-*/
void HT_highWrite(uint8_t buf, uint8_t len)//高位先来
{
  uint8_t i;
	for(i=0;i<len;i++)
	{
		HT_WR_RESET;
//    Delayus(100);
		if(buf&0x80)
		{
		 HT_DA_SET;
		}
		else
		{
			HT_DA_RESET;
		}
	   Delayus(100);
		 HT_WR_SET;
		 Delayus(100);
	   buf<<=1;
	}
}
///*---------------Low---------------------
//uint8_t buf 
//uint8_t len
//-*/
void HT_LowWrite(uint8_t buf, uint8_t len)//低位先来
{
	  uint8_t i;
	for(i=0;i<len;i++)
	{
		HT_WR_RESET;
		if(buf&0x01)
		{
		 HT_DA_SET;
		}
		else
		{
			HT_DA_RESET;
		}
	   Delayus(100);
		 HT_WR_SET;
		 Delayus(100);
	   buf>>=1;
	}
}

///*-------------------

//----------------*/
void HT_WriteCmd(uint8_t Cmd)
{
	HT_CS_RESET;
	Delayus(100);
  HT_highWrite(0x80, 3);//0x100  
	HT_highWrite(Cmd, 9);
	Delayus(100);
	HT_CS_SET;	
}
///*-------------------

//----------------*/
void HT_WriteDat(uint8_t Addr, uint8_t Dat)
{
	HT_CS_RESET;
	Delayus(100);
  HT_highWrite(0xA0, 3);
	HT_highWrite(Addr<<2, 6);
	HT_highWrite(Dat,4);
	Delayus(100);
	HT_CS_SET;	
}
///*-------------------
//void HT_Config(void)
//	HT_Write(0x18,9);//ON Chip RC
//	HT_Write(0x29,9);//1/3 bias 4 Com
//	HT_Write(0x01,9);//SYS EN 
//	HT_Write(0x03,9);//EN BIAS Generator
//----------------*/
void HT_Config(void)
{
  HT_Port_Config();
//	HT_CS_RESET;
//	Delayus(100);
	HT_WriteCmd(0x18);
  HT_WriteCmd(0x29);
	HT_WriteCmd(0x01);
	HT_WriteCmd(0x03);
//	Delayus(100);
//	HT_CS_SET;
}
///*-------------------

//----------------*/
void HT_Test()
{
	 uint8_t i,s=0x11;
	 uint16_t n=0;
	 HT_WriteDat(0x00,0x10);
	 HT_WriteDat(0x01,0x80);
	 HT_WriteDat(0x02,0xF0);
	 HT_WriteDat(0x03,0xF0);
	 HT_WriteDat(0x04,0xF0);
	 HT_WriteDat(0x05,0xF0);
	 HT_WriteDat(0x06,0xF0);
   HT_WriteDat(0x07,0xF0);
	 HT_WriteDat(0x08,0xF0);
	 HT_WriteDat(0x09,0xF0);
	 HT_WriteDat(0x0A,0xF0);
	 HT_WriteDat(0x0B,0xF0);
   HT_WriteDat(0x0C,0xF0);
	 HT_WriteDat(0x0D,0xF0);
	 Delayus(200000);
	 for(i=0;i<14;i++)
	{  
		 HT_WriteDat(i-1,0x00);
		 HT_WriteDat(i,s);
		 HT_WriteDat(i+1,0x00);
		 Delayus(100000);
		 s<<=1;
	}
//	 HT_WriteDat(0x00,0x10);
//	 HT_WriteDat(0x01,0x10);
//	 HT_WriteDat(0x02,0x20);
//	 HT_WriteDat(0x03,0x20);
//	 HT_WriteDat(0x04,0x40);
//	 HT_WriteDat(0x05,0x40);
//	 HT_WriteDat(0x06,0x80);
//   HT_WriteDat(0x07,0x80);
//	 HT_WriteDat(0x08,0xF0);
//	 HT_WriteDat(0x09,0xF0);
//   Delayus(1000000);
	 Delayus(1000000);
	 HT_WriteDat(SEG_A, LCD_R_A);
   HT_WriteDat(SEG_B, LCD_U_REPAIR|LCD_R_V);
   HT_WriteDat(SEG_C, LCD_U_DENGER);
	 HT_WriteDat(SEG_D, LCD_U_WAIT);
   for(n=0;n<65535;n++)
	 {
	 HT_DecNum_Display(n);
	 Delayus(500000);
	 }
}

void HT_DecNum_Display(uint16_t num)
{
	uint8_t i;
	uint8_t tab[5]={0x00,0x00,0x00,0x00,0x00};

	tab[0]=Lcd_Seg[(num/10000)];
	tab[1]=Lcd_Seg[(num%10000/1000)];//1000
	tab[2]=Lcd_Seg[(num%1000/100)];//100
	tab[3]=Lcd_Seg[(num%100/10)];//10
	tab[4]=Lcd_Seg[(num%10)];//1
	
	
	HT_CS_RESET;
	Delayus(100);
  HT_highWrite(0xA0, 3);//dat
	HT_highWrite(0x00, 6);//Addr=0000000
	for(i=0;i<5;i++)
	{
	 HT_highWrite(tab[i],8);
	}
	Delayus(100);
	HT_CS_SET;	
}

 
