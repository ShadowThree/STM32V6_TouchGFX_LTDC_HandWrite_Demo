/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dbger.h"
#include "gt911.h"
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
/* Definitions for TouchGFX */
osThreadId_t TouchGFXHandle;
const osThreadAttr_t TouchGFX_attributes = {
  .name = "TouchGFX",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for cmd_process */
osThreadId_t cmd_processHandle;
const osThreadAttr_t cmd_process_attributes = {
  .name = "cmd_process",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TouchGFX_Task(void *argument);
void cmd_process_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of TouchGFX */
  TouchGFXHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFX_attributes);

  /* creation of cmd_process */
  cmd_processHandle = osThreadNew(cmd_process_Task, NULL, &cmd_process_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_TouchGFX_Task */
/**
  * @brief  Function implementing the TouchGFX thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TouchGFX_Task */
__weak void TouchGFX_Task(void *argument)
{
  /* USER CODE BEGIN TouchGFX_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END TouchGFX_Task */
}

/* USER CODE BEGIN Header_cmd_process_Task */
/**
* @brief Function implementing the cmd_process thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_cmd_process_Task */
__weak void cmd_process_Task(void *argument)
{
  /* USER CODE BEGIN cmd_process_Task */
	GT911_STA_t gt911_sta = GT911_STA_OK;
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);		// delete it if GT911 is NOT work in interrupt mode;
	gt911_sta = gt911_init();
	if(GT911_STA_OK != gt911_sta) {
		LOG_ERR("GT911 init err[%d]\n", gt911_sta);
	} else {
		LOG_DBG("GT911 init OK\n");
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);		// delete it if GT911 is NOT work in interrupt mode;
	}
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END cmd_process_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

