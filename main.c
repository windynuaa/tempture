
#include "stm32f10x.h"                  // Device header
int delay_time;
//HCLK=72M
//PCLK2=72M
//PCLK1=36M;
//ds18b20 12 bit convert time : 750 ms
void delay_us(int a)
{
	SysTick_Config(72*a);
	while(~(SysTick->CTRL&1<<16));
	SysTick->CTRL=0x00;
  SysTick->VAL =0X00;
}

void delay_ms(int a)
{
	SysTick_Config(72000*a);
	while(~(SysTick->CTRL&1<<16));
	SysTick->CTRL=0x00;
  SysTick->VAL =0X00;
}
//init usart
void uart_init()
{
	USART_InitTypeDef uart;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_StructInit(&uart);
	uart.USART_BaudRate=115200;
	USART_Init(USART1,&uart);
	USART_Cmd(USART1,ENABLE);
}
//init SPI
void spi_init()
{
	SPI_InitTypeDef spi;
	SPI_StructInit(&spi);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	SPI_Init(SPI1,&spi);
	SPI_Cmd(SPI1,ENABLE);
}

void ssi_write()
{
	SPI_I2S_SendData(SPI1,0x00);

}

int main()
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&gpio);
	while (1)
	{
		delay_ms(500);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		delay_ms(500);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
	}
}


