
#ifndef __APP_H_
#define __APP_H_

#include <reg51.h>

extern unsigned char DisBuf[7];	

struct Scale{
	unsigned long refAD;	// �ο�ֵ
	unsigned long nowAD;	// ����ֵ
	long weight;	// ʵ������ֵ
	float rate;				// ת������
};

void ftoc(unsigned long value); 

/* ������ʾ */
void LcdDisp(struct Scale s);

/* BT������������ */
void BTSend(unsigned char *ptr);


#endif
