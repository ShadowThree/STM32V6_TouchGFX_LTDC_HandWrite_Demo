/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
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
#include "ltdc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 5;
  hltdc.Init.VerticalSync = 5;
  hltdc.Init.AccumulatedHBP = 51;
  hltdc.Init.AccumulatedVBP = 28;
  hltdc.Init.AccumulatedActiveW = 851;
  hltdc.Init.AccumulatedActiveH = 508;
  hltdc.Init.TotalWidth = 1061;
  hltdc.Init.TotalHeigh = 530;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = LTDC_L0_WIDTH;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = LTDC_L0_HEIGHT;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = LTDC_L0_ADDR;
  pLayerCfg.ImageWidth = LTDC_L0_WIDTH;
  pLayerCfg.ImageHeight = LTDC_L0_HEIGHT;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = LTDC_L1_START_X;
  pLayerCfg1.WindowX1 = (LTDC_L1_START_X + LTDC_L1_WIDTH);
  pLayerCfg1.WindowY0 = LTDC_L1_START_Y;
  pLayerCfg1.WindowY1 = (LTDC_L1_START_Y + LTDC_L1_HEIGHT);
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg1.Alpha = 255;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg1.FBStartAdress = LTDC_L1_ADDR;
  pLayerCfg1.ImageWidth = LTDC_L1_WIDTH;
  pLayerCfg1.ImageHeight = LTDC_L1_HEIGHT;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 68;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOK_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PI12     ------> LTDC_HSYNC
    PI13     ------> LTDC_VSYNC
    PI14     ------> LTDC_CLK
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    PJ4     ------> LTDC_R5
    PJ5     ------> LTDC_R6
    PJ6     ------> LTDC_R7
    PJ9     ------> LTDC_G2
    PJ10     ------> LTDC_G3
    PJ11     ------> LTDC_G4
    PK0     ------> LTDC_G5
    PK1     ------> LTDC_G6
    PK2     ------> LTDC_G7
    PJ15     ------> LTDC_B3
    PK3     ------> LTDC_B4
    PK4     ------> LTDC_B5
    PK5     ------> LTDC_B6
    PK6     ------> LTDC_B7
    PK7     ------> LTDC_DE
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 13, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PI12     ------> LTDC_HSYNC
    PI13     ------> LTDC_VSYNC
    PI14     ------> LTDC_CLK
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    PJ4     ------> LTDC_R5
    PJ5     ------> LTDC_R6
    PJ6     ------> LTDC_R7
    PJ9     ------> LTDC_G2
    PJ10     ------> LTDC_G3
    PJ11     ------> LTDC_G4
    PK0     ------> LTDC_G5
    PK1     ------> LTDC_G6
    PK2     ------> LTDC_G7
    PJ15     ------> LTDC_B3
    PK3     ------> LTDC_B4
    PK4     ------> LTDC_B5
    PK5     ------> LTDC_B6
    PK6     ------> LTDC_B7
    PK7     ------> LTDC_DE
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14);

    HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOK, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
#include <stdlib.h>
#include "atk_ncr.h"

