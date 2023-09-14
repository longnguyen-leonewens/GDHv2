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
 * @return ErrorStatus SUCCESS or ERROR
 */
ErrorStatus GyroPackage_Build(Gyro_DataFrameTypeDef *pFrame,\
                              Gyro_ParamsTypeDef *pSensorData)
{
    uint16_t crc    = 0u;
    uint16_t length = PACKAGE_SIZE - 2u;
    uint16_t *pU16Temp = (uint16_t*)pFrame->ByteFrame;
    /* Check parameters */
    //assert(IS_VALID_POINTER(pFrame));
    //assert(IS_VALID_POINTER(pSensorData));
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
       length--;
       crc = crc ^ ((*(pU16Temp + PACKAGE_SIZE - 2U -length)) << 8u);
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
   }
    pFrame->Fields.CRC[0] = ((crc&0xFF00)>>8);
    pFrame->Fields.CRC[1] = (crc&0xFF);

    return SUCCESS;
}

/**
 * @brief Convert package frame to array of uint8_t
 * @param pFrame Pointer to package frame
 * @param array Array
 * @return Error status
 */
ErrorStatus GyroPackage_PackageToArray(Gyro_DataFrameTypeDef* pFrame,\
                                       uint8_t *array)
{
    memcpy(array, pFrame->ByteFrame, PACKAGE_SIZE);
    return SUCCESS;
}

/**
 * @brief Convert array of uint8_t to package frame
 * @param array Array
 * @param pFrame Pointer to package frame
 * @return Error status
 */
ErrorStatus GyroPackage_ArrayToPackage(uint8_t *array,\
                                       Gyro_DataFrameTypeDef* pFrame)
{
    memcpy(pFrame->ByteFrame, array, PACKAGE_SIZE);
    return SUCCESS;
}

/**
* @brief  Convert package to struct of strings used for printing, interface
 * @param pFrame pointer to package struct
 * @param pString pointer to string struct
* @return ErrorStatus SUCCESS or ERROR
*/
ErrorStatus GyroPackage_ToString(Gyro_DataFrameTypeDef *pFrame,\
                                 Gyro_StringsTypeDef* pString)
{
    /* Work in progress */
    return SUCCESS;
}

/******************************************************************************
 * EOF
 ******************************************************************************/
