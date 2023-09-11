/**
  ******************************************************************************
  * @file    gyro_sim.c
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

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "gyro_sim.h"
/******************************************************************************
 * PRIVATE TYPEDEF
 ******************************************************************************/

/******************************************************************************
 * PRIVATE CONSTANTS
 ******************************************************************************/

/** @defgroup Gyroscope constants
 * @{
 */
#define FREQUENCY                   (60U)
#define ACCE                        (9.8)
#define MAX_GYRO                    (10U)
#define AVERAGE_TEMPERATURE         (77.5)
#define OFFSET_TEMPERATURE          (37.5)
/**
 * @}
 */

/******************************************************************************
 * PRIVATE MACROS
 ******************************************************************************/

/******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/
static ParamGyro_t Gyro_Data;
/******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES
 ******************************************************************************/

/******************************************************************************
 * PRIVATE FUNCTIONS
 ******************************************************************************/

static void *s_Gyro_Simulator(void* arg)
{
    ParamGyro_t *gyro = (ParamGyro_t *)arg;
    double time = 0;
    double temp = 0;
    double alpha = 0;

    while (1)
    {
        gyro->gyro_x = (double)rand()/RAND_MAX * 2 * MAX_GYRO - MAX_GYRO;
        gyro->gyro_y = (double)rand()/RAND_MAX * 2 * MAX_GYRO - MAX_GYRO;
        gyro->gyro_z = (double)rand()/RAND_MAX * 2 * MAX_GYRO - MAX_GYRO;
        gyro->acce_x = (double)rand()/RAND_MAX * 2 * ACCE - ACCE;
        temp = ACCE * ACCE - (gyro->acce_x) * (gyro->acce_x);
        alpha = 2 * M_PI * FREQUENCY * time;
        gyro->acce_y = sqrt(temp) * sin(alpha);
        gyro->acce_z = sqrt(temp) * cos(alpha);
        gyro->temperature = OFFSET_TEMPERATURE + AVERAGE_TEMPERATURE * sin(alpha);
        usleep((1.0/FREQUENCY) * 1e6);
        time = time + 1.0/FREQUENCY;
    }

    return NULL;
}

void Gyro_Sim_Data_Init(pthread_t gyroThread, ParamGyro_t *data)
{
    /* Initialize gyro data */
    data->gyro_x = 0;
    data->gyro_y = 0;
    data->gyro_z = 0;
    data->acce_x = 0;
    data->acce_y = 0;
    data->acce_z = 0;
    data->temperature = 0;
    /* Start gyro simulation thread */
    pthread_create(&gyroThread, NULL, s_Gyro_Simulator, &Gyro_Data);
}

void Gyro_Sim_Data_Deinit(void)
{
    pthread_exit(NULL);
}

ParamGyro_t Gyro_Sim_Get_Data(void)
{
    return Gyro_Data;
}

double Gyro_Sim_Get_Gyro_X(void)
{
    return Gyro_Data.gyro_x;
}

double Gyro_Sim_Get_Gyro_Y(void)
{
    return Gyro_Data.gyro_y;
}

double Gyro_Sim_Get_Gyro_Z(void)
{
    return Gyro_Data.gyro_z;
}

double Gyro_Sim_Get_Acce_X(void)
{
    return Gyro_Data.acce_x;
}

double Gyro_Sim_Get_Acce_Y(void)
{
    return Gyro_Data.acce_y;
}

double Gyro_Sim_Get_Acce_Z(void)
{
    return Gyro_Data.acce_z;
}

double Gyro_Sim_Get_Temperature(void)
{
    return Gyro_Data.temperature;
}

/******************************************************************************
 * EOF
 ******************************************************************************/