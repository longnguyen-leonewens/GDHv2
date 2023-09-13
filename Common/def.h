/**
  ******************************************************************************
  * @file    def.h
  * @author  Leo Newens (LongNDT5)
  * @version
  * @date
  * @brief
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 longnguyen-leonewens (Github)
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef DEF_H_
#define DEF_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include <stdint.h>
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the
  *        HAL drivers code
  */
#define USE_FULL_ASSERT    1U

/**
 * @brief  Error status
 */
typedef enum
{
    SUCCESS = 0U,
    ERROR = !SUCCESS
}ErrorStatus;

/**
  * @brief  Status structures definition
  */
typedef enum
{
  ERROR_NONE = 0x00U,
  ERROR      = 0x01U,
  BUSY       = 0x02U,
  TIMEOUT    = 0x03U
} StatusTypeDef;

#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */
/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/



/******************************************************************************
 * EXPORTED MACROS
 ******************************************************************************/


#endif /* DEF_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/