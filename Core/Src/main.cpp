/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <Engine.hpp>

#include "engineController.hpp"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TIMCLOCK 80000000
#define PRESCALAR 90

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile uint32_t realSpeed;
IEngineController *motorA;
EngineController motorB{};
volatile int32_t speed = 0;
int int_dec = 1;
uint32_t IC_Val1 = 0;
uint32_t IC_Val2 = 0;
uint32_t Difference = 0;
int Is_First_Captured = 0;
int blockOne = 0;
volatile int second_capture = 0;
volatile uint32_t IC_Val12 = 0;
volatile uint32_t IC_Val22 = 0;
volatile uint32_t Difference2 = 0;
volatile int Is_First_Captured2 = 0;
float frequency = 0;
int32_t rightChannel = 0;
int32_t leftChannel = 0;
int32_t right = 0;
int32_t left = 0;
uint8_t speedMultiplier = 9;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  Engine rightEngine{htim3};
  Engine leftEngine{htim4};
  motorA = new EngineController{htim2, &rightEngine};
  // motorA.setParams(htim2,&rightEngine);
  motorB.setParams(htim5, &leftEngine);

  HAL_TIM_Base_Start_IT(&htim6);
  //  uint32_t time_tick = HAL_GetTick();
  uint32_t max_time = 1000;
  //  int leftSpeedTable[] = {80, 60, -100, -70, 80};
  //  int rightSpeedTable[] = {60, -60,-100, 70 , 80};
  //  int i = 0;

  //  HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);
  //  HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {


    //	  if(speed < 440)
    //	  {
    //		  motorA.setSpeed(right);
    //		  motorB.setSpeed(left);
    //	  }
    //	  else if(speed > 470)
    //	  {
    //		  motorA.setSpeed(-(speed - 460));
    //		  motorB.setSpeed(-(speed - 460));
    //	  }
    //	  if((HAL_GetTick() - time_tick) > max_time)
    //	  {
    //		  time_tick = HAL_GetTick();
    //
    //
    //	  }
    //  TIM16->CCR1 = 500;

    //	  if((HAL_GetTick() - time_tick) > max_time )
    //	  	  	  {
    //
    //	  	         time_tick = HAL_GetTick();
    //
    //	  	  		 speed += int_dec;
    //	  	  		 leftEngine.setSpeed(700);
    //	  	  		 rightEngine.setSpeed(880);
    //
    //	  	  		// motorA.setSpeed(speed);
    //	  	  		// motorB.setSpeed(speed);
    //	  	  		// realSpeed = (speed - 40 ) / 0.7;
    //	  	  		  if(speed >= 1000)
    //	  	  		  {
    //	  	  			  int_dec = -1;
    //	  	  			  max_time = 20;
    //	  	  		  }
    //	  	  		  else if(speed <=400)
    //	  	  		  {
    //	  	  			  int_dec = 1;
    //
    //
    //
    //	  //	  			TIM3->CCR4 = speed;
    //	  //	  			TIM2->CCR4 = speed;
    //	  	  		  }
    //	  	  		  else
    //	  	  		  {
    //	  	  			  max_time = 600;
    //	  	  		  }
    //	  	  	  }
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {
    motorA->calculateSpeed();
    motorB.calculateSpeed();
    //		motor_calculate_speed(&motorA);
    //		motor_calculate_speed(&motorB);
  }
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
  if (htim->Channel ==
      HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
  {
    if (Is_First_Captured == 0)  // if the first value is not captured
    {
      IC_Val1 = HAL_TIM_ReadCapturedValue(
          htim, TIM_CHANNEL_1);  // read the first value
      Is_First_Captured = 1;     // set the first captured as true
    }

    else if (Is_First_Captured == 1)  // if the first is already captured
    {
      IC_Val2 =
          HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value

      if (IC_Val2 > IC_Val1) {
        Difference = IC_Val2 - IC_Val1;
      }

      else if (IC_Val1 > IC_Val2) {
        Difference = (0xffff - IC_Val1) + IC_Val2;
      }

      float refClock = TIMCLOCK / (PRESCALAR);
      float mFactor = 1000000 / refClock;

      rightChannel = Difference * mFactor;
      // rightChannel -= 12000;
      __HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
      Is_First_Captured = 0;           // set it back to false
    }
  }

  if (htim->Channel ==
      HAL_TIM_ACTIVE_CHANNEL_2)  // if the interrupt source is channel1
  {
    if (Is_First_Captured == 0)  // if the first value is not captured
    {
      IC_Val12 = HAL_TIM_ReadCapturedValue(
          htim, TIM_CHANNEL_2);  // read the first value
      Is_First_Captured = 3;     // set the first captured as true
    }

    else if (Is_First_Captured == 1)  // if the first is already captured
    {
      IC_Val22 =
          HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);  // read second value

      if (IC_Val22 > IC_Val12) {
        Difference2 = IC_Val22 - IC_Val12;
      }

      else if (IC_Val12 > IC_Val22) {
        Difference2 = (0xffff - IC_Val12) + IC_Val22;
      }

      float refClock = TIMCLOCK / (PRESCALAR);
      float mFactor = 1000000 / refClock;

      leftChannel = Difference2 * mFactor;
      // leftChannel -= 12000;
      __HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
      Is_First_Captured = 0;           // set it back to false
    }
  }
}
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
  while (1) {
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
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
