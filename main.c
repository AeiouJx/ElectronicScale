

#include <reg51.h>
/* 底层驱动接口	*/
#include "lcd.h"	
#include "uart.h"	
#include "HX711.h"	
#include "timer0.h"	
#include "key.h"
/* 应用层 */
#include "app.h"	

		
/* 主函数入口 */
void main(void) {
	unsigned char i = 0;
	
	struct Scale scale = {0,0,0,0.5};

	P0 = P1 = P2 = P3 = 0xFF;

	Lcd1602Init();	/* LCD初始化 */
	uartInit();		/* UART初始化 */
	timer0Init();	/* Timer0初始化 */	
	EA = 1;			/* 总中断允许 */
	//8615179			
	do{	  
		scale.refAD = AD_average();
		LcdDisp(scale);	
		i++;
	}while(i < 10);

	while(1) { 
		/* 按键处理 */
		keyPros();
		
		/* 测量体重 */
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

		/* LCD显示进程 */
		if(flag_time&0x02) {
			flag_time &= ~0x02;	 // 清除标志位
			LcdDisp(scale);
			delay_ms(10);
		}

		/* uart发送串行口数据进程 */		
		if(flag_time&0x04) {		// 1秒钟，发送一次数据
			flag_time &= ~0x04;
			BTSend(DisBuf);	
		}

	}
}

