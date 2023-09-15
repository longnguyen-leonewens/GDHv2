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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include <_timeval.h>
#include <pthread.h>
#include <unistd.h>
#include "gyro_sim.h"
/******************************************************************************
 * PRIVATE TYPEDEF
 ******************************************************************************/

typedef struct timeval Gyro_Time_Val;

/**
 * @brief Struct for parameter of gyro
 *
 */
typedef struct __GyroSim_ParamStruct
{
    double   axisX;                  /*>! x-axis position */
    double   axisY;                  /*>! y-axis position */
    double   axisZ;                  /*>! z-axis position */
    double   acceX;                  /*>! x-axis acceleration */
    double   acceY;                  /*>! y-axis acceleration */
    double   acceZ;                  /*>! z-axis acceleration */
    int16_t temp;                   /*>! Temperature in Celcius */
}GyroSim_ParamsTypeDef;

/******************************************************************************
 * PRIVATE CONSTANTS
 ******************************************************************************/

/** @defgroup Gyroscope simulation thread state
 * @{
 */
#define GYRO_SIMULATION_RUNNING                (1U)
#define GYRO_SIMULATION_STOPPED                (0U)
/**
 * @}
 */

/** @defgroup Misc
 * @{
 */
#define PI            (3.14159265358979323846)
/**
 * @}
 */
/******************************************************************************
 * PRIVATE MACROS
 ******************************************************************************/
#define IS_SIM_READ_OPTION(OP)          (((OP) == SIMULATOR_READ_AXIS_X) \
                                      || ((OP) == SIMULATOR_READ_AXIS_Y) \
                                      || ((OP) == SIMULATOR_READ_AXIS_Z) \
                                      || ((OP) == SIMULATOR_READ_ACCE_X) \
                                      || ((OP) == SIMULATOR_READ_ACCE_Y) \
                                      || ((OP) == SIMULATOR_READ_ACCE_Z) \
                                      || ((OP) == SIMULATOR_READ_TEMP)   \
                                      || ((OP) == SIMULATOR_READ_ALL))

#define IS_VALID_POINTER(PTR)                   ((PTR) != NULL)
/******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/
static GyroSim_ParamsTypeDef gyroData;       /* Struct to hold simulation data */
static pthread_t             threadGyro;     /* For Gyroscope thread */
static pthread_mutex_t       mutexGyroData;  /* Mutex for Gyroscope data */
static bool                  isRunning;      /* For controlling the thread */
static uint32_t              generateFreq;   /* Data generating frequency */
/******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES
 ******************************************************************************/
static void *Gyro_Simulation(void* arg);
static void GyroSim_Delay(uint64_t microsec);
/******************************************************************************
 * PRIVATE FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Gyroscope imulation thread
 * @param  arg Argument to the function
 * @return None
 */
static void *Gyro_Simulation(void* arg)
{
    uint32_t simFrequency = MIN_FREQUENCY;
    double temp  = 0;
    double alpha = 0;
    /* Check if frequency is passed as an argument */
    if (arg != NULL)
    {
        simFrequency = *((uint32_t *)arg);
    }
    /* Simulation */
    isRunning = GYRO_SIMULATION_RUNNING;
    while (isRunning)
    {
        /* Lock mutex */
        pthread_mutex_lock(&mutexGyroData);
        /* Randomly generate axis positions */
        gyroData.axisX = (double)rand()/RAND_MAX * 2 * MAX_GYRO - MAX_GYRO;
        gyroData.axisY = (double)rand()/RAND_MAX * 2 * MAX_GYRO - MAX_GYRO;
        gyroData.axisZ = (double)rand()/RAND_MAX * 2 * MAX_GYRO - MAX_GYRO;
        /* Randomly generate accelerations */
        gyroData.acceX = (double)rand()/RAND_MAX * 2 * GRAVITY_ACCE - GRAVITY_ACCE;
        temp           = GRAVITY_ACCE * GRAVITY_ACCE - (gyroData.acceX) * (gyroData.acceX);
        gyroData.acceY = sqrt(temp) * sin(alpha);
        gyroData.acceZ = sqrt(temp) * cos(alpha);
        gyroData.temp  = OFFSET_TEMP + AVG_TEMP * sin(alpha);
        /* Unlock mutex */
        pthread_mutex_unlock(&mutexGyroData);
        alpha = alpha + PI/3000000;
    }
    /* End the thread */
    pthread_exit(NULL);
    return NULL;
}

