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

/**
 * @brief Struct for parameter of gyro
 *
 */
typedef struct __Gyro_ParamStruct
{
    double axisX;                  /*>! x-axis position */
    double axisY;                  /*>! y-axis position */
    double axisZ;                  /*>! z-axis position */
    double acceX;                  /*>! x-axis acceleration */
    double acceY;                  /*>! y-axis acceleration */
    double acceZ;                  /*>! z-axis acceleration */
    double temp;                   /*>! Temperature in Celcius */
}Gyro_ParamsTypeDef;

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
/******************************************************************************
 * PRIVATE MACROS
 ******************************************************************************/

/******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/
static Gyro_ParamsTypeDef gyroData;       /* Struct to hold simulation data */
static pthread_t          threadGyro;     /* For Gyroscope thread */
static pthread_mutex_t    mutexGyroData;  /* Mutex for Gyroscope data */
static bool               isRunning;      /* For controlling the thread */
/******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES
 ******************************************************************************/
static void *Gyro_Simulation(void* arg);
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
    uint32_t simFrequency = DEFAULT_FREQUENCY;
    double time  = 0;
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
        alpha          = 2 * M_PI * simFrequency * time;
        gyroData.acceY = sqrt(temp) * sin(alpha);
        gyroData.acceZ = sqrt(temp) * cos(alpha);
        gyroData.temp  = OFFSET_TEMP + AVG_TEMP * sin(alpha);
        /* Unlock mutex */
        pthread_mutex_unlock(&mutexGyroData);
        /* Sleep */
        usleep((1.0/simFrequency) * 1e6);
        time = time + 1.0/simFrequency;
    }
    /* End the thread */
    pthread_exit(NULL);
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
    if (pthread_create(&threadGyro, NULL, Gyro_Simulation, (void *)&simFrequency) != 0)
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
StatusTypeDef GyroSim_ReadData(uint8_t readOption, double* pData)
{
    double  *pTempData = (double*)&gyroData;
    uint8_t i          = 0;
    /* Assertion */
    assert(IS_SIM_READ_OPTION(readOption));
    /* Lock mutex */
    pthread_mutex_lock(&mutexGyroData);
    if (readOption == SIMULATOR_READ_ALL)
    {
        for (i = 0; i < 7; i++)
        {
            pData[i] = pTempData[i];
        }
    }
    else
    {
        *pData = ((double*)&gyroData)[readOption];
    }
    /* Unlock mutex */
    pthread_mutex_unlock(&mutexGyroData);
    return ERROR_NONE;
}

/******************************************************************************
 * EOF
 ******************************************************************************/