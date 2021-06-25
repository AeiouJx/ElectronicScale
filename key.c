

#include "key.h"


// 延时函数
void delayMs(unsigned char t) {
    unsigned char a,b;
	for(; t>0; t--)
	{
		 for(b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	} 
}

// 独立按键
void keyPros(void) {

	if((K1 == 0)||(K2 == 0)) {
		delayMs(10);
		if((K1 == 0)||(K2 == 0)) {
			if(K1 == 0)
			{
				LED1 =! LED1;
			}
			else if(K2 == 0)
			{
				LED2 =! LED2;
			}
			while(K1 == 0);
			while(K2 == 0);
		}
	}
}


