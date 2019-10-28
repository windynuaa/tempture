
#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include "ds18b20.h"
#include "keyboard.h"
#include "oled.h"
int delay_time;
//HCLK=72M
//PCLK2=72M
//PCLK1=36M;
//ds18b20 12 bit convert time : 750 ms


/*
PA1 beeper
PA5 SCL
PA7 SDA
PA9 TX
PA10 RX





*/
char str_buffer[20];


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
    return ch;
}

void gpio_ini()
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//led(beeper)
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_Pin=GPIO_Pin_1;
	//usart
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
	char count=0;
	gpio_ini();
	ds18b20_init();
	uart_init();
	printf("hello world");
	OLED_Init();
	OLED_Clear();
	while (1)
	{
		
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		delay_us(250000);
		a=(int)(ds18b20_read()*10000);
		//if(a>gate)
			
		count++;
		if(count>127)
			count=0;
		OLED_draw_line(count,5,a/10000);
		printf("%d\r\n",a);
		OLED_ShowString(32,0,"Tempture",16);
		OLED_ShowNum(0+36,2,a/10000,2,16);
		OLED_ShowChar(16+36,2,'.',16);
		OLED_ShowNum(24+36,2,a%10000,4,16);
		if(a>470000){
			OLED_ShowString(0,7," ! OVER  HEAT ! ",8);
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
		else
			OLED_ShowString(0,7,"                ",8);
		delay_us(250000);
		//printf("temp : %.4f\n",a);
	
	}
}


