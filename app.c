

#include "app.h"

#include "HX711.h"
#include "lcd.h"
#include "uart.h"
#include "timer0.h"
#include "key.h"

unsigned char DisBuf[7] = {0};

void ftoc(unsigned long value) {

	DisBuf[0] = value / 1000000 % 10;  
	DisBuf[1] = value / 100000 % 10;
	DisBuf[2] = value / 10000 % 10;
	DisBuf[3] = value / 1000 % 10;
	DisBuf[4] = value / 100 % 10;
	DisBuf[5] = value / 10 % 10;			 
	DisBuf[6] = value  % 10;
}


void LcdDisp(struct Scale s) { 
	unsigned char i = 0;

	ftoc(s.refAD);
	LcdWriteCom(0x80);

	do{
		LcdWriteData(0x30+DisBuf[i]);
		i++;	 
	}while(i < 7);

	i=0;
	ftoc(s.nowAD);
	LcdWriteData(' ');
	do{
		LcdWriteData('0'+DisBuf[i]);
		i++;	 
	}while(i < 7);

	i=0;
	ftoc(s.weight);
	LcdWriteCom(0x80+0x40);
	LcdWriteStr("Wegiht:");
	// 单位
	if(s.weight > 1000)
	{
		do{
			LcdWriteData('0'+DisBuf[i]);
			if(2 == i) {
				LcdWriteData('.');
			}
			i++;	 
		}while(i < 6);
		LcdWriteStr("kg");
	}
	else
	{
		do{
			LcdWriteData('0'+DisBuf[i]);
			i++;	 
		}while(i < 6);
		LcdWriteStr("  g");
	}		
}


/* BT蓝牙发送数据 */
void BTSend(unsigned char *ptr) {

	unsigned char i = 0;

	uartSendStr(" >> The Value is: ");
	do{
		uartSendChr('0'+ptr[i++]);
	}while(i < 6);
	//uartSendStr("kg!");
}


