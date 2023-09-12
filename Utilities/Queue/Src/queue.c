/**
 * @file queue.h
 * @author HungDH14
 * @brief J0B 4- QUEUE
 * @version 0.1
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

/*******************************************************************************
* Definitions
******************************************************************************/


/*******************************************************************************
* Prototypes
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

Error_CallbackFunction pError;


/*******************************************************************************
* Code
******************************************************************************/

/**
 * @brief Function is used to initialize for Queue struct
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t -status of function
 */
Queue_Status_t Queue_Init(Queue_Instance_Struct_t* pQueueInstance)
{
    Queue_Status_t retVal = QUEUE_OK;

    if (pQueueInstance != NULL)
    {
        pQueueInstance->size = 0;
        pQueueInstance->head = 0;
        pQueueInstance->tail = 0;
    }
    else
    {
        retVal = QUEUE_FAIL
    }

    return retVal;
}

/**
 * @brief Function is used to check queue full or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t -status of function
 */
Queue_Status_t Queue_IsFull(Queue_Instance_Struct_t* pQueueInstance)
{
    Queue_Status_t retVal = QUEUE_OK;

    if (pQueueInstance != NULL)
    {
        if (pQueueInstance->size == QUEUE_MAX_SIZE)
        {
            retVal = QUEUE_FULL;
        }
    }
    else
    {
        retVal = QUEUE_FAIL;
    }
    return retVal;
}

/**
 * @brief Function is used to check queue empty or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_IsEmpty(Queue_Instance_Struct_t* pQueueInstance)
{
    Queue_Status_t retVal = QUEUE_OK;

    if(pQueueInstance != NULL)
    {
        if (pQueueInstance->size == 0)
        {
            retVal = Queue_IsEmpty;
        }
    }
    else
    {
        retVal = QUEUE_FAIL;
    }

    return retVal;
}

/**
 * @brief Function is used to push data to queue
 * @param pQueueInstance pointer to a queue struct
 * @param pPushData pointer to data needs pushed to the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_Push(Queue_Instance_Struct_t* pQueueInstance,
                          Package_FrameTypeDef* pPushData)
{
    Queue_Status_t retVal = QUEUE_OK;

    if(pQueueInstance != NULL)
    {
        if (Queue_IsFull ==  false)
        {
            pQueueInstance->dataFrame[pQueueInstance->head] = *pPushData;
            pQueueInstance->head                           = (pQueueInstance->head + 1) % QUEUE_MAX_SIZE;
            pQueueInstance->size++;
        }
        else
        {
            pError(QUEUE_FULL);
            retVal = QUEUE _FULL;
        }
    }
    else
    {
        retVal = QUEUE_FAIL;
    }

    return retVal;
}

/**
 * @brief Function is used to pop data from queue
 * @param pQueueInstance pointer to a queue struct
 * @param pPopData pointer to data popped from the queue
 * @return Queue_Status_t - status of function 
 */
Queue_Status_t Queue_Pop(Queue_Instance_Struct_t* pQueueInstance,
                         Package_FrameTypeDef* pPopData)
{
    Queue_Status_t retVal = QUEUE_OK;
    if ((pQueueInstance != NULL) && (pPopData != NULL))
    {
        if (Queue_IsEmpty == false)
        {
            *pPopData            = pQueueInstance->dataFrame[queueInstance->tail];
            pQueueInstance->tail = (pQueueInstance->tail + 1) % QUEUE_MAX_SIZE;
            pQueueInstance->size--;
        }
        else
        {
            pError(QUEUE_EMPTY);
            retVal = QUEUE_EMPTY;
        }
    }
    else
    {
        retVal = QUEUE_FAIL;
    }

    return retVal;
}

/**
 * @brief Function is used to get the available length of the queue
 * @param pQueueInstance pointer to a queue struct
 * @param pAvaibleLength pointer to the number of available length of the queue
 * @return Queue_Status_t - status of function 
 */
Queue_Status_t Queue_GetAvailbleLength(Queue_Instance_Struct_t* pQueueInstance,
                                       uint8_t* pAvailableLength)
{
    Queue_Status_t retVal = QUEUE_OK;

    if(pQueueInstance != NULL && pAvailableLength != NULL)
    {
        *pAvailableLength = QUEUE_MAX_SIZE - pQueueInstance->size;
    }
    else
    {
        retVal = QUEUE_FAIL;
    }

    return retVal;

}

void Queue_UpdateAdressCallbackFunction(Error_CallbackFunction addressCallbackFunction)
{
    pError = addressCallbackFunction;
}