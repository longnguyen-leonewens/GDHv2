/**
 ******************************************************************************
 * @file    ais_fsar_gyropacket.h
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

/******************************************************************************
* PRIVATE FUNCTIONS
******************************************************************************/

status_t GyroPackage_PackageToArray(Package_FrameTypeDef* package){
    status_t result = FAIL;
    uint16_t crc = 0u;
    uint16_t length = SIZE_OF_PACKAGE - 2;
    uint8_t i = 0;
    while (length)
   {
       length--;
       crc = crc ^ ((*((uint16_t *)package + i++)) << 8u);
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
    package->Strc.CRC[0] = ((crc&0xFF00)>>8);
    package->Strc.CRC[1] = (crc&0xFF);

    result = SUCCESS;

    return result;
}

status_t GyroPackage_ArrayToPackage(Package_FrameTypeDef* package,uint8_t* array){
    status_t result = FAIL;
    package->Strc.Preamble[0]       = array[0];
    package->Strc.Preamble[1]       = array[1];
    package->Strc.Package_Version   = array[2];
    package->Strc.Timestamp[0]       = array[3];
    package->Strc.Timestamp[1]       = array[4];
    package->Strc.Timestamp[2]       = array[5];
    package->Strc.Timestamp[3]       = array[6];
    package->Strc.Timestamp[4]       = array[7];
    package->Strc.Timestamp[5]       = array[8];
    package->Strc.Data.Gyro_X      = (array[9]<<56)+(array[10]<<48)+(array[11]<<40)+(array[12]<<32)+(array[13]<<24)+(array[14]<<16)+(array[15]<<8)+array[16];
    package->Strc.Data.Gyro_Y      = (array[17]<<56)+(array[18]<<48)+(array[19]<<40)+(array[20]<<32)+(array[21]<<24)+(array[22]<<16)+(array[23]<<8)+array[24];
    package->Strc.Data.Gyro_Z      = (array[25]<<56)+(array[26]<<48)+(array[27]<<40)+(array[28]<<32)+(array[29]<<24)+(array[30]<<16)+(array[31]<<8)+array[32];
    package->Strc.Data.Acce_X      = (array[33]<<56)+(array[34]<<48)+(array[35]<<40)+(array[36]<<32)+(array[37]<<24)+(array[38]<<16)+(array[39]<<8)+array[40];
    package->Strc.Data.Acce_Y      = (array[41]<<56)+(array[42]<<48)+(array[43]<<40)+(array[44]<<32)+(array[45]<<24)+(array[46]<<16)+(array[47]<<8)+array[48];
    package->Strc.Data.Acce_Z      = (array[49]<<56)+(array[50]<<48)+(array[51]<<40)+(array[52]<<32)+(array[53]<<24)+(array[54]<<16)+(array[55]<<8)+array[56]; 
    package->Strc.Data.Temperature = (array[57]<<56)+(array[58]<<48)+(array[59]<<40)+(array[60]<<32)+(array[61]<<24)+(array[62]<<16)+(array[63]<<8)+array[64]; 
    package->Strc.Used              = array[65];
    package->Strc.Reserve[0]        = array[66];
    package->Strc.Reserve[1]        = array[67];
    package->Strc.CRC[0]            = array[68];
    package->Strc.CRC[1]            = array[69];
 

    result = SUCCESS;

    return result;
}


status_t GyroPackage_ToString(int number,char* string)
{
    status_t result = FAIL;

    sprintf(string, "%d", number);

    result = SUCCESS;

    return result;
}