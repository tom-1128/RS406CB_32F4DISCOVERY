/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

unsigned char moji[]="0123456789abcdef";
unsigned char data2char(unsigned char c){
	return moji[c];
}

	unsigned char data[2];
	unsigned char* data2chars(unsigned char c){

	data[0] = data2char((c & 0xf0)>>4);
	data[1] = data2char((c & 0x0f));
	return data;
}




/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  char buf[] =  "A\n\r";
   HAL_UART_Transmit(&huart2, (uint8_t *)buf, sizeof(buf), 0xFFFF);


   unsigned char sendbuf_05[12] = {0};
   sendbuf_05[0]  = (unsigned char)0xFA;
   sendbuf_05[1]  = (unsigned char)0xAF;
   sendbuf_05[2]  = (unsigned char)0x03;//03
   sendbuf_05[3]  = (unsigned char)0x00;//00
   sendbuf_05[4]  = (unsigned char)0x1E;//1E
   sendbuf_05[5]  = (unsigned char)0x04;//04
   sendbuf_05[6]  = (unsigned char)0x01;//01
   sendbuf_05[7]  = (unsigned char)0x32;//32(0032-L)
   sendbuf_05[8]  = (unsigned char)0x00;//00(0032-H)
   sendbuf_05[9]  = (unsigned char)0xF4;//F4(01F4-L)
   sendbuf_05[10]  = (unsigned char)0x01;//01(01F4-H)

   unsigned char check_sum = sendbuf_05[2];
   for( int i = 3; i < 10; i++ )
   {
   check_sum = (unsigned char)(check_sum ^ sendbuf_05[i]);
    }
   sendbuf_05[11] = check_sum;

//    unsigned char sendbuf_90[12] = {0};
//    sendbuf_90[0]  = (unsigned char)0xFA;
//    sendbuf_90[1]  = (unsigned char)0xAF;
//    sendbuf_90[2]  = (unsigned char)0x03;//03
//    sendbuf_90[3]  = (unsigned char)0x00;//00
//    sendbuf_90[4]  = (unsigned char)0x1E;//1E
//    sendbuf_90[5]  = (unsigned char)0x04;//04
//    sendbuf_90[6]  = (unsigned char)0x01;//01
//    sendbuf_90[7]  = (unsigned char)0x84;//84(0384-L)
//    sendbuf_90[8]  = (unsigned char)0x03;//03(0384-H)
//    sendbuf_90[9]  = (unsigned char)0xF4;//F4(01F4-L)
//    sendbuf_90[10]  = (unsigned char)0x01;//01(01F4-H)
//
//    check_sum = sendbuf_90[2];
//    for( int i = 3; i < 10; i++ )
//    {
//    check_sum = (unsigned char)(check_sum ^ sendbuf_90[i]);
//     }
//    sendbuf_90[11] = check_sum;

    unsigned char sendbuf_torque[9] = {0};
    sendbuf_torque[0]  = (unsigned char)0xFA;
    sendbuf_torque[1]  = (unsigned char)0xAF;
    sendbuf_torque[2]  = (unsigned char)0x03;//03
    sendbuf_torque[3]  = (unsigned char)0x00;//00
    sendbuf_torque[4]  = (unsigned char)0x24;//1E
    sendbuf_torque[5]  = (unsigned char)0x01;//01
    sendbuf_torque[6]  = (unsigned char)0x01;//01
    sendbuf_torque[7]  = (unsigned char)0x01;//01(torque)


    check_sum = sendbuf_torque[2];
    for( int i = 3; i < 8; i++ )
    {
    check_sum = (unsigned char)(check_sum ^ sendbuf_torque[i]);
     }
    sendbuf_torque[8] = check_sum;
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  unsigned char buf[23]={0};//文字変化用
	  for(int i=0 ; i<=11 ; i++){//文字変化用
//		  unsigned char datas[3];
//		  datas=data2chars(sendbuf[i]);
		  data2chars(sendbuf_05[i]);//文字変化用

		  buf[i*2+0]=data[0];//文字変化用
		  buf[i*2+1]=data[1];//文字変化用
	  }
	  {if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)){ //ボタン状態取得
	 	  HAL_UART_Transmit(&huart2, (uint8_t *)buf, 9*2, 0xFFFF);
	 	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET); //ボタンが押されたらLED消灯
	 	  HAL_Delay(100);
	  }else{HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET); //ボタンが押されてないときLDE点灯
	  	  HAL_Delay(100);
		  }
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PD12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
