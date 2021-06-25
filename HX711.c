
#include <intrins.h>   // _nop()_
#include "HX711.h"

// ��������С
#define M	5		// ��ֵ�˲�
#define N	16		// ƽ���˲�

unsigned long ReadCount(void)
{
	unsigned long datA = 0;
	unsigned char i = 0;

	A_DOUT = 1;	   // DOUT��1
	_nop_();
	_nop_();	
	A_SCK = 0;	   // SCK��0
	datA = 0;

	// �ȴ�HX711_DOUT�½��ص���
	while(A_DOUT && i<50);	 // ADת��δ������ȴ� ����ʼ��ȡ����
	{
		_nop_();
		_nop_();
		i++;
	}
	// ����24�����壬��ȡ24λ����
	for(i = 0;i < 24; i++)	
	{
		A_SCK = 1;	   // SCK��1 ����һ������ ��ȡһλ����
		_nop_();
		datA = datA << 1;	 // �½�����ʱdat��������һλ �Ҳಹ��
		A_SCK = 0;
		if(A_DOUT)	// DOUTΪ�ߵ�ƽ 
			datA++;
	}
	// ��25������ ����Ϊ128
	A_SCK = 1;
	_nop_();
	datA = datA ^ 0x800000;  
	A_SCK = 0;
	return(datA);
}


unsigned long AD_median(void) 
{
	unsigned long buff[M],temp; //����洢���ݵ�����
	unsigned char i = 0,j = 0;
	
	// ���ݲɼ�
	for(i = 0; i < M; i++)
	{
		buff[i] = ReadCount();
		_nop_();
	}
    
	// ����(ð��) 
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
	return buff[(M-1)/2];  // ��ֵ
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
