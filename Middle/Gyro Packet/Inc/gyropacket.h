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
#include "gyro.h"
/******************************************************************************
* EXPORTED CONSTANTS
******************************************************************************/
#define SIZE_OF_PACKAGE 70
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
* @brief Struct example
* @note  Struct shoulde be name [Module name]_[Function of Struct]TypeDef
* @note  Struct members should capitalized every word
*/

typedef enum {
    SUCCESS,
    FAIL,
}status_t;


typedef struct Gyro_Data_Struct{
   double Gyro_X;
   double Gyro_Y;
   double Gyro_Z;
   double Acce_X;
   double Acce_Y;
   double Acce_Z;
   double Temperature;
} __attribute__((packed)) Gyro_Data_Struct_tTypeDef;

typedef struct __Gyro_PackageStruct
{
   uint8_t Preamble[2];
   uint8_t Package_Version;
   uint8_t Timestamp[6];
   Gyro_Data_Struct_tTypeDef Data ;
   uint8_t Used;
   uint8_t Reserve[2];
   uint8_t CRC[2];
} __attribute__((packed)) Gyro_PackageStruct_tTypeDef;

typedef union union_frame{
   Gyro_PackageStruct_tTypeDef Strc;
   uint8_t Frame[SIZE_OF_PACKAGE];
} Package_FrameTypeDef;

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
* @brief convert to stirng
* @param number convert to string
* @param string is array to save string
* @return the string after convert
*/
status_t GyroPackage_ToString(int number,char* string);


/**
* @brief convert package to array
* @param package the struct input 
* @return success or fail
*/
status_t GyroPackage_PackageToArray(Package_FrameTypeDef* package);


/**
* @brief convert array to package
* @param package the array input output struct
* @param array  input 
* @return success or fail
*/
status_t GyroPackage_ArrayToPackage(Package_FrameTypeDef* package,uint8_t* array);

#endif /* GYROPACKET_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/
