

#ifndef __FILTER_H_
#define __FILTER_H_


/* ��ֵ�˲� */
#define N 11
char filter() 
{
	char value_buff[N],temp; //����洢���ݵ����� 8 9    
	char count = 0,i = 0,j = 0;
    for(count=0;count<N;count++)
    {
        value_buf[count]=get_data();
        delay(); //����ɼ����ݱȽ�������ô����Ҫ��ʱ���ж�1819    
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
/* ����ƽ���˲��㷨 */
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
/* ��Ȩƽ��ֵ�˲��� */
//code����Ϊ��Ȩϵ�������ڳ���洢��
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
/* ����ƽ���˲��㷨 */
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



