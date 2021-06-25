


#ifndef __HX711_H_
#define __HX711_H_

#include <reg51.h>

/* PIN口定义 */
sbit A_SCK = P2^0;
sbit A_DOUT = P2^1;

// 读取数据
unsigned long ReadCount(void);

unsigned long AD_average(void); 

unsigned long AD_median(void);



#endif
