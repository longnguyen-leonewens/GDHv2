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

/******************************************************************************
 * PRIVATE MACROS
 ******************************************************************************/

/******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/

/******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES
 ******************************************************************************/
void Application_DataHandling(void *arg);
void Application_DataLogging(void *arg);
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
    //Queue_Init();
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

    return 0;
}

/**
 * @brief  Thread for handling data (read data, queue operations)
 * @param  arg Optional argument
 * @retval None
 */
void Application_DataHandling(void *arg)
{

}

/**
 * @brief  Thread for logging data onto FLASH (check valid package, find writable region in FLASH)
 * @param  arg Optional argument
 * @retval None
 */
void Application_DataLogging(void *arg)
{

}

/******************************************************************************
 * EOF
 ******************************************************************************/