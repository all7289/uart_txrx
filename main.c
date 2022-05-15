#include "main.h"
#include "stm32f0xx.h"
#include <stdint.h>


#define GPIOAEN 0x20000
#define UARTEN 0x20000

#define SYS_FREQ 8000000
#define APB1_CLK SYS_FREQ // vi chua cau hinh cay toc do truyen

#define UART_BAUDRATE 9600

void uart2_rxtx_init(void);

static uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t Baudrate);

static uint16_t compete_uart_bd(uint32_t PeriphClk,uint32_t Baudrate);

void uart2_write(int ch);
char uart2_read(void);
void delayMs(int delay);

char key;

int main(void)
{
	uart2_rxtx_init();

  while (1)
  {
	  key= uart2_read();
	  	  if (key == 'a')
	  	  {
	  		  GPIOB->BSRR |=0x8;//led on
	  		  	  delayMs(1000);
	  	  }
	  	  else
	  	  {
	  		  GPIOB->BSRR |=0x80000;//led off
	  		  	  delayMs(1000);
	  	  }
  }
}

void uart2_rxtx_init(void)
{
/***************Configre pin ***************/
	RCC->AHBENR |= GPIOAEN;//enable clock to access GPIOA
	GPIOA->MODER |= 0x20;// enable moder alternate function at PA2
	GPIOA->AFR[0] |= 0x100;// set type AF1 pin PA2//AFR[0]=AFRL******AFR[1]=AFRH

/***************Configre module uart ***************/
	RCC->APB1ENR |= UARTEN;//enable clock access to uart2
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);//configure baudrate
	USART2->CR1 |= 0x8;//configure transfer direcction
	/***************Configre pin Rx ***************/

		GPIOA->MODER |= 0x80;// enable moder alternate function at PA3
		GPIOA->AFR[0] |= 0x1000;// set type AF1 pin PA2//AFR[0]=AFRL******AFR[1]=AFRH

	/***************Configre module uart Rx ***************/

		USART2->CR1 |= 0x4;//configure transfer direcction
		USART2->CR1 |=0x1;//enable mode uart

}

static uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t Baudrate)
{
	USARTx->BRR = compete_uart_bd(PeriphClk,Baudrate);
}

static uint16_t compete_uart_bd(uint32_t PeriphClk,uint32_t Baudrate)
{
	return ((PeriphClk+(Baudrate/2U))/Baudrate);
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3195; i++) ;
}

void uart2_write(int ch)
{
	while(!(USART2->ISR & 0x80))
	{
		delayMs(100);
	}
	USART2->TDR = (ch & 0xFF);
}

char uart2_read(void)
{
	while(!(USART2->ISR & 0x20))
	{
	}
	return USART2->RDR;
}

