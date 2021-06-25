 
/*
	FileName	: lcd.c
	Author		: Tkz
	Date		: 2021.02.5
*/

#include "lcd.h"

void ReadBusy(void)           //æ��⺯�����ж�bit7��0������ִ�У�1��ֹ
{
    unsigned char statu;      //
    LCD1602_DATAPINS = 0xff;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_EN = 1;
        statu = LCD1602_DATAPINS;
        LCD1602_EN = 0;    //ʹ�ܣ���������ͣ��ͷ�����
    }while(statu & 0x80);
}

void Lcd1602_Delay1ms(unsigned int c)   //��� 0us
{
    unsigned char a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	} 	
}

/* LCD1602д������ */
void LcdWriteCom(unsigned char com)	  //д������
{
	ReadBusy();
	LCD1602_EN = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��д������ ����/����ѡ���(H/L) 1/0
	LCD1602_RW = 0;	   //ѡ��д�� ��/дѡ���(H\L)     1/0
	
	LCD1602_DATAPINS = com;     //��������
	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

	LCD1602_EN = 1;	          //д��ʱ��
	Lcd1602_Delay1ms(5);	  //����ʱ��
	LCD1602_EN = 0;
}

/* LCD1602д������ */		   		   
void LcdWriteData(unsigned char dat)			//д������
{
	ReadBusy();
	LCD1602_EN = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;   //д��ʱ��
	Lcd1602_Delay1ms(5);   //����ʱ��
	LCD1602_EN = 0;
}
void delay_ms(unsigned char ms);
/* LCD1602��ʼ�� */	   
void Lcd1602Init(void)						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ 5*8,8λ����
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	//LcdWriteCom(0x0f); // ��ʾ��겢��˸
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����

	//LcdWriteCom(0x80);
	LcdWriteStr(" Welcome To Use ");
	LcdWriteCom(0x80+0x40);
	LcdWriteStr("Electronic Scale");
}



/* ��ָ��λ����ʾ�ַ��� */
void LcdWriteStr(unsigned char * str){
	while(*str != '\0'){
		LcdWriteData(*str++);
	}	
}



