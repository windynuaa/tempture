
#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include "ds18b20.h"
int delay_time;
//HCLK=72M
//PCLK2=72M
//PCLK1=36M;
//ds18b20 12 bit convert time : 750 ms
void delay_us(int a)
{
	SysTick->LOAD=a*9;          	// 72m=1s       
  SysTick->CTRL|=0x01;
	while(!(SysTick->CTRL&1<<16));
	SysTick->CTRL=0x00;
  SysTick->VAL =0X00;
}

void delay_ms(int a)
{
	SysTick->LOAD=a*9000;          	// 72m=1s       
  SysTick->CTRL|=0x01;
	while(!(SysTick->CTRL&1<<16));
	SysTick->CTRL=0x00;
  SysTick->VAL =0X00;
}
//init usart
void uart_init()
{
	USART_InitTypeDef uart;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_StructInit(&uart);
	uart.USART_BaudRate=9600;
	USART_Init(USART1,&uart);
	USART_Cmd(USART1,ENABLE);
}
//init SPI

int fputc(int ch, FILE* stream)
{
    USART_SendData(USART1, (unsigned char) ch);
    while (!(USART1->SR & USART_FLAG_TXE));
    //USART_SendData(USART1, (uint8_t)ch);
    return ch;
}

void gpio_ini()
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&gpio);
	gpio.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&gpio);
	gpio.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&gpio);
}

int main()
{
	
	int a;
	int gate;
	char b,c,d,e,f,g;
	gpio_ini();
	ds18b20_init();
	uart_init();
	printf("hello world");
	while (1)
	{
		delay_us(100000);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		a=(int)(ds18b20_read()*10000);
		//if(a>gate)
			
		
		printf("%d\r\n",a);
		
		g=a%10+'0';
		a/=10;
		f=a%10+'0';
		a/=10;
		e=a%10+'0';
		a/=10;
		d=a%10+'0';
		a/=10;
		c=a%10+'0';
		a/=10;
		b=a%10+'0';

		delay_us(100000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		//printf("temp : %.4f\n",a);
	
	}
}


