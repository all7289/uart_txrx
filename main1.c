
#include "main.h"

uint8_t Rx_Buff[20]; 					   // Buffer luu chuoi nhan duoc
uint8_t Rx_Data;             				// Luu byte nhan duoc
uint8_t Tx_Buff[20] = "Hello Vietnam";    // Buffer truyen di
uint8_t _rxIndex;                         // Con tro cua Rx_Buff
uint16_t Tx_Flag =0;                      // Co bao nhan thanh cong
uint16_t tmp;                      		// Co bao nhan thanh cong

UART_HandleTypeDef huart2;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void dot(void);
void dash(void);
void SoundLetter(char text);

/* Private user code ---------------------------------------------------------*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2 )
	{
		if(Rx_Data !=6 )
			{
				Rx_Buff[_rxIndex++] = Rx_Data;  // Them du lieu vao Buffer
			}
			else if(Rx_Data ==6)
			{
				_rxIndex = 0;              // Xoa con tro
				Tx_Flag =1;                // Bat co
			}
		HAL_UART_Receive_IT(&huart2, &Rx_Data, 1);
	}

}

int main(void)
{

  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
  while (1)
  {
	  HAL_UART_Receive_IT(&huart2, &Rx_Data,1);

	  HAL_Delay(1000);

	  for( int i =0; i< 20; i++)
	  {
	  	SoundLetter(Rx_Buff[i]);
	  	Rx_Buff[i]=0;
	  }
  }
}

void dot(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
}

void dash(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 0);
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, 1);
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
      HAL_Delay(400);
      return;
  }
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

