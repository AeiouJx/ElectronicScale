
#ifndef __APP_H_
#define __APP_H_

#include <reg51.h>

extern unsigned char DisBuf[7];	

struct Scale{
	unsigned long refAD;	// 参考值
	unsigned long nowAD;	// 测量值
	long weight;	// 实际重量值
	float rate;				// 转换比例
};

void ftoc(unsigned long value); 

/* 数据显示 */
void LcdDisp(struct Scale s);

/* BT蓝牙发送数据 */
void BTSend(unsigned char *ptr);


#endif
