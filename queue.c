/**
  ******************************************************************************
  * @file    queue.c
  * @author  Leo Newens (LongNDT5)
  * @version V1.0
  * @date    July 5th 2023
  * @brief   Implementation for queue library
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
#include "queue.h"
#include <string.h>
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

/******************************************************************************
 * PRIVATE FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Initialize queue struct
 * @param  pQueue: pointer to a queue struct
 * @param  dataBuffer: data buffer of queue
 * @param  elementSize: size of each elements in queue
 * @param  queueSize: size of the queue (number of elements)
 * @retval None
 */
void Queue_Init(Queue_TypeDef *pQueue,\
                uint8_t *dataBuffer,\
                const uint32_t elementSize,\
                const uint32_t queueSize)
{
    pQueue->queueBuffer = dataBuffer;
    pQueue->elementSize = elementSize;
    pQueue->queueSize   = queueSize;
    pQueue->queueFront  = 0x00;
    pQueue->queueBack   = 0x00;
    memset(pQueue->queueBuffer, 0x00, pQueue->elementSize * pQueue->queueSize);
}

/**
 * @brief  Enqueue(insert) data into queue
 * @param  pQueue: pointer to a queue struct
 * @param  pData: pointer to the data to be inserted
 * @param  numOfElements: number of elements to enqueue
 * @retval Status
 */
Queue_StatusTypeDef Queue_Enqueue(Queue_TypeDef *pQueue,\
                                  const uint8_t *pData,\
                                  const uint32_t numOfElements)
{
    uint32_t count;
    uint32_t bytes;
    uint32_t bufferIndex;
    Queue_StatusTypeDef enqueueStatus = QUEUE_OK;
    if ((pQueue->elementCount + numOfElements) > pQueue->queueSize)
    {
        enqueueStatus = QUEUE_ERROR_FULL;
    }
    else
    {
        /* Place data in buffer */
        for (count = 0; count < numOfElements; count++)
        {
            for(bytes = 0; bytes < pQueue->elementSize; bytes++)
            {
                bufferIndex = count * pQueue->elementSize + bytes;
                pQueue->queueBuffer[bufferIndex] = pData[bufferIndex];
            }
            pQueue->elementCount++;
            pQueue->queueBack = (pQueue->queueBack + 1U) % pQueue->queueSize;
        }
    }
    return enqueueStatus;
}

/**
 * @brief  Dequeue data from queue
 * @param  pQueue: pointer to a queue struct
 * @param  pData: pointer to the data that store the data to be dequeued
 * @param  numOfElements: number of elements to dequeue
 * @retval Status
 */
Queue_StatusTypeDef Queue_Dequeue(Queue_TypeDef *pQueue,\
                                  uint8_t *pBuffer,\
                                  const uint32_t numOfElements)
{
    uint32_t count;
    uint32_t bytes;
    uint32_t bufferIndex;
    Queue_StatusTypeDef dequeueStatus = QUEUE_OK;
    if (numOfElements > pQueue->elementCount)
    {
        dequeueStatus = QUEUE_ERROR_EMPTY;
    }
    else
    {
        for (count = 0; count < numOfElements; count++)
        {
            for(bytes = 0; bytes < pQueue->elementSize; bytes++)
            {
                bufferIndex = count * pQueue->elementSize + bytes;
                pBuffer[bufferIndex] = pQueue->queueBuffer[bufferIndex];
            }
            pQueue->elementCount--;
            pQueue->queueFront = (pQueue->queueFront + 1U) % pQueue->queueSize;
        }
    }
    return dequeueStatus;
}

/**
 * @brief  Check if a queue is empty
 * @param  pQueue: Pointer to a queue struct
 * @retval None
 */
bool Queue_IsEmpty(const Queue_TypeDef *pQueue)
{
    bool checkQueue = false;
    if (pQueue->elementCount == 0)
    {
        checkQueue = true;
    }
    return checkQueue;
}

/**
 * @brief  Check if a queue is full
 * @param  pQueue: Pointer to a queue struct
 * @retval None
 */
bool Queue_IsFull(const Queue_TypeDef *pQueue)
{
    bool checkQueue = false;
    if (pQueue->elementCount == pQueue->queueSize)
    {
        checkQueue = true;
    }
    return checkQueue;
}

/**
 * @brief  Increase the index of the back (used when data is enqueued by other means)
 * @param  pQueue: Pointer to a queue struct
 * @param  numOfElements: Number of elements to push, or was pushed
 * @retval None
 */
Queue_StatusTypeDef Queue_PushIndex(Queue_TypeDef *pQueue, const uint32_t numOfElements)
{
    Queue_StatusTypeDef pushStatus = QUEUE_OK;
    if ((pQueue->elementCount + numOfElements) > pQueue->queueSize)
    {
        pushStatus = QUEUE_ERROR_FULL;
    }
    else
    {
        pQueue->elementCount += numOfElements;
        pQueue->queueBack = (pQueue->queueBack + numOfElements) % pQueue->queueSize;
    }
    return pushStatus;
}

/**
 * @brief  Increase the index of the front (used when data is dequeued by other means)
 * @param  pQueue: Pointer to a queue struct
 * @param  numOfElements: Number of elements to pop, or was popped
 * @retval None
 */
Queue_StatusTypeDef Queue_PopIndex(Queue_TypeDef *pQueue, const uint32_t numOfElements)
{
    Queue_StatusTypeDef popStatus = QUEUE_OK;
    if (numOfElements > pQueue->elementCount)
    {
        popStatus = QUEUE_ERROR_EMPTY;
    }
    else
    {
        pQueue->elementCount -= numOfElements;
        pQueue->queueFront = (pQueue->queueFront + numOfElements) % pQueue->queueSize;
    }
    return popStatus;
}

/**
 * @brief  Peek inside the front of queue
 * @param  pQueue; pointer to a queue struct
 * @retval Pointer the the first data byte of front
 */
const uint8_t *Queue_PeekFront(const Queue_TypeDef *pQueue)
{
    const uint8_t *pPeek = NULL;
    pPeek = &pQueue->queueBuffer[pQueue->queueFront * pQueue->elementSize];
    return pPeek;
}

/**
 * @brief  Peek inside the back of queue
 * @param  pQueue; pointer to a queue struct
 * @retval Pointer the the first data byte of back
 */
const uint8_t *Queue_PeekBack(const Queue_TypeDef *pQueue)
{
    const uint8_t *pPeek = NULL;
    pPeek = &pQueue->queueBuffer[pQueue->queueBack * pQueue->elementSize];
    return pPeek;
}

/******************************************************************************
 * End of file
 ******************************************************************************/
