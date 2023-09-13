/**
 ******************************************************************************
 * @file    gyropacket.h
 * @author  TungBT23
 * @date    12nd Sep 2023
 * @brief   JOB 3: Package data from gyroscope
 ******************************************************************************
 * @attention
 *
 * Copyright (c)
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#ifndef GYROPACKET_H_
#define GYROPACKET_H_
/******************************************************************************
* INCLUDES
******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "gyro.h"
/******************************************************************************
* EXPORTED CONSTANTS
******************************************************************************/

/** @defgroup Gyroscope package field constants
 * @{
 */
#define PACKAGE_SIZE                   (64U)

#define PREAMBLE                       (0xABCDU)
#define PACKAGE_VERSION                (0x01U)
/**
 * @}
 */

/******************************************************************************
* EXPORTED TYPEDEF
******************************************************************************/

/**
 * @brief  Error status
 */
typedef enum
{
    SUCCESS = 0U,
    ERROR = !SUCCESS
}ErrorStatus;

/**
 * @brief  Gyroscope packet struct
 */
typedef struct __Gyro_PackageStruct
{
   uint8_t            Preamble[2];         /*<! Preamble start bytes */
   uint8_t            PackageVer;          /*<! Package version */
   uint8_t            Timestamp[6];        /*<! Gyroscope sensro read time*/
   Gyro_ParamsTypeDef Data ;               /*<! Sensor data */
   uint8_t            Used;                /*<! Using mark */
   uint8_t            Reserved[2];          /*<! Reserved for future use */
   uint8_t            CRC[2];              /*<! CRC Check bytes */
} __attribute__((packed)) Gyro_PackageTypeDef;

/**
 * @brief  Gyroscope package information as strings
 */
typedef struct __Gyro_StringStruct
{
   char PackageVer[2];          /*<! Packet version xx */
   char Timestamp[6];           /*<! Timestamp xx:xx:xx */
   char GyroData[6][6];         /*<! Gyroscope data xxx,xx */
}Gyro_StringsTypeDef;

/**
 * @brief  Gyroscope packet union
 */
typedef union __Gyro_DataFrameUnion
{
   Gyro_PackageTypeDef Fields;                 /*<! Package frame with fields*/
   uint8_t             ByteFrame[PACKAGE_SIZE]; /*<! Data frame in as bytes */
} Gyro_DataFrameTypeDef;

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
* @brief   Build a package from data that was read from sensor
 * @param  pFrame pointer to package struct
 * @param  pSensorData pointer to gyroscope data struct
 * @return ErrorStatus SUCCESS or ERROR
 */
ErrorStatus GyroPackage_Build(Gyro_DataFrameTypeDef *pFrame,\
                              Gyro_ParamsTypeDef *pSensorData);


/**
* @brief  Convert package to struct of strings used for printing, interface
 * @param pFrame pointer to package struct
 * @param pString pointer to string struct
* @return ErrorStatus SUCCESS or ERROR
*/
ErrorStatus GyroPackage_ToString(Gyro_DataFrameTypeDef *pFrame,\
                                 Gyro_StringsTypeDef* pString);

#endif /* GYROPACKET_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/
