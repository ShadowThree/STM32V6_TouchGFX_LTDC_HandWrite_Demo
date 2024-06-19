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
#include "atk_ncr.h"
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
volatile uint8_t recognize_finish;
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
/* Definitions for drawLine */
osThreadId_t drawLineHandle;
const osThreadAttr_t drawLine_attributes = {
  .name = "drawLine",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for semGetPoint */
osSemaphoreId_t semGetPointHandle;
const osSemaphoreAttr_t semGetPoint_attributes = {
  .name = "semGetPoint"
};
/* Definitions for eventProcess */
osEventFlagsId_t eventProcessHandle;
const osEventFlagsAttr_t eventProcess_attributes = {
  .name = "eventProcess"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void LTDC_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t width);
/* USER CODE END FunctionPrototypes */

void TouchGFX_Task(void *argument);
void cmd_process_Task(void *argument);
void drawLineTask(void *argument);

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

  /* Create the semaphores(s) */
  /* creation of semGetPoint */
  semGetPointHandle = osSemaphoreNew(1, 0, &semGetPoint_attributes);

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

  /* creation of drawLine */
  drawLineHandle = osThreadNew(drawLineTask, NULL, &drawLine_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of eventProcess */
  eventProcessHandle = osEventFlagsNew(&eventProcess_attributes);

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
	gt911_sta = gt911_init();
	if(GT911_STA_OK != gt911_sta) {
		LOG_ERR("GT911 init err[%d]\n", gt911_sta);
	} else {
		LOG_DBG("GT911 init OK\n");
	}
	
	alientek_ncr_init();
  /* Infinite loop */
	uint32_t evt_id;
  for(;;)
  {
    evt_id = osEventFlagsWait(eventProcessHandle, EVT_ALL, osFlagsWaitAny, osWaitForever);
		if(evt_id & EVT_RECOGNIZE) {
			/* LOG_DBG("recognize...\n");
			for(uint16_t i = 0; i < point_num; i+=2) {
				LOG_DBG("P(%d,%d) P(%d,%d)\n", draw_coor[i].x, draw_coor[i].y, draw_coor[i+1].x, draw_coor[i+1].y);
				osDelay(2);
			} */
			alientek_ncr(draw_coor, point_num, CHAR_NUM/2, RECOGNIZE_123, result);
			alientek_ncr(draw_coor, point_num, CHAR_NUM/2, RECOGNIZE_ABC, &result[3]);
			recognize_finish = 1;
			LOG_DBG("point_num[%d] result: %s\n", point_num, result);
		}
  }
  /* USER CODE END cmd_process_Task */
}

/* USER CODE BEGIN Header_drawLineTask */
/**
* @brief Function implementing the drawLine thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_drawLineTask */
__weak void drawLineTask(void *argument)
{
  /* USER CODE BEGIN drawLineTask */
	osDelay(100);	// waiting GT911 init
	osSemaphoreRelease(semGetPointHandle);
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreAcquire(semGetPointHandle, osWaitForever);
		gt911_get_touch(touch_coordinate, &num_touched);
		if(num_touched == 0) {
			osDelay(5);
			osSemaphoreRelease(semGetPointHandle);
		} else {
			
			if(touch_coordinate[0].x > LTDC_L1_START_X && touch_coordinate[0].x < LTDC_L1_START_X + LTDC_L1_WIDTH &&
				 touch_coordinate[0].y > LTDC_L1_START_Y && touch_coordinate[0].y < LTDC_L1_START_Y + LTDC_L1_HEIGHT)
			{			
				static COORDINATE_t last_point = {.x = 0, .y = 0};
				static uint32_t last_point_tick = 0;
				if(last_point.x == touch_coordinate[0].x && last_point.y == touch_coordinate[0].y) {
					last_point_tick = HAL_GetTick();
				} else {
					#if 0		// coordinate turn 90 dgr test
					int16_t temp = touch_coordinate[0].x;
					touch_coordinate[0].x = (touch_coordinate[0].y - 240) + 350;
					touch_coordinate[0].y = (350 - temp + 240);
					#endif
					
					uint32_t now = HAL_GetTick();
					if(now - last_point_tick > 50) {
						last_point.x = touch_coordinate[0].x;
						last_point.y = touch_coordinate[0].y;
					} else {
						// draw line
						#define LINE_WIDTH	2
						//LOG_DBG("(%d, %d) --> (%d, %d)\n", last_point.x, last_point.y, touch_coordinate[0].x, touch_coordinate[0].y);
						if(last_point.x < LTDC_L1_START_X + LINE_WIDTH) {
							last_point.x = LTDC_L1_START_X + LINE_WIDTH;
						}
						if(last_point.x > LTDC_L1_START_X + LTDC_L1_WIDTH - LINE_WIDTH) {
							last_point.x = LTDC_L1_START_X + LTDC_L1_WIDTH - LINE_WIDTH;
						}
						if(last_point.y < LTDC_L1_START_Y + LINE_WIDTH) {
							last_point.y = LTDC_L1_START_Y + LINE_WIDTH;
						}
						if(last_point.y > LTDC_L1_START_Y + LTDC_L1_HEIGHT - LINE_WIDTH) {
							last_point.y = LTDC_L1_START_Y + LTDC_L1_HEIGHT - LINE_WIDTH;
						}
						if(touch_coordinate[0].x < LTDC_L1_START_X + LINE_WIDTH) {
							touch_coordinate[0].x = LTDC_L1_START_X + LINE_WIDTH;
						}
						if(touch_coordinate[0].x > LTDC_L1_START_X + LTDC_L1_WIDTH - LINE_WIDTH) {
							touch_coordinate[0].x = LTDC_L1_START_X + LTDC_L1_WIDTH - LINE_WIDTH;
						}
						if(touch_coordinate[0].y < LTDC_L1_START_Y + LINE_WIDTH) {
							touch_coordinate[0].y = LTDC_L1_START_Y + LINE_WIDTH;
						}
						if(touch_coordinate[0].y > LTDC_L1_START_Y + LTDC_L1_HEIGHT - LINE_WIDTH) {
							touch_coordinate[0].y = LTDC_L1_START_Y + LTDC_L1_HEIGHT - LINE_WIDTH;
						}
						LTDC_draw_line(last_point.x, last_point.y, touch_coordinate[0].x, touch_coordinate[0].y, LINE_WIDTH);
						last_point.x = touch_coordinate[0].x;
						last_point.y = touch_coordinate[0].y;
						if(point_num > MAX_POINT - 20) {
							LOG_WAR("MAX_POINT[%d] too small\n", MAX_POINT);
						}
					}
					last_point_tick = now;
				}
				osSemaphoreRelease(semGetPointHandle);
			}
			
		}
  }
  /* USER CODE END drawLineTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

