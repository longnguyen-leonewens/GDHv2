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
uint8_t fifoBuffer[FIFO_SIZE][PACKAGE_SIZE];
/* Package queue struct */
Queue_TypeDef gyroQueue;
/* Gyroscope data struct */
Gyro_ParamsTypeDef gyroData;
/* Gyroscope data frame */
Gyro_DataFrameTypeDef gyroPackage;
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
    Queue_Init(&gyroQueue, (uint8_t*)fifoBuffer, FIFO_SIZE, PACKAGE_SIZE);
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
    int i = 5;
    int count = 0;
    // printf("\n-------------------------------------------------------------------------------------");
    // printf("\n| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|", "Gyro X", "Gyro Y", "Gyro Z", "Acce X", "Acce Y", "Acce Z", "Temp","SimTemp","sqrt(temp)","alpha","sin(alpha)","cos(alpha)");
    // printf("\n-------------------------------------------------------------------------------------");
    // printf("\n-------------------------------------------------------------------------------------");
    printf("\n| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|%-10s| Push or Pop| Index ",\
             "Preamble", "Version", "Timestamp", "Gyro X", "Gyro Y", "Gyro Z","Acce X", "Acce Y", "Acce Z", "Temp","Reserved","Used","CRC");
     printf("\n-------------------------------------------------------------------------------------");
    while(i > 0)
    {
        /* Check if queue is not full yet to read data and push into FIFO */
        if (Queue_IsFull(&gyroQueue) == QUEUE_OK)
        {
            Gyro_ReadData(GYRO_READ_ALL, (double*)&gyroData, NULL);
            //printf("\n| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10d| Main", gyroData.axisX,gyroData.axisY,gyroData.axisZ,gyroData.acceX,gyroData.acceY,gyroData.acceZ,gyroData.temp);
            /* Package data */
            GyroPackage_Build(&gyroPackage, &gyroData);
            // printf("\n| %02X%02X%02X%02X%02X%02X%02X%02X%02X%016llX%016llX%016llX%016llX%016llX%016llX%04X%02X%02X%02X%02X%02X|",
            // gyroPackage.Fields.Preamble[0],gyroPackage.Fields.Preamble[1],gyroPackage.Fields.PackageVer,gyroPackage.Fields.Timestamp[0],gyroPackage.Fields.Timestamp[1],gyroPackage.Fields.Timestamp[2],gyroPackage.Fields.Timestamp[3],gyroPackage.Fields.Timestamp[4],gyroPackage.Fields.Timestamp[5],
            // gyroPackage.Fields.Data.axisX,gyroPackage.Fields.Data.axisY,gyroPackage.Fields.Data.axisZ,gyroPackage.Fields.Data.acceX,gyroPackage.Fields.Data.acceY,gyroPackage.Fields.Data.acceZ,(uint16_t)gyroPackage.Fields.Data.temp,
            // gyroPackage.Fields.Reserved[0],gyroPackage.Fields.Reserved[1],gyroPackage.Fields.Used,gyroPackage.Fields.CRC[0],gyroPackage.Fields.CRC[1]);
            /* Lock mutex */
            printf("\n| %02X | %02X| %02X| %02X|%02X| %02X| %02X|%02X|%02X| %f | %f |%f |%f |%f |%f |%d| %02X| %02X| %02X| %02X| %02X| %s| %d ",\
            gyroPackage.Fields.Preamble[0],gyroPackage.Fields.Preamble[1],gyroPackage.Fields.PackageVer,gyroPackage.Fields.Timestamp[0],gyroPackage.Fields.Timestamp[1],gyroPackage.Fields.Timestamp[2],gyroPackage.Fields.Timestamp[3],gyroPackage.Fields.Timestamp[4],gyroPackage.Fields.Timestamp[5],\
            gyroPackage.Fields.Data.axisX,gyroPackage.Fields.Data.axisY,gyroPackage.Fields.Data.axisZ,gyroPackage.Fields.Data.acceX,gyroPackage.Fields.Data.acceY,gyroPackage.Fields.Data.acceZ,(uint16_t)gyroPackage.Fields.Data.temp,\
            gyroPackage.Fields.Reserved[0],gyroPackage.Fields.Reserved[1],gyroPackage.Fields.Used,gyroPackage.Fields.CRC[0],gyroPackage.Fields.CRC[1], "Push", ++count);
            pthread_mutex_lock(&mutexFIFO);
            /* Enqueue data */
            Queue_Push(&gyroQueue, (uint8_t*)&gyroPackage, PACKAGE_SIZE);
            /* Unlock mutex */
            pthread_mutex_unlock(&mutexFIFO);
            i--;
        }
        /* Check if queue is not empty yet to signal another thread to pop data */
    }
    
    return NULL;
}

/**
 * @brief  Thread for logging data onto FLASH (check valid package, find writable region in FLASH)
 * @param  arg Optional argument
 * @retval None
 */
void* Application_DataLogging(void *arg)
{
    int i = 5;
    int count = 0;
    uint8_t dataBuffer[64U];
    Gyro_DataFrameTypeDef *testFrame;
    while(i > 0)
    {
        if (Queue_IsEmpty(&gyroQueue) == QUEUE_OK)
        {
            /* Lock mutex */
            pthread_mutex_lock(&mutexFIFO);
            Queue_Pop(&gyroQueue, dataBuffer, PACKAGE_SIZE);
            testFrame = (Gyro_DataFrameTypeDef*)dataBuffer;
            printf("\n| %02X | %02X| %02X| %02X|%02X| %02X| %02X|%02X|%02X| %f | %f |%f |%f |%f |%f |%d| %02X| %02X| %02X| %02X| %02X| %s| %d ",\
            testFrame->Fields.Preamble[0],testFrame->Fields.Preamble[1],testFrame->Fields.PackageVer,testFrame->Fields.Timestamp[0],testFrame->Fields.Timestamp[1],testFrame->Fields.Timestamp[2],testFrame->Fields.Timestamp[3],testFrame->Fields.Timestamp[4],testFrame->Fields.Timestamp[5],\
            testFrame->Fields.Data.axisX,testFrame->Fields.Data.axisY,testFrame->Fields.Data.axisZ,testFrame->Fields.Data.acceX,testFrame->Fields.Data.acceY,testFrame->Fields.Data.acceZ,(uint16_t)testFrame->Fields.Data.temp,\
            testFrame->Fields.Reserved[0],testFrame->Fields.Reserved[1],testFrame->Fields.Used,testFrame->Fields.CRC[0],testFrame->Fields.CRC[1], "Pop", ++count);
            /* Unlock mutex */
            pthread_mutex_unlock(&mutexFIFO);
            i--;
        }
    }
    return NULL;
}

/******************************************************************************
 * EOF
 ******************************************************************************/