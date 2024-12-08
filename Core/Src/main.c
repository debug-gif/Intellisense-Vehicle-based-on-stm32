/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"Motor.h"
#include"stm32f1xx_hal.h"

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1  | TIM_CHANNEL_2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    int sensor[5] = {0};
    /**从左向右依次存储五个探头传来的数据，如果测试的时候电机的转速不好可视化，
     * 可以尝试用vofa看看数组值，看看两边输出的pwm波，当然这个程序要你自己写。
     * 注意，单片机这里控制台上不会直接打印值，所以你要用usart，这个printf函数已经重定向过了，可以直接在vofa当中打印出你想要的值，
     * 比如printf("%d", sensor[0]);就可以打印出sensor[0]的值。
     * 但是，如果是自己的空程序，就要自己在usart.c里面重定向printf函数，具体方法可以百度，这里就不赘述了，建议跳转定义去看一下。
     * */
    uint8_t counter = 0;
    while (1)
    {
      /**MotorLSetPWM(800);
       * MotorRSetPWM(800);
       * 上面这两个是测试例程，可以将下面的所有if注释掉以后，取消上面的注释，测试电机是否正常工作
       * 硬件问题一定要注意，指不定什么时候杀个回马枪
       * */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //黑线是0, 白线是1
    //黑线到底是1还是0
    //黑线真的是0
        sensor[0] = HAL_GPIO_ReadPin(SENSOR_1_GPIO_Port, SENSOR_1_Pin);
        sensor[1] = HAL_GPIO_ReadPin(SENSOR_2_GPIO_Port, SENSOR_2_Pin);
        sensor[2] = HAL_GPIO_ReadPin(SENSOR_3_GPIO_Port, SENSOR_3_Pin);
        sensor[3] = HAL_GPIO_ReadPin(SENSOR_4_GPIO_Port, SENSOR_4_Pin);
        sensor[4] = HAL_GPIO_ReadPin(SENSOR_5_GPIO_Port, SENSOR_5_Pin);
        
        if(sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 0 && sensor[0] == 0){//起点全黑
            counter++;
            if(counter == 1){//发车
                MotorLSetPWM(300);
                MotorRSetPWM(300);
            }else if(counter == 2){//十字路口一
              MotorLSetPWM(500);
              MotorRSetPWM(500);
            }else if(counter == 3){//十字路口二
              MotorLSetPWM(500);
              MotorRSetPWM(500);
            }else{//终点
              MotorLSetPWM(0);
              MotorRSetPWM(0);
            }
        }
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 1){//直行
            MotorLSetPWM(500);
            MotorRSetPWM(500);
        }//11011

		    if(sensor[0] == 1 && sensor[1] == 0 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 1){//左
            MotorLSetPWM(100);
            MotorRSetPWM(500);
				
        }//10111
        if(sensor[0] == 1 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 1){//左,苯环
            MotorLSetPWM(50);
            MotorRSetPWM(800);  
       
        }//10011
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 1){//右
            MotorLSetPWM(500);
            MotorRSetPWM(100);
         
        }//11101
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 1){//右
            MotorLSetPWM(500);
            MotorRSetPWM(100);
        }//11001
        if(sensor[0] == 0 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 1){//极左
            MotorLSetPWM(10);
            MotorRSetPWM(500);
  
        }//01111
        if(sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 1){//极左
            MotorLSetPWM(10);
            MotorRSetPWM(500);
				
        }//00111
        if(sensor[0] == 0 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 1){//极左，苯环
            MotorLSetPWM(15);
            MotorRSetPWM(600);
           
        }//01011
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 0){//极右
            MotorLSetPWM(500);
            MotorRSetPWM(10);
          
        }//11010
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 0){//极右
            MotorLSetPWM(300);
            MotorRSetPWM(500);
           
        }//11000
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 0){//极右
            MotorLSetPWM(500);
            MotorRSetPWM(10);
           
        }//11110
        if(sensor[0] == 1 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 1){//三岔路口
            MotorLSetPWM(650);
            MotorRSetPWM(100);
        
        }//10001
        if(sensor[0] == 1 && sensor[1] == 0 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 1){//三岔路口
            MotorLSetPWM(650);
            MotorRSetPWM(100);
          
        }//10101
        if(sensor[0] == 0 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 0){//三岔路口
            MotorLSetPWM(600);
            MotorRSetPWM(40);
   
        }//01110
        if(sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 1){//左直角弯
            MotorLSetPWM(50);
            MotorRSetPWM(600);
        
        }//00111
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 0){//右直角弯
            MotorLSetPWM(500);
            MotorRSetPWM(50);
        
        }//11100
        if(sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 1){//左直角弯
            MotorLSetPWM(30);
            MotorRSetPWM(500);
          
        }//00011
        if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 0){//右直角弯
            MotorLSetPWM(500);
            MotorRSetPWM(50);
         
        }//11000
        if(sensor[0] == 0 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 1){//苯环锐角弯
            MotorLSetPWM(40);
            MotorRSetPWM(700);
          
        }//01101
        if(sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 1){//左直角弯,大
            MotorLSetPWM(-100);
            MotorRSetPWM(500);
        }//00001
        if(sensor[0] == 1 && sensor[1] == 0 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 0){//苯环锐角弯
            MotorLSetPWM(40);
            MotorRSetPWM(700);
        }//10110
        HAL_Delay(10);
    }
}
  /* USER CODE END 3 */

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