#define LTDC_DBG_EN	0
#if LTDC_DBG_EN
#include "dbger.h"
#define LTDC_DBG(fmt, ...)	LOG_DBG(fmt, ##__VA_ARGS__)
#else
#define LTDC_DBG(fmt, ...)
#endif
void LTDC_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t width)
{
	#define RECOGNIZE_TURN_CLOCKWISE			0		// clockwise the coordinate 90 dgr for recognizing				// (x,y) --> (y,-x)
	#define RECOGNIZE_TURN_ANTICLOCKWISE	1		// anti-clockwise the coordinate 90 dgr for recognizing		// (x,y) --> (-y,x)
	#define DELAY_TIME	20
	//#define DRAW_LINE_DELAY(ms)		osDelay(ms)
	#define DRAW_LINE_DELAY(ms)
	uint32_t addr;
	int16_t val;
	if(abs(x1-x2) > abs(y1-y2)) {
		val = (int16_t)(100.0f * abs(y2-y1) / abs(x2-x1));
		if(x1 < x2) {
			if(y1 < y2) {		// abs(x1-x2) > abs(y1-y2)		// x1 < x2		// y1 < y2
				for(int16_t i = x1; i <= x2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = y1+val*(i-x1)/100;
						draw_coor[point_num++].y = -i;
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -(y1+val*(i-x1)/100);
						draw_coor[point_num++].y = i;
						#else
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1+val*(i-x1)/100;
						#endif
						
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1+val*(i-x1)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1+val*(i-x1)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) > abs(y1-y2)		// x1 < x2		// y1 >= y2
				for(int16_t i = x1; i <= x2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = y1-val*(i-x1)/100;
						draw_coor[point_num++].y = -i;
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -(y1-val*(i-x1)/100);
						draw_coor[point_num++].y = i;
						#else
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1-val*(i-x1)/100;
						#endif
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1-val*(i-x1)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1-val*(i-x1)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		} else {
			if(y1 < y2) {		// abs(x1-x2) > abs(y1-y2)		// x1 >= x2		// y1 < y2
				for(int16_t i = x1; i >= x2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = y1+val*(x1-i)/100;
						draw_coor[point_num++].y = -i;
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -(y1+val*(x1-i)/100);
						draw_coor[point_num++].y = i;
						#else
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1+val*(x1-i)/100;
						#endif
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1+val*(x1-i)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1+val*(x1-i)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) > abs(y1-y2)		// x1 >= x2		// y1 >= y2
				for(int16_t i = x1; i >= x2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = y1-val*(x1-i)/100;
						draw_coor[point_num++].y = -i;
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -(y1-val*(x1-i)/100);
						draw_coor[point_num++].y = i;
						#else
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1-val*(x1-i)/100;
						#endif
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1-val*(x1-i)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1-val*(x1-i)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		}
	} else {
		val = (int16_t)(100.0f * abs(x2-x1) / abs(y2-y1));
		if(x1 < x2) {
			if(y1 < y2) {		// abs(x1-x2) <= abs(y1-y2)		// x1 < x2		// y1 < y2
				for(int16_t i = y1; i <= y2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = -(x1+val*(i-y1)/100);
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -i;
						draw_coor[point_num++].y = x1+val*(i-y1)/100;
						#else
						draw_coor[point_num].x = x1+val*(i-y1)/100;
						draw_coor[point_num++].y = i;
						#endif
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1+val*(i-y1)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1+val*(i-y1)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) <= abs(y1-y2)		// x1 < x2		// y1 >= y2
				for(int16_t i = y1; i >= y2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = -(x1+val*(y1-i)/100);
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -i;
						draw_coor[point_num++].y = x1+val*(y1-i)/100;
						#else
						draw_coor[point_num].x = x1+val*(y1-i)/100;
						draw_coor[point_num++].y = i;
						#endif
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1+val*(y1-i)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1+val*(y1-i)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		} else {
			if(y1 < y2) {		// abs(x1-x2) <= abs(y1-y2)		// x1 >= x2		// y1 < y2
				for(int16_t i = y1; i <= y2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = -(x1-val*(i-y1)/100);
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -i;
						draw_coor[point_num++].y = x1-val*(i-y1)/100;
						#else
						draw_coor[point_num].x = x1-val*(i-y1)/100;
						draw_coor[point_num++].y = i;
						#endif
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1-val*(i-y1)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1-val*(i-y1)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) <= abs(y1-y2)		// x1 >= x2		// y1 >= y2
				for(int16_t i = y1; i >= y2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						#if RECOGNIZE_TURN_CLOCKWISE
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = -(x1-val*(y1-i)/100);
						#elif RECOGNIZE_TURN_ANTICLOCKWISE
						draw_coor[point_num].x = -i;
						draw_coor[point_num++].y = x1-val*(y1-i)/100;
						#else
						draw_coor[point_num].x = x1-val*(y1-i)/100;
						draw_coor[point_num++].y = i;
						#endif
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1-val*(y1-i)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1-val*(y1-i)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		}
	}
}
/* USER CODE END 1 */
