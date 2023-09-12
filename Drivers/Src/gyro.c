/**
  ******************************************************************************
  * @file    gyro.c
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

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "gyro_sim.h"
#include "gyro.h"
/******************************************************************************
 * PRIVATE TYPEDEF
 ******************************************************************************/

/******************************************************************************
 * PRIVATE CONSTANTS
 ******************************************************************************/

/******************************************************************************
 * PRIVATE MACROS
 ******************************************************************************/

/******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/

/******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES
 ******************************************************************************/

/******************************************************************************
 * PRIVATE FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Initialize gyroscope sensor
 * @param  None
 * @return DRV_StatusTypeDef Error status
 */
DRV_StatusTypeDef Gyro_Init(void)
{
    DRV_StatusTypeDef initStatus = ERROR_NONE;
    /* Initialize GPIO Pins, Clocks, Configuration */

    /* Start simulation */
    if(GyroSim_StartSimulation(DEFAULT_FREQUENCY))
    {
        initStatus = ERROR;
    }
    return initStatus;
}

/**
 * @brief  Deinitialize Gyroscope sensor
 * @param  None
 * @return DRV_StatusTypeDef Error status
 */
DRV_StatusTypeDef Gyro_DeInit(void)
{
    DRV_StatusTypeDef deinitStaus = ERROR_NONE;
    /* Deinitialize GPIO Pins, Clocks, Periph */

    /* Stop simulation */
    if(GyroSim_StopSimulation())
    {
        deinitStaus = ERROR;
    }
    return deinitStaus;
}

/**
 * @brief  Read data from gyroscopesensor
 * @param  readOption Could be a value of @defgroup Gyro_ReadOption
 * @param  pData Pointer to data buffer for storing values
 * @return DRV_StatusTypeDef Error status
 */
DRV_StatusTypeDef Gyro_ReadData(uint8_t readOption, double *pData)
{
    DRV_StatusTypeDef readStatus = ERROR_NONE;
    if (GyroSim_ReadData(readOption, pData))
    {
        readStatus = ERROR;
    }
    return readStatus;
}

/******************************************************************************
 * EOF
 ******************************************************************************/