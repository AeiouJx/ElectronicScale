

#ifndef __FILTER_H_
#define __FILTER_H_


/* 中值滤波 */
#define N 11
char filter() 
{
	char value_buff[N],temp; //定义存储数据的数组 8 9    
	char count = 0,i = 0,j = 0;
    for(count=0;count<N;count++)
    {
        value_buf[count]=get_data();
        delay(); //如果采集数据比较慢，那么就需要延时或中断1819    
	}   
	for(j=0;j<N;j++)
    {
        if(value_buff[i]>value_buff[i+1])
        {
            temp=value_buff[i];
            value_buff[i]=value_buff[i+1];
            value_buff[i+1]=temp;
        }
    }
	return value_buff[(N-1)/2];
}
/* 算术平均滤波算法 */
unsigned long Average(unsigned char times) {
	
	unsigned long sum = 0;
	unsigned char i = 0;
	for(i = times; i > 0; i--) 
	{
		sum += HX711_Read();
		//delay();
	}
	return (unsigned long)(sum / times);
}
/* 加权平均值滤波法 */
//code数组为加权系数表，存在程序存储区
char code jq[N]={1,2,3,4,5,6,7,8,9,10,11,12};
char code sum_jq = 1+2+3+4+5+6+7+8+9+10+11+12;
char filter()
{
	char count = 0;
	char value_buff[N];
	int sum = 0;
	for(count = 0;count < N;count++)
	{
		value_buff[count] = get_data();
		delay();
	}
	for(count = 0; count < N; count++)
	{
		sum += value_buff[count]*jq[count];
	}
	return (char)(sum / sum_jq);
}
/* 滑动平均滤波算法 */
char value_buff[N];
char i = 0;
char filter()
{
	char count;
	int sum = 0;
	value_buff[i++] = get_data();
	if(i == N)
		i = 0;
	for(count = 0; count < N; count++)
	{
		sum += value_buff[count];
	}
	return (char)(sum / N);
}

#endif



