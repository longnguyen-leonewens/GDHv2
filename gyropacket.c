/**
 ******************************************************************************
 * @file    ais_fsar_gyropacket.h
 * @author  TungBT23
 * @version
 * @date
 * @brief
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


/******************************************************************************
* INCLUDES
******************************************************************************/
#include "gyropacket.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
void GyroPackage_GetTime(uint8_t *pBuffer);
/******************************************************************************
* PRIVATE FUNCTIONS
******************************************************************************/

/**
* @brief   Build a package from data that was read from sensor
 * @param  pPackage pointer to package struct
 * @param  pData pointer to gyroscope data struct
 * @return StatusTypeDef ERROR_NONE or ERROR
 */
StatusTypeDef GyroPackage_Build(Gyro_DataFrameTypeDef *pFrame,\
                              Gyro_ParamsTypeDef *pSensorData)
{
    uint16_t crc    = 0u;
    uint16_t length = PACKAGE_SIZE - 2u;
    uint8_t *pU8Temp = &pFrame->ByteFrame[0];
    /* Check parameters */
    assert_param(IS_VALID_POINTER(pFrame));
    assert_param(IS_VALID_POINTER(pSensorData));
    /* Preamble */
    pFrame->Fields.Preamble[0] = 0xAB;
    pFrame->Fields.Preamble[1] = 0XCD;
    /* Package version */
    pFrame->Fields.PackageVer  = 0x01;
    /* Timestamp */
    GyroPackage_GetTime(pFrame->Fields.Timestamp);
    /* Gyrosccope data */
    pFrame->Fields.Data.axisX = pSensorData->axisX;
    pFrame->Fields.Data.axisY = pSensorData->axisY;
    pFrame->Fields.Data.axisZ = pSensorData->axisZ;
    pFrame->Fields.Data.acceX = pSensorData->acceX;
    pFrame->Fields.Data.acceY = pSensorData->acceY;
    pFrame->Fields.Data.acceZ = pSensorData->acceZ;
    pFrame->Fields.Data.temp  = pSensorData->temp;
    /* CRC Check */
    while (length)
   {
       crc = crc ^ (*pU8Temp++ << 8u);
       for (uint8_t i = 0u; i < 8u; i++)
       {
           if (crc & 0x8000u)
           {
               crc = (crc << 1u) ^ 0x1021u;
           }
           else
           {
               crc = crc << 1u;
           }
       }
       length--;
   }
    pFrame->Fields.CRC[0] = (uint8_t)(crc&0xFF);
    pFrame->Fields.CRC[1] = (uint8_t)((crc&0xFF00)>>8);

    return ERROR_NONE;
}

/**
 * @brief Convert package frame to array of uint8_t
 * @param pFrame Pointer to package frame
 * @param array Array
 * @return Error status
 */
StatusTypeDef GyroPackage_PackageToArray(Gyro_DataFrameTypeDef* pFrame,\
                                       uint8_t *array)
{
    /* Check parameters */
    assert_param(IS_VALID_POINTER(pFrame));
    assert_param(IS_VALID_POINTER(array));
    memcpy(array, pFrame->ByteFrame, PACKAGE_SIZE);
    return ERROR_NONE;
}

/**
 * @brief Convert array of uint8_t to package frame
 * @param array Array
 * @param pFrame Pointer to package frame
 * @return Error status
 */
StatusTypeDef GyroPackage_ArrayToPackage(uint8_t *array,\
                                       Gyro_DataFrameTypeDef* pFrame)
{
    /* Check parameters */
    assert_param(IS_VALID_POINTER(pFrame));
    assert_param(IS_VALID_POINTER(array));
    memcpy(pFrame->ByteFrame, array, PACKAGE_SIZE);
    return ERROR_NONE;
}

/**
* @brief  Convert package to struct of strings used for printing, interface
 * @param pFrame pointer to package struct
 * @param pString pointer to string struct
* @return StatusTypeDef ERROR_NONE or ERROR
*/
StatusTypeDef GyroPackage_ToString(Gyro_DataFrameTypeDef *pFrame,\
                                 Gyro_StringsTypeDef* pString)
{
    uint8_t i;
    /* Check parameters */
    assert_param(IS_VALID_POINTER(pFrame));
    assert_param(IS_VALID_POINTER(pString));
    /* Convert */
    /* Version */
    snprintf(pString->PackageVer, 2U, "%d", pFrame->Fields.PackageVer);
    /* Time in format hour:minute:second */
    snprintf(pString->Time, 8U, "%02d:%02d:%02d", pFrame->Fields.Timestamp[2U], \
                                                  pFrame->Fields.Timestamp[1U],\
                                                  pFrame->Fields.Timestamp[0U]);
    /* Date in format dd/mm/yyyy */
    snprintf(pString->Date, 10U, "%02d/%02d/%04d", pFrame->Fields.Timestamp[3U], \
                                                   pFrame->Fields.Timestamp[4U],\
                                                   pFrame->Fields.Timestamp[5U] + 1900U);
    /* Gyroscope data */
    for (i = 0; i < 6U; i++)
    {
        snprintf(pString->GyroData[i], 6U, "%.3f", ((double*)&pFrame->Fields.Data.axisX)[i]);
    }
    /* Temp */
    snprintf(pString->GyroData[6], 6U, "%d", pFrame->Fields.Data.temp);
    return ERROR_NONE;
}

/**
 * @brief Get local time
 * @param pBuffer Buffer tp store converted time
 * @note  None
 */
void GyroPackage_GetTime(uint8_t *pBuffer)
{
    time_t    rawTime;
    struct tm *timeRead;
    uint8_t   i;
    /* Check parameters */
    assert_param(IS_VALID_POINTER(pBuffer));
    /* Get time */
    time(&rawTime);
    timeRead = localtime(&rawTime);
    for (i = 0; i < 6; i++)
    {
        pBuffer[i] = (uint8_t)(((int*)timeRead)[i]);
    }
}
/******************************************************************************
 * EOF
 ******************************************************************************/
