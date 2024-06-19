/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define EVT_RECOGNIZE		1
#define EVT_DRAW_LINE		2
#define EVT_ALL					(EVT_RECOGNIZE | EVT_DRAW_LINE)
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LTDC_L0_ADDR 0xC0000000
#define LTDC_L0_WIDTH 800
#define LTDC_L0_HEIGHT 480
#define LTDC_L1_ADDR (LTDC_L0_ADDR + LTDC_L0_WIDTH * LTDC_L0_HEIGHT * 2 * 2)
#define LTDC_L1_WIDTH 300
#define LTDC_L1_HEIGHT 300
#define LTDC_L1_START_X 200
#define LTDC_L1_START_Y 90
#define LCD_BL_Pin GPIO_PIN_0
#define LCD_BL_GPIO_Port GPIOA
#define TP_INT_Pin GPIO_PIN_7
#define TP_INT_GPIO_Port GPIOH
#define TP_SCL_Pin GPIO_PIN_6
#define TP_SCL_GPIO_Port GPIOB
#define TP_SDA_Pin GPIO_PIN_9
#define TP_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
