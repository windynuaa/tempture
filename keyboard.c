
#include "keyboard.h"                  // Device header

void keyboard_init()
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio);
}

char get_keyboard()
{
	char val;
	val=0;
	GPIOB->ODR=0x0f;
	switch(GPIOB->IDR&0x0f)
	{
		case 0xe:val=0;break;
		case 0xd:val=1;break;
		case 0xc:val=2;break;
		case 0x7:val=3;break;
	}
	GPIOB->ODR=0xf0;
	switch(GPIOB->IDR&0xf0)
	{
		case 0xe0:val+=0;break;
		case 0xd0:val+=1;break;
		case 0xc0:val+=2;break;
		case 0x70:val+=3;break;
	}
	return val;
}

void set_alarm(int *gate)
{
	int a,count;
	char b=1;
	a=0;
	count=0;
	while(count<GATE_LEN)
	{
		b=get_keyboard();
		a+=b;
		a*=10;
		count++;
	}
	*gate=a;
}