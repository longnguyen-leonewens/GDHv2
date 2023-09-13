/**
  ******************************************************************************
  * @file    gyro_sim.h
  * @author  LongH9
  * @date    11st Sep 2027
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
#ifndef GYRO_SIM_H_
#define GYRO_SIM_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/
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

/** @defgroup Parameter read options from gyroscope simulation
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
 * EXPORTED CONSTANTS
 ******************************************************************************/


/******************************************************************************
 * EXPORTED MACROS
 ******************************************************************************/

/******************************************************************************
 * EXPORTED VARIABLES
 ******************************************************************************/

/******************************************************************************
 * EXPORTED FUNCTIONS PROTOTYPES
 ******************************************************************************/

/******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Start gyroscope simulating thread
 * @param  None
 * @retval StatusTypeDef Error status
 */
StatusTypeDef GyroSim_StartSimulation(uint32_t simFrequency);

/**
 * @brief  Stop gyroscope simulating thread
 * @param  None
 * @retval StatusTypeDef Error status
 */
StatusTypeDef GyroSim_StopSimulation(void);

/**
 * @brief  Read one or all parameters of gyrocsope simulator
 * @param  readOption Choose which parameters to read
 * @param  pData Pointer to data buffer to hold data read
 * @retval StatusTypeDef Error status
 * @note   For READ_ALL: the sequence of parameters are
 *         Axis X -> Axis Y -> Axis Z -> Acceleration X -> Acceleration Y -> Acceleration Z -> Temperature
 */
StatusTypeDef GyroSim_ReadData(uint8_t readOption, double* pData);

#endif /* GYRO_SIM_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/