/**
 * @brief  Initialize variables and start a gyroscope simulation thread
 * @param  simFrequency Set simulation frequency (data changing rate)
 * @retval StatusTypeDef Error status
 */
StatusTypeDef GyroSim_StartSimulation(uint32_t simFrequency)
{
    StatusTypeDef startState = ERROR_NONE;
    /* Initialize gyro data */
    gyroData.axisX = 0;
    gyroData.axisY = 0;
    gyroData.axisZ = 0;
    gyroData.acceX = 0;
    gyroData.acceY = 0;
    gyroData.acceZ = 0;
    gyroData.temp  = 0;
    /* Start gyro simulation thread */
    generateFreq = simFrequency;
    if (simFrequency == 0)
    {
        startState = ERROR;
    }
   else if (pthread_create(&threadGyro, NULL, Gyro_Simulation, (void *)&generateFreq) != 0)
    {
        startState = ERROR;
    }
    else if (pthread_mutex_init(&mutexGyroData, NULL))
    {
        startState = ERROR;
    }
    return startState;
}

/**
 * @brief  Initialize variables and start a gyroscope simulation thread
 * @param  simFrequency Set simulation frequency (data changing rate)
 * @retval StatusTypeDef Error status
 */
StatusTypeDef GyroSim_StopSimulation(void)
{
    isRunning = 0;
    return ERROR_NONE;
}

/**
 * @brief  Read one or all parameters of gyrocsope simulator
 * @param  readOption Choose which parameters to read
 * @param  pData Pointer to data buffer to hold data read
 * @retval StatusTypeDef Error status
 */
StatusTypeDef GyroSim_ReadData(uint8_t readOption, double* pData, int16_t *pTemp)
{
    double       *pTempData  = (double*)&gyroData;
    uint8_t       i          = 0;
    StatusTypeDef readStatus = ERROR_NONE;
    /* Assertion */
    assert(IS_SIM_READ_OPTION(readOption));
    /* Lock mutex */
    pthread_mutex_lock(&mutexGyroData);
    if (readOption == SIMULATOR_READ_TEMP)
    {
        /* Check parameter */
        assert(IS_VALID_POINTER(pTemp));
        *pTemp = gyroData.temp;
    }
    else if (readOption == SIMULATOR_READ_ALL)
    {
        /* Check parameter */
        assert(IS_VALID_POINTER(pData));
        /* Read gyroscope stats */
        for (i = 0; i < 6; i++)
        {
            pData[i] = pTempData[i];
        }
        *((int16_t*)&pData[6]) = gyroData.temp;
    }
    else
    {
        /* Check parameter */
        assert(IS_VALID_POINTER(pData));
        *pData = pTempData[readOption];
    }
    /* Unlock mutex */
    pthread_mutex_unlock(&mutexGyroData);
    return ERROR_NONE;
}

/**
 * @brief  Delay in microseconds
 * @param  microsec Number of microseconds
 * @retval None
 */
static void GyroSim_Delay(uint64_t microsec)
{
    uint64_t start;
    uint64_t current;
    Gyro_Time_Val GyroSim_Time;
    gettimeofday(&GyroSim_Time, NULL);
    start = GyroSim_Time.tv_usec;
    current = start;
    while(current < (start + microsec))
    {
        gettimeofday(&GyroSim_Time, NULL);
        current = GyroSim_Time.tv_usec;
    }
}

/******************************************************************************
 * EOF
 ******************************************************************************/
