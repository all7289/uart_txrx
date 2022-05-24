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

void dot(void);
void dash(void);
void SoundLetter(char text);

char key;
uint8_t status;


int main(void)
{
	// clock
		RCC->AHBENR |= 0x40000;
		//define GPIOB_3
		GPIOB->MODER |=0x40;
		GPIOB->OSPEEDR |=0xC0;
		//GPIOB->PUPDR |=0x40;
		//GPIOB_6
		GPIOB->MODER |=0x1000;
		GPIOB->OSPEEDR |=0x3000;

	uart2_rxtx_init();

	GPIOB->BSRR |=0x40;//status 1 at pinB6
	GPIOB->BSRR |=0x8;//status 1 at pinB3
  while (1)
  {
	 // uart2_write('Q');
	  key= uart2_read();

	  uart2_write(key);
	  SoundLetter(key);

//	  	  if (key == '1')
//	  	  {
////	  		  GPIOB->BSRR |=0x8;//led on
////	  		  	  delayMs(100);
//
//	  		  dot();
//	  		  dot();
//	  	  }
//	  	  else
//	  	  {
////	  		  GPIOB->BSRR |=0x80000;//led off
////	  		  	  delayMs(100);
//	  		  dash();
//	  		  dash();
//	  		SoundLetter(key);
//	  	  }


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

		USART2->CR1 |= 0x4;//configure receiver direcction
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

/**********kur project*********/
void dot(void)
{
	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 0);
	GPIOB->BSRR |=0x400000;
	delayMs(50);
	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 1);
	GPIOB->BSRR |=0x40;
	delayMs(200);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
	//GPIOB->BSRR |=0x8;
}

void dash(void)
{
	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 0);
	GPIOB->BSRR |=0x400000;
	delayMs(200);
	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 1);
	GPIOB->BSRR |=0x40;
	delayMs(200);
	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 1);
	//GPIOB->BSRR |=0x8;
}

void SoundLetter(char text)
{
  switch(text)
  {
    case 'E':
      dot();
      return;
    case 'T':
      dash();
      return;
    case 'A':
      dot();
      dash();
      return;
    case 'O':
      dash();
      dash();
      dash();
      return;
    case 'I':
      dot();
      dot();
      return;
    case 'N':
      dash();
      dot();
      return;
    case 'S':
      dot();
      dot();
      dot();
      return;
    case 'H':
      dot();
      dot();
      dot();
      dot();
      return;
    case 'R':
      dot();
      dash();
      dot();
      return;
    case 'D':
      dash();
      dot();
      dot();
      return;
    case 'L':
      dot();
      dash();
      dot();
      dot();
      return;
    case 'C':
      dash();
      dot();
      dash();
      dot();
      return;
    case 'U':
      dot();
      dot();
      dash();
      return;
    case 'M':
      dash();
      dash();
      return;
    case 'W':
      dot();
      dash();
      dash();
      return;
    case 'F':
      dot();
      dot();
      dash();
      dot();
      return;
    case 'G':
      dash();
      dash();
      dot();
      return;
    case 'Y':
      dash();
      dot();
      dash();
      dash();
      return;
    case 'P':
      dot();
      dash();
      dash();
      dot();
      return;
    case 'B':
      dash();
      dot();
      dot();
      dot();
      return;
    case 'V':
      dot();
      dot();
      dot();
      dash();
      return;
    case 'K':
      dash();
      dot();
      dash();
      return;
    case 'J':
      dot();
      dash();
      dash();
      dash();
      return;
    case 'X':
      dash();
      dot();
      dot();
      dash();
      return;
    case 'Q':
      dash();
      dash();
      dot();
      dash();
      return;
    case 'Z':
      dash();
      dash();
      dot();
      dot();
      return;
    case ' ':
    	delayMs(400);
      return;
  }
}

