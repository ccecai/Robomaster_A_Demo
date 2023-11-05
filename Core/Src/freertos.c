/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId StartDebugHandle;
osThreadId Test_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDebugTask(void const * argument);
void Test_TaskTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of StartDebug */
  osThreadDef(StartDebug, StartDebugTask, osPriorityNormal, 0, 128);
  StartDebugHandle = osThreadCreate(osThread(StartDebug), NULL);

  /* definition and creation of Test_Task */
  osThreadDef(Test_Task, Test_TaskTask, osPriorityNormal, 0, 256);
  Test_TaskHandle = osThreadCreate(osThread(Test_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
    vTaskResume(StartDebugHandle);
    vTaskResume(Test_TaskHandle);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDebugTask */
/**
  * @brief  Function implementing the StartDebug thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDebugTask */
void StartDebugTask(void const * argument)
{
  /* USER CODE BEGIN StartDebugTask */
    Mymain_Init();
  /* Infinite loop */
  for(;;)
  {
      BUZZER_OFF;
      LED1_Flash();
      LED2_Flash();
      WaterLED();

      osDelay(10);
  }
  /* USER CODE END StartDebugTask */
}

/* USER CODE BEGIN Header_Test_TaskTask */
/**
* @brief Function implementing the Test_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Test_TaskTask */
void Test_TaskTask(void const * argument)
{
  /* USER CODE BEGIN Test_TaskTask */
    PID_BASESTR MOTOR3508_P;
    PID_BASESTR MOTOR3508_S;

    int16_t Speed;

    PID_Set(&MOTOR3508_S,3.0f,0.03f,0,10000,0);
    PID_Set(&MOTOR3508_P,0.06f,0.0f,4.2f,0,0);


  /* Infinite loop */
  for(;;)
  {

//      Speed = (int16_t) PID_realise(&MOTOR3508_S,500,motor_info[4].speed,M3508_CURRENT_MAX);
      Speed = (int16_t) PID_realise(&MOTOR3508_P,8200,motor_info[4].total_angle,M3508_CURRENT_MAX);

      set_current(&hcan2,0x1FF,Speed,0,0,0);
//      usart_printf("%d,%d\r\n",motor_info[4].total_angle,Speed);

      osDelay(1);
  }
  /* USER CODE END Test_TaskTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
