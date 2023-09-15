/**
  ******************************************************************************
  * @file    gyro.h
  * @author  LongH9
  * @date    12st Sep 2027
  * @brief   JOB 2: Gyroscope simulation and APIs
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
#ifndef GYRO_H_
#define GYRO_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include <stdint.h>
#include "def.h"
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/**
 * @brief Struct for parameter of gyro
 *
 */
typedef struct __Gyro_ParamStruct
{
    double   axisX;                  /*>! x-axis position */
    double   axisY;                  /*>! y-axis position */
    double   axisZ;                  /*>! z-axis position */
    double   acceX;                  /*>! x-axis acceleration */
    double   acceY;                  /*>! y-axis acceleration */
    double   acceZ;                  /*>! z-axis acceleration */
    int16_t temp;                   /*>! Temperature in Celcius */
} __attribute__((packed)) Gyro_ParamsTypeDef;

/**
  * @brief  Driver Status structures definition
  */
typedef enum
{
  DRV_ERROR_NONE = 0x00U,
  DRV_ERROR      = 0x01U,
  DRV_BUSY       = 0x02U,
  DRV_TIMEOUT    = 0x03U
} DRV_StatusTypeDef;

/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/

/** @defgroup Gyro_Readoption Parameter read options from gyroscope sensor
 * @{
 */
#define GYRO_READ_AXIS_X                   (0U)
#define GYRO_READ_AXIS_Y                   (1U)
#define GYRO_READ_AXIS_Z                   (2U)
#define GYRO_READ_ACCE_X                   (3U)
#define GYRO_READ_ACCE_Y                   (4U)
#define GYRO_READ_ACCE_Z                   (5U)
#define GYRO_READ_TEMP                     (6U)
#define GYRO_READ_ALL                      (7U)
/**
 * @}
 */

/******************************************************************************
 * EXPORTED MACROS
 ******************************************************************************/


/******************************************************************************
 * EXPORTED VARIABLES
 ******************************************************************************/

/******************************************************************************
 * EXPORTED FUNCTIONS PROTOTYPES
 ******************************************************************************/

/**
 * @brief  Initialize gyroscope sensor
 * @param  None
 * @return DRV_StatusTypeDef Error status
 */
DRV_StatusTypeDef Gyro_Init(void);

/**
 * @brief  Deinitialize Gyroscope sensor
 * @param  None
 * @return DRV_StatusTypeDef Error status
 */
DRV_StatusTypeDef Gyro_DeInit(void);

/**
 * @brief  Read data from gyroscopesensor
 * @param  readOption Could be a value of @defgroup Gyro_ReadOption
 * @param  pData Pointer to data buffer for storing values
 * @return DRV_StatusTypeDef Error status
 */
DRV_StatusTypeDef Gyro_ReadData(uint8_t readOption, double *pData, int16_t *pTemp);

#endif /* GYRO_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/
