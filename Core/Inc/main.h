/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "eguha_config.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLED_Pin GPIO_PIN_13
#define BLED_GPIO_Port GPIOC
#define GLED_Pin GPIO_PIN_14
#define GLED_GPIO_Port GPIOC
#define RLED_Pin GPIO_PIN_15
#define RLED_GPIO_Port GPIOC
#define GMI_ENABLE_Pin GPIO_PIN_1
#define GMI_ENABLE_GPIO_Port GPIOA
#define CCID_SELF_ENABLE_Pin GPIO_PIN_6
#define CCID_SELF_ENABLE_GPIO_Port GPIOA
#define CP_RY_Pin GPIO_PIN_10
#define CP_RY_GPIO_Port GPIOB
#define MC1_Pin GPIO_PIN_11
#define MC1_GPIO_Port GPIOB
#define SPI2_NSS_Pin GPIO_PIN_12
#define SPI2_NSS_GPIO_Port GPIOB
#define STE_LED1_Pin GPIO_PIN_15
#define STE_LED1_GPIO_Port GPIOA
#define BLE_NET_STATUS_Pin GPIO_PIN_3
#define BLE_NET_STATUS_GPIO_Port GPIOB
#define BLE_WAKEUP_OUT_Pin GPIO_PIN_4
#define BLE_WAKEUP_OUT_GPIO_Port GPIOB
#define BLE_WAKEUP_IN_Pin GPIO_PIN_5
#define BLE_WAKEUP_IN_GPIO_Port GPIOB
#define BLE_RST_Pin GPIO_PIN_8
#define BLE_RST_GPIO_Port GPIOB
#define I_EMG_Pin GPIO_PIN_9
#define I_EMG_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
