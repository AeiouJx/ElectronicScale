

#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>



// 独立按键 已接地
sbit K1 = P1^0;
sbit K2 = P1^1;
// 灯
sbit LED1 = P1^6;
sbit LED2 = P1^7;

// 延时函数
static void delayMs(unsigned char t);
void keyPros(void);


#endif


