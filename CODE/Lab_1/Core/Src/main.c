/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE BEGIN PV */
int cforR;
int cforY;
int cforG;
int Ex1Counter = 2;
int RED_STATE = 1;
int YELLOW_STATE = 0;
int GREEN_STATE = 0;
int S1state = 1, S2state = 0, S3state = 0, S4state = 0;
int cforS1, cforS2, cforS3, cforS4;
int cforRed = 0;
int count;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void Switch_State();
void display7SEG(int count);
void Traffic_Light_1way(int REDCOUNTER, int YELLOWCOUNTER, int GREENCOUNTER);
void Traffic_Light_4way(int S1COUNTER, int S2COUNTER, int S3COUNTER, int S4COUNTER);
void Analog_Clock();
void clearAllClock();
void setNumberOnClock(int num);
void clearNumberOnClock(int num);
void displayClock(int hour, int minute, int second);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void displayClock(int hour, int minute, int second){
	clearAllClock();
	int a = hour % 12;
	int b = (minute/5) % 12;
	int c = (second/5) % 12;
	setNumberOnClock(a);
	setNumberOnClock(b);
	setNumberOnClock(c);
}
void setNumberOnClock(int num){
	if(num < 0 || num > 11){
		return;
	}
	GPIOB->ODR |= (1<<num);
}
void clearNumberOnClock(int num){
	if(num < 0 || num > 11){
		return;
	}
	GPIOB->ODR &= ~(1<<num);
}
void clearAllClock(){
	  HAL_GPIO_WritePin(s0_GPIO_Port, s0_Pin, RESET);
	  HAL_GPIO_WritePin(s1_GPIO_Port, s1_Pin, RESET);
	  HAL_GPIO_WritePin(s2_GPIO_Port, s2_Pin, RESET);
	  HAL_GPIO_WritePin(s3_GPIO_Port, s3_Pin, RESET);
	  HAL_GPIO_WritePin(s4_GPIO_Port, s4_Pin, RESET);
	  HAL_GPIO_WritePin(s5_GPIO_Port, s5_Pin, RESET);
	  HAL_GPIO_WritePin(s6_GPIO_Port, s6_Pin, RESET);
	  HAL_GPIO_WritePin(s7_GPIO_Port, s7_Pin, RESET);
	  HAL_GPIO_WritePin(s8_GPIO_Port, s8_Pin, RESET);
	  HAL_GPIO_WritePin(s9_GPIO_Port, s9_Pin, RESET);
	  HAL_GPIO_WritePin(s10_GPIO_Port, s10_Pin, RESET);
	  HAL_GPIO_WritePin(s11_GPIO_Port, s11_Pin, RESET);
}
void Switch_State(){
	//Convention: Red: p0 | Yellow: p1
	if(Ex1Counter <= 0){
		if(RED_STATE == 1){
		HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, SET);
		HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, RESET);
		}
		else if(YELLOW_STATE == 1){
		HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, RESET);
		HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, SET);
		}
	//Change State
		RED_STATE = !RED_STATE;
		YELLOW_STATE = !YELLOW_STATE;
	//Update Counter
		Ex1Counter = 2;
	}
	//Decrease Counter
	Ex1Counter--;
	HAL_Delay(1000);
}
void Analog_Clock(){
	  // Lam` sang den tai vi tri count
	  GPIOB->ODR = (1 << count);
	  // update count
	  count = (count + 1) % 12;
	  HAL_Delay(1000);
}
void display7SEG(int count){
	switch(count){
		case 0:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, RESET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, RESET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, SET);
	  		  break;
	  	case 1:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, SET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, SET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, SET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, SET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, SET);
	  		  break;
	  	case 2:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, SET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, RESET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, SET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
	  		  break;
	  	case 3:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, SET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, SET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
	  		  break;
	  	case 4:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, SET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, SET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, SET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, RESET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
	  		  break;
	  	case 5:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, SET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, SET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, RESET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
	  		  break;
	  	case 6:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, SET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, RESET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, RESET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
	  		  break;
	  	case 7:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, SET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, SET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, SET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, SET);
	  		  break;
	  	case 8:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, RESET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, RESET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
	  		  break;
	  	case 9:
	  		  HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
	  		  HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
	  		  HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
	  		  HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
	  		  HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, SET);
	  		  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, RESET);
	  		  HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
	  		  break;
	  	}
}
void Traffic_Light_1way(int REDCOUNTER, int YELLOWCOUNTER, int GREENCOUNTER){
	//RED: p0, YELLOW: p1, GREEN: p2
	//RED_STATE
	  if(RED_STATE == 1 && cforR > 0){
		  HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, RESET);
		  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, SET);
		  HAL_GPIO_WritePin(p2_GPIO_Port, p2_Pin, SET);
		  cforR--;
	  }
	  else if(cforR == 0){
		  GREEN_STATE = 1;
		  RED_STATE = 0;
		  cforR = REDCOUNTER;
	  }
	  //GREEN_STATE
	  if(GREEN_STATE == 1 && cforG > 0){
	  	  HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, SET);
	      HAL_GPIO_WritePin(p2_GPIO_Port, p2_Pin, RESET);
	  	  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, SET);
	      cforG--;
	  }
	  else if(cforG == 0){
	  	  YELLOW_STATE = 1;
	  	  GREEN_STATE = 0;
	  	  cforG = GREENCOUNTER;
	  }
	  //YELLOW_STATE
	  if(YELLOW_STATE == 1 && cforY > 0){
	  	  HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, SET);
	      HAL_GPIO_WritePin(p2_GPIO_Port, p2_Pin, SET);
	  	  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, RESET);
	      cforY--;
	  }
	  else if(cforY == 0){
	  	  RED_STATE = 1;
	  	  YELLOW_STATE = 0;
	  	  cforY = YELLOWCOUNTER;
	  }
	  HAL_Delay(1000);
}
void Traffic_Light_4way(int S1COUNTER, int S2COUNTER, int S3COUNTER, int S4COUNTER){
	  //State 1: GREEN-RED
	  if(S1state == 1 && cforS1 > 0){
		  //1
		  HAL_GPIO_WritePin(p2_GPIO_Port, p2_Pin, SET);
		  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, RESET);
		  HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, RESET);
		  //2
		  HAL_GPIO_WritePin(p3_GPIO_Port, p3_Pin, SET);
		  HAL_GPIO_WritePin(p5_GPIO_Port, p5_Pin, RESET);
		  HAL_GPIO_WritePin(p4_GPIO_Port, p4_Pin, RESET);
		  cforS1--;
		  display7SEG(cforS1);
	  }
	  else if(cforS1 == 0){
		  S1state = 0;
		  S2state = 1;
		  cforS1 = S1COUNTER;
		  display7SEG(0);
	  }
	  //State 2: YELLOW-RED
	  if(S2state == 1 && cforS2 > 0){
		  //1
		  HAL_GPIO_WritePin(p2_GPIO_Port, p2_Pin, RESET);
		  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, SET);
		  HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, RESET);
		  //2
		  HAL_GPIO_WritePin(p3_GPIO_Port, p3_Pin, SET);
		  HAL_GPIO_WritePin(p5_GPIO_Port, p5_Pin, RESET);
		  HAL_GPIO_WritePin(p4_GPIO_Port, p4_Pin, RESET);
		  cforS2--;
		  display7SEG(cforS2);
	  }
	  else if(cforS2 == 0){
		  S2state = 0;
		  S3state = 1;
		  cforS2 = S2COUNTER;
		  display7SEG(0);
		  cforRed = cforS3 + cforS4;
	  }
	  //State 3: RED-GREEN
	  if(S3state == 1 && cforS3 > 0){
		  //1
		  HAL_GPIO_WritePin(p2_GPIO_Port, p2_Pin, RESET);
		  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, RESET);
		  HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, SET);
		  //2
		  HAL_GPIO_WritePin(p3_GPIO_Port, p3_Pin, RESET);
		  HAL_GPIO_WritePin(p5_GPIO_Port, p5_Pin, SET);
		  HAL_GPIO_WritePin(p4_GPIO_Port, p4_Pin, RESET);
		  cforS3--;
		  cforRed--;
		  display7SEG(cforRed);
	  }
	  else if(cforS3 == 0){
		  S3state = 0;
		  S4state = 1;
		  cforS3 = S3COUNTER;
		  display7SEG(0);
	  }
	  //State 4: RED-YELLOW
	  if(S4state == 1 && cforS4 != 0){
		  //1
		  HAL_GPIO_WritePin(p2_GPIO_Port, p2_Pin, RESET);
		  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, RESET);
		  HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, SET);
		  //2
		  HAL_GPIO_WritePin(p3_GPIO_Port, p3_Pin, RESET);
		  HAL_GPIO_WritePin(p5_GPIO_Port, p5_Pin, RESET);
		  HAL_GPIO_WritePin(p4_GPIO_Port, p4_Pin, SET);
		  cforS4--;
		  cforRed--;
		  display7SEG(cforRed);
	  }
	  else if(cforS4 == 0){
		  S4state = 0;
		  S1state = 1;
		  cforS4 = S4COUNTER;
		  return;
	  }
	  HAL_Delay(1000);
}
/* USER CODE END 0 */

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
  /* USER CODE BEGIN 2 */

  //Default State for Ex1:
  /*HAL_GPIO_WritePin(p0_GPIO_Port, p0_Pin, RESET);
  HAL_GPIO_WritePin(p1_GPIO_Port, p1_Pin, SET);*/

  //Default Counter for Ex2:
  /*cforR = 5;
  cforY = 2;
  cforG = 3;*/

  //Display Led: 9 8 7 ....
  //int cfor7segment = 9;

  //Default Counter for Ex3, 4, 5:
  /*cforS1 = 3;
  cforS2 = 2;
  cforS3 = 3;
  cforS4 = 2;*/

  //Count for Ex6:
  count = 0;

  //Clearcount for Ex7:
  //int c1 = 3;

  //Example for Ex10:
  /*int hour = 6;
  int minute = 54;
  int second = 55;*/

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //Ex1:
	  //Switch_State();

	  //Ex2:
	  //Traffic_Light_1way(5, 2, 3);

	  //Ex4:
	  /*display7SEG(cfor7segment);
	  cfor7segment--;
	  if(cfor7segment < 0){
		  cfor7segment = 9;
	  }
	  HAL_Delay(1000);*/

	  //Ex3, 4, 5:
	  //Traffic_Light_4way(3, 2, 3, 2);

	  //Ex6:
	  Analog_Clock();

	  //Ex7:
	  /*c1--;
	  if(c1 >= 0){
		  setNumberOnClock(1);
		  setNumberOnClock(3);
		  setNumberOnClock(5);
		  setNumberOnClock(7);
		  setNumberOnClock(9);
		  setNumberOnClock(11);
	  } else clearAllClock();
	  HAL_Delay(1000);*/

	  //Ex10
	  /*displayClock(hour, minute, second);
	  HAL_Delay(1000);
	  second++;
	  if(second == 60){
		  second = 0;
		  minute++;
	  }
	  if(minute == 60){
		  minute = 0;
		  hour++;
	  }
	  if(hour == 24){
		  hour = 0;
	  }*/
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
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, p0_Pin|p1_Pin|p2_Pin|p3_Pin
                          |p4_Pin|p5_Pin|a_Pin|b_Pin
                          |c_Pin|d_Pin|e_Pin|f_Pin
                          |g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, s0_Pin|s1_Pin|s2_Pin|s10_Pin
                          |s11_Pin|s3_Pin|s4_Pin|s5_Pin
                          |s6_Pin|s7_Pin|s8_Pin|s9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : p0_Pin p1_Pin p2_Pin p3_Pin
                           p4_Pin p5_Pin a_Pin b_Pin
                           c_Pin d_Pin e_Pin f_Pin
                           g_Pin */
  GPIO_InitStruct.Pin = p0_Pin|p1_Pin|p2_Pin|p3_Pin
                          |p4_Pin|p5_Pin|a_Pin|b_Pin
                          |c_Pin|d_Pin|e_Pin|f_Pin
                          |g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : s0_Pin s1_Pin s2_Pin s10_Pin
                           s11_Pin s3_Pin s4_Pin s5_Pin
                           s6_Pin s7_Pin s8_Pin s9_Pin */
  GPIO_InitStruct.Pin = s0_Pin|s1_Pin|s2_Pin|s10_Pin
                          |s11_Pin|s3_Pin|s4_Pin|s5_Pin
                          |s6_Pin|s7_Pin|s8_Pin|s9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
