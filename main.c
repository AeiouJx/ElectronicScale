

#include <reg51.h>
/* �ײ������ӿ�	*/
#include "lcd.h"	
#include "uart.h"	
#include "HX711.h"	
#include "timer0.h"	
#include "key.h"
/* Ӧ�ò� */
#include "app.h"	

		
/* ��������� */
void main(void) {
	unsigned char i = 0;
	
	struct Scale scale = {0,0,0,0.5};

	P0 = P1 = P2 = P3 = 0xFF;

	Lcd1602Init();	/* LCD��ʼ�� */
	uartInit();		/* UART��ʼ�� */
	timer0Init();	/* Timer0��ʼ�� */	
	EA = 1;			/* ���ж����� */
	//8615179			
	do{	  
		scale.refAD = AD_average();
		LcdDisp(scale);	
		i++;
	}while(i < 10);

	while(1) { 
		/* �������� */
		keyPros();
		
		/* �������� */
		scale.nowAD = AD_average();
		if(scale.nowAD > scale.refAD)
		{
			scale.nowAD = scale.nowAD - scale.refAD;
			scale.weight = (unsigned long)((float)scale.nowAD*scale.rate+0.05);
		}
		else
		{
			scale.weight = 0;
		}

		/* LCD��ʾ���� */
		if(flag_time&0x02) {
			flag_time &= ~0x02;	 // �����־λ
			LcdDisp(scale);
			delay_ms(10);
		}

		/* uart���ʹ��п����ݽ��� */		
		if(flag_time&0x04) {		// 1���ӣ�����һ������
			flag_time &= ~0x04;
			BTSend(DisBuf);	
		}

	}
}

