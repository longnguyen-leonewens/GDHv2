/**
 * @file queue.c
 * @author HungDH14
 * @brief J0B 4- QUEUE
 * @version 0.1
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"
#include "assert.h"
/*******************************************************************************
* Definitions
******************************************************************************/

#define IS_VALID_POINTER(ptr)   (NULL != ptr)

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
 * @param bufferQueue    buffer used as a queue
 * @param sizeQueue      number of element of queue
 * @param sizeElement    size of data element
 * @return Queue_Status_t- status of function
 */
Queue_Status_t Queue_Init(Queue_Instance_Struct_t* pQueueInstance,
                          uint8_t* bufferQueue,
                          uint8_t sizeQueue,
                          uint16_t sizeElement)
{
    ASSERT(IS_VALID_POINTER(pQueueInstance) && IS_VALID_POINTER(bufferQueue));

    pQueueInstance->pQueueElement = bufferQueue;
    pQueueInstance->elementSize   = sizeElement;
    pQueueInstance->queueSize     = sizeQueue;
    pQueueInstance->levelQueue    = 0;
    pQueueInstance->head          = 0;
    pQueueInstance->tail          = 0;

    return QUEUE_OK;
}

/**
 * @brief Function is used to check queue full or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t- status of function
 */
Queue_Status_t Queue_IsFull(Queue_Instance_Struct_t* pQueueInstance)
{
    Queue_Status_t retVal = QUEUE_OK;
    ASSERT(IS_VALID_POINTER(pQueueInstance));

    if (pQueueInstance->levelQueue == pQueueInstance->queueSize)
    {
        retVal = QUEUE_FULL;
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
    ASSERT(IS_VALID_POINTER(pQueueInstance));

    if (pQueueInstance->levelQueue == 0)
    {
        retVal = QUEUE_EMPTY;
    }

    return retVal;
}

/**
 * @brief Function is used to push data to queue
 * @param pQueueInstance   pointer to a queue struct
 * @param pPushData        pointer to data needs pushed to the queue
 * @param lengthDataPush   length of data for push to queue struct
 * @return Queue_Status_t  status of function
 */
Queue_Status_t Queue_Push(Queue_Instance_Struct_t* pQueueInstance,
                          uint8_t* pPushData,
                          uint16_t lengthDataPush)
{
    Queue_Status_t retVal = QUEUE_OK;
    ASSERT(IS_VALID_POINTER(pQueueInstance) && IS_VALID_POINTER(pPushData));

    if (pQueueInstance->levelQueue != pQueueInstance->queueSize)
    {
        memcpy(&(pQueueInstance->pQueueElement[pQueueInstance->head]),pPushData,lengthDataPush);
        pQueueInstance->head = (pQueueInstance->head + pQueueInstance->elementSize) % (pQueueInstance->queueSize * pQueueInstance->elementSize);
        pQueueInstance->levelQueue++;
    }
    else
    {
        pError(QUEUE_FULL);
        retVal = QUEUE_FULL;
    }

    return retVal;
}

/**
 * @brief Function is used to pop data from queue
 * @param pQueueInstance pointer to a queue struct
 * @param pPopData       pointer to data popped from the queue
 * @param lengthDataPop  the length of data to be pop from the queue
 * @return Queue_Status_t - status of function 
 */
Queue_Status_t Queue_Pop(Queue_Instance_Struct_t* pQueueInstance,
                         uint8_t* pPopData,
                         uint16_t lengthDataPop)
{
    Queue_Status_t retVal = QUEUE_OK;
    ASSERT(IS_VALID_POINTER(pQueueInstance) && IS_VALID_POINTER(pPopData));

    if (pQueueInstance->levelQueue != 0)
    {
        memcpy(pPopData,&(pQueueInstance->pQueueElement[pQueueInstance->tail]),lengthDataPop);
        memset(&(pQueueInstance->pQueueElement[pQueueInstance->tail]),0,pQueueInstance->elementSize);
        pQueueInstance->tail = (pQueueInstance->tail + pQueueInstance->elementSize) % (pQueueInstance->queueSize * pQueueInstance->elementSize);
        pQueueInstance->levelQueue--;
    }
    else
    {
        pError(QUEUE_EMPTY);
        retVal = QUEUE_EMPTY;
    }

    return retVal;
}

/**
 * @brief Function is used to get the available length of the queue
 * @param pQueueInstance pointer to a queue struct
 * @param pAvaibleLength pointer to the number of available length of the queue
 * @return Queue_Status_t - status of function 
 */
Queue_Status_t Queue_GetAvailableLength(Queue_Instance_Struct_t* pQueueInstance,
                                       uint8_t* pAvailableLength)
{
    Queue_Status_t retVal = QUEUE_OK;
    ASSERT(IS_VALID_POINTER(pQueueInstance) && IS_VALID_POINTER(pAvailableLength));

    *pAvailableLength = pQueueInstance->queueSize - pQueueInstance->levelQueue;

    return retVal;

}

/**
 * @brief Function is used to reset queue
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t - status of function 
 */
Queue_Status_t Queue_Reset(Queue_Instance_Struct_t* pQueueInstance)
{
    ASSERT(IS_VALID_POINTER(pQueueInstance));

    pQueueInstance->head = 0;
    pQueueInstance ->tail = 0;
    pQueueInstance->levelQueue = 0;
    memset(&(pQueueInstance->pQueueElement[pQueueInstance->tail]),0,(pQueueInstance->elementSize)*(pQueueInstance->queueSize));

    return QUEUE_OK;
}

/**
 * @brief function get callback function's address
 * @param addressCallbackFunction Error code
 * @return void
 */
Queue_Status_t Queue_UpdateAddressCallbackFunction(Error_CallbackFunction addressCallbackFunction)
{
    pError = addressCallbackFunction;
    return QUEUE_OK;
}

/************************************************************************************
 * EOF
 * *********************************************************************************/

