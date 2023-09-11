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
#include <math.h>
#include <pthread.h>
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/**
 * @brief Struct for parameter of gyro
 *
 */
typedef struct __Gyro_DataStruct
{
    double gyro_x;                  /*>! x-axis position */
    double gyro_y;                  /*>! y-axis position */
    double gyro_z;                  /*>! z-axis position */
    double acce_x;                  /*>! x-axis acceleration */
    double acce_y;                  /*>! y-axis acceleration */
    double acce_z;                  /*>! z-axis acceleration */
    double temperature;             /*>! Temperature in Celcius */
}ParamGyro_t;

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
 * @brief Funtion to init parameter of gyro sensor
 *
 * @param gyroThread is ID of thread
 * @param data is pointer to the memory that initted
 */
void Gyro_Sim_Data_Init(pthread_t gyroThread, ParamGyro_t *data);

/**
 * @brief Funtion to deinit and exit thread
 *
 */
void Gyro_Sim_Data_Deinit(void);

/**
 * @brief Funtion to get all parameter of gyro sensor
 *
 * @return ParamGyro_t struct for parameter of gyro sensor
 */
ParamGyro_t Gyro_Sim_Get_Data(void);

/**
 * @brief Funtion to get gyro_x
 *
 * @return double value of gyro_x
 */
double Gyro_Sim_Get_Gyro_X(void);

/**
 * @brief Funtion to get gyro_y
 *
 * @return double value of gyro_y
 */
double Gyro_Sim_Get_Gyro_Y(void);

/**
 * @brief Funtion to get gyro_z
 *
 * @return double value of gyro_z
 */
double Gyro_Sim_Get_Gyro_Z(void);

/**
 * @brief Funtion to get acce_x
 *
 * @return double value of acce_x
 */
double Gyro_Sim_Get_Acce_X(void);

/**
 * @brief Funtion to get acce_y
 *
 * @return double value of acce_y
 */
double Gyro_Sim_Get_Acce_Y(void);

/**
 * @brief Funtion to get acce_z
 *
 * @return double value of acce_z
 */
double Gyro_Sim_Get_Acce_Z(void);

/**
 * @brief Funtion to get temperature
 *
 * @return double value of temperature
 */
double Gyro_Sim_Get_Temperature(void);

#endif /* GYRO_SIM_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/