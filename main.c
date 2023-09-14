/**
  ******************************************************************************
  * @file    library.c
  * @author  Leo Newens (LongNDT5)
  * @version
  * @date
  * @brief
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
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "gyropacket.h"
#include "gyro.h"
#include "queue.h"
/******************************************************************************
 * PRIVATE TYPEDEF
 ******************************************************************************/

/******************************************************************************
 * PRIVATE CONSTANTS
 ******************************************************************************/

/** @defgroup FIFO Configurations
 * @{
 */
#define FIFO_SIZE                        (16U)
/**
 * @}
 */

/******************************************************************************
 * PRIVATE MACROS
 ******************************************************************************/

/******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/
/* FIFO Buffer for storing gyroscope data packet */
uint8_t fifoBuffer[PACKAGE_SIZE][FIFO_SIZE];
/* Package queue struct */
Queue_TypeDef gyroQueue;
/* Gyroscope data struct */
Gyro_ParamsTypeDef gyroData;
/* Mutex pthread type for FIFO */
pthread_mutex_t mutexFIFO;
/* Condition variable for signaling data logging thread */
pthread_cond_t condNotifyThread;
/******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES
 ******************************************************************************/
void* Application_DataHandling(void *arg);
void* Application_DataLogging(void *arg);
/******************************************************************************
 * PRIVATE FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Main function of the program
 * @param  None
 * @return None
 */
int main(void)
{
    /* Initialize peripherals and modules */
    Gyro_Init();
    //Flash_Init();
    Queue_Init(&gyroQueue, (uint8_t*)fifoBuffer, PACKAGE_SIZE, FIFO_SIZE);
    /* Init mutex for pushing and popping FIFO */
    pthread_mutex_init(&mutexFIFO, NULL);
    /* Init condition variable for thread signaling */
    pthread_cond_init(&condNotifyThread, NULL);
    /* Create threads for handling gyrocope data and logging to FLASH */
    pthread_t threadDataHandling;
    pthread_t threadDataLogging;

    pthread_create(&threadDataHandling, NULL, Application_DataHandling, NULL);
    pthread_create(&threadDataLogging , NULL, Application_DataLogging , NULL);
    /* Join threads to prevent this thread ends */
    pthread_join(threadDataHandling, NULL);
    pthread_join(threadDataLogging , NULL);
    /* Deinitialize peripherals and modules */
    Gyro_DeInit();
    /* Multithreading resources cleaning */
    pthread_mutex_destroy(&mutexFIFO);

    return 0;
}

/**
 * @brief  Thread for handling data (read data, queue operations)
 * @param  arg Optional argument
 * @retval None
 */
void* Application_DataHandling(void *arg)
{
    printf("\n-------------------------------------------------------------------------------------");
    printf("\n| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|", "Gyro X", "Gyro Y", "Gyro Z", "Acce X", "Acce Y", "Acce Z", "Temp","SimTemp","sqrt(temp)","alpha","sin(alpha)","cos(alpha)");
    printf("\n-------------------------------------------------------------------------------------");
    while(true)
    {
        /* Check if queue is not full yet to read data and push into FIFO */
        if (Queue_IsFull(&gyroQueue) == false)
        {
            Gyro_ReadData(GYRO_READ_ALL, (double*)&gyroData, NULL);
            //printf("\n| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10d|", gyroData.axisX,gyroData.axisY,gyroData.axisZ,gyroData.acceX,gyroData.acceY,gyroData.acceZ,gyroData.temp);
            /* Package data */
            //GyroPackage_Build();
            /* Lock mutex */
            pthread_mutex_lock(&mutexFIFO);
            /* Enqueue data */
            //Queue_Enqueue(&gyroQueue,    ,     );
            /* Unlock mutex */
            pthread_mutex_unlock(&mutexFIFO);
        }
        /* Check if queue is not empty yet to signal another thread to pop data */
        if (Queue_IsEmpty(&gyroQueue) == false)
        {
            //pthread_cond_signal();
        }
    }
}

/**
 * @brief  Thread for logging data onto FLASH (check valid package, find writable region in FLASH)
 * @param  arg Optional argument
 * @retval None
 */
void* Application_DataLogging(void *arg)
{
    while(true)
    {
        /* Lock mutex */
        pthread_mutex_lock(&mutexFIFO);
        /* Unlock mutex */
        pthread_mutex_unlock(&mutexFIFO);
    }
}

/******************************************************************************
 * EOF
 ******************************************************************************/