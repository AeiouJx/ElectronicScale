
#include <intrins.h>   // _nop()_
#include "HX711.h"

// 缓冲区大小
#define M	5		// 中值滤波
#define N	16		// 平均滤波

unsigned long ReadCount(void)
{
	unsigned long datA = 0;
	unsigned char i = 0;

	A_DOUT = 1;	   // DOUT置1
	_nop_();
	_nop_();	
	A_SCK = 0;	   // SCK置0
	datA = 0;

	// 等待HX711_DOUT下降沿到来
	while(A_DOUT && i<50);	 // AD转换未结束则等待 否则开始读取数据
	{
		_nop_();
		_nop_();
		i++;
	}
	// 发送24个脉冲，读取24位数据
	for(i = 0;i < 24; i++)	
	{
		A_SCK = 1;	   // SCK置1 发送一个脉冲 读取一位数据
		_nop_();
		datA = datA << 1;	 // 下降沿来时dat变量左移一位 右侧补零
		A_SCK = 0;
		if(A_DOUT)	// DOUT为高电平 
			datA++;
	}
	// 第25个脉冲 增益为128
	A_SCK = 1;
	_nop_();
	datA = datA ^ 0x800000;  
	A_SCK = 0;
	return(datA);
}


unsigned long AD_median(void) 
{
	unsigned long buff[M],temp; //定义存储数据的数组
	unsigned char i = 0,j = 0;
	
	// 数据采集
	for(i = 0; i < M; i++)
	{
		buff[i] = ReadCount();
		_nop_();
	}
    
	// 排序(冒泡) 
	for(j = 0; j < M-1; j++)
    {
		for(i = 0; i < M-1-j; i++)
		{
	        if(buff[i] > buff[i+1])	
	        {
	            temp = buff[i];
	            buff[i] = buff[i+1];
	            buff[i+1] = temp;
	        }
		}
    }
	return buff[(M-1)/2];  // 中值
}
// 773414 8615179

unsigned long AD_average(void)
{	
	unsigned long sum = 0;
	unsigned char i = 0;


	for(i = N; i > 0; i--) 
	{
		sum += AD_median();
	}
	return (unsigned long)(sum / N);
}
