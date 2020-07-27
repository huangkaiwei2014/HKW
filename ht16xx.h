#ifndef __HT16XX_H_
#define __HT16XX_H_

#ifndef u16
#define unsigned short int  u16
#endif

//液晶背光 PB11
#define    LCD_BLK_ON     GPIOB->BSRR=GPIO_Pin_11
#define    LCD_BLK_OFF    GPIOB->BRR=GPIO_Pin_11
#define    LED_MUTE_ON    GPIOB->BSRR=GPIO_Pin_10
#define    LED_POWER_ON   GPIOB->BSRR=GPIO_Pin_9
#define    LED_MUTE_OFF   GPIOB->BRR=GPIO_Pin_10
#define    LED_POWER_OFF  GPIOB->BRR=GPIO_Pin_9

/*---------------------显示表-------------------*/
/*
    AAAAAAAA
	F	        B   
	F					B
	F			  	B
	F				  B
	 GGGGGGGGG					
	E			   	C
	E				  C
	E				  C
	E				  C
	 DDDDDDDD	   dp
*/
/*-------------------------------LCD Display Table------------------------------------------------
	    SEG0	SEG1  SEG2	SEG3  SEG4	SEG5  SEG6	SEG7  SEG8	SEG9  SEG10  SEG11	SEG12  SEG13
COM0  1D	  DP1	  2D	  DP2	  3D	  DP3	  4D	  DP4	  5D	  DP5		`C		               X      14   0001
COM1  1E	  1C	  2E	  2C	  3E	  3C	  4E	  4C	  5E	  5C	  hour	 X	    |_     U>     15   0010	
COM2  1F	  1G	  2F	  2G	  3F	  3G	  4F	  4G	  5F	  5G	  VA	   Hz		  X      U<     16   0100
COM3  1A	  1B    2A	  2B	  3A	  3B	  4A	  4B	  5A	  5B	  A  	   V	    :	     I>     17   1000
-----------------------------------------------------------------------------------------------*/
//数字字模部分
#define     LCDBASE_A     0x80
#define     LCDBASE_B     0x08
#define     LCDBASE_C     0x02
#define     LCDBASE_D     0x10
#define     LCDBASE_E     0x20
#define     LCDBASE_F     0x40
#define     LCDBASE_G     0x04
#define     LCDBASE_DP    0x01  //小数点 

#define     LCD_D_0      (LCDBASE_A | LCDBASE_B | LCDBASE_C | LCDBASE_D |LCDBASE_E |LCDBASE_F)
#define     LCD_D_1      (LCDBASE_B | LCDBASE_C)
#define     LCD_D_2      (LCDBASE_A | LCDBASE_B | LCDBASE_D |LCDBASE_E |LCDBASE_G)
#define     LCD_D_3      (LCDBASE_A | LCDBASE_B | LCDBASE_C |LCDBASE_D |LCDBASE_G)
#define     LCD_D_4      (LCDBASE_B | LCDBASE_C | LCDBASE_F |LCDBASE_G)
#define     LCD_D_5      (LCDBASE_A | LCDBASE_C | LCDBASE_D |LCDBASE_F |LCDBASE_G)
#define     LCD_D_6      (LCDBASE_A | LCDBASE_C | LCDBASE_D |LCDBASE_E |LCDBASE_F |LCDBASE_G)
#define     LCD_D_7      (LCDBASE_A | LCDBASE_B | LCDBASE_C )
#define     LCD_D_8      (LCDBASE_A | LCDBASE_B | LCDBASE_C | LCDBASE_D |LCDBASE_E |LCDBASE_F |LCDBASE_G)
#define     LCD_D_9      (LCDBASE_A | LCDBASE_B | LCDBASE_C | LCDBASE_D |LCDBASE_F |LCDBASE_G)
#define     LCD_D_A      (LCDBASE_A | LCDBASE_B | LCDBASE_C | LCDBASE_E |LCDBASE_F |LCDBASE_G)
#define     LCD_D_C      (LCDBASE_A | LCDBASE_D | LCDBASE_E | LCDBASE_F)
#define     LCD_D_E      (LCDBASE_A | LCDBASE_D | LCDBASE_E | LCDBASE_F |LCDBASE_G)
#define     LCD_D_F      (LCDBASE_A | LCDBASE_B | LCDBASE_E | LCDBASE_F |LCDBASE_G)
#define     LCD_D_H      (LCDBASE_B | LCDBASE_C | LCDBASE_E |LCDBASE_F  |LCDBASE_G)
#define     LCD_D_U      (LCDBASE_F | LCDBASE_D | LCDBASE_E | LCDBASE_C |LCDBASE_B)
#define     LCD_D_YOKO   (LCDBASE_G)

//选项字符
#define     SEG_A         0x0A
#define     SEG_B         0x0B
#define     SEG_C         0x0C
#define     SEG_D         0x0D
//SEG11     0x0A
#define     LCD_R_A       0x80
#define     LCD_R_VA      0x40
#define     LCD_R_HOUR    0x20
#define     LCD_R_TEMPC   0x10
//SEG12     0x0b
#define     LCD_R_V       0x80
#define     LCD_R_HZ      0x40
#define     LCD_U_REPAIR  0x20
//#define     LCD_O_TEMPC   0x10
//SEG13     0x0c
#define     LCD_O_MAOHAO  0x80
#define     LCD_U_DENGER  0x40
#define     LCD_U_TEMPJI  0x20
//#define     LCD_O_TEMPC   0x10
//SEG14     0x0d
#define     LCD_U_IDY    0x80
#define     LCD_U_UXY    0x40
#define     LCD_U_UDY    0x20
#define     LCD_U_WAIT   0x10


//void Timer_PWM_Init(uint16_t arr,uint16_t psc);
//void Timer_Init(uint16_t arr, uint16_t div);

//void NVIC_Config(void);



//函数声明
void HT_Port_Config(void);
//void HT_Write(uint8_t lcdbuf, uint8_t lcdbit);
void HT_Config(void);
void HT_Test(void);
void HT_DecNum_Display(uint16_t num);
//void HT_Update_Number(uint16_t num);





























#endif
