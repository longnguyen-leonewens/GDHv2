/**
  ******************************************************************************
  * @file    fpt_emb_queue.h
  * @author  Leo Newens (LongNDT5)
  * @date    May 18, 2023
  * @brief   Header file for queue functions
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
#ifndef QUEUE_H_
#define QUEUE_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/**
 * @brief Queue control struct
 */
typedef struct __Queue_Struct
{
    uint32_t elementCount;   /*< Count of queue's elements */
    uint32_t elementSize;    /*< Size of each element */
    uint32_t queueFront;     /*< Points to the front (head) of the queue storage area. */
    uint32_t queueBack;      /*< Points to the back (tail) of the queue storage area */
    uint32_t queueSize;      /*< Size of queue */
    uint8_t *queueBuffer;    /*< Data memory */
}Queue_TypeDef;

/**
 * @brief Queue errors enumeration
 */
typedef enum __Queue_Status_Enum
{
    QUEUE_OK,
    QUEUE_ERROR_FULL,
    QUEUE_ERROR_EMPTY,
    QUEUE_BUSY
}Queue_StatusTypeDef;

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
                const uint32_t queueSize);

/**
 * @brief  Enqueue(insert) data into queue
 * @param  pQueue: pointer to a queue struct
 * @param  pData: pointer to the data to be inserted
 * @param  numOfElements: number of elements to enqueue
 * @retval Status
 */
Queue_StatusTypeDef Queue_Enqueue(Queue_TypeDef *pQueue,\
                                  const uint8_t *pData,\
                                  const uint32_t numOfElements);

/**
 * @brief  Dequeue data from queue
 * @param  pQueue: pointer to a queue struct
 * @param  pData: pointer to the data that store the data to be dequeued
 * @param  numOfElements: number of elements to dequeue
 * @retval Status
 */
Queue_StatusTypeDef Queue_Dequeue(Queue_TypeDef *pQueue,\
                                  uint8_t *pBuffer,\
                                  const uint32_t numOfElements);


/**
 * @brief  Check if a queue is full
 * @param  pQueue: Pointer to a queue struct
 * @retval None
 */
bool Queue_IsFull(const Queue_TypeDef *pQueue);

/**
 * @brief  Check if a queue is empty
 * @param  pQueue: Pointer to a queue struct
 * @retval None
 */
bool Queue_IsEmpty(const Queue_TypeDef *pQueue);

/**
 * @brief  Increase the index of the back (used when data is enqueued by other means)
 * @param  pQueue: Pointer to a queue struct
 * @param  numOfElements: Number of elements to push, or was pushed
 * @retval None
 */
Queue_StatusTypeDef Queue_PushIndex(Queue_TypeDef *pQueue, const uint32_t numOfElements);

/**
 * @brief  Increase the index of the front (used when data is dequeued by other means)
 * @param  pQueue: Pointer to a queue struct
 * @param  numOfElements: Number of elements to pop, or was popped
 * @retval None
 */
Queue_StatusTypeDef Queue_PopIndex(Queue_TypeDef *pQueue, const uint32_t numOfElements);

/**
 * @brief  Peek inside the front of queue
 * @param  pQueue; pointer to a queue struct
 * @retval Pointer the the first data byte of front
 */
const uint8_t *Queue_PeekFront(const Queue_TypeDef *pQueue);

/**
 * @brief  Peek inside the back of queue
 * @param  pQueue; pointer to a queue struct
 * @retval Pointer the the first data byte of back
 */
const uint8_t *Queue_PeekBack(const Queue_TypeDef *pQueue);

#endif /* QUEUE_H_ */

/******************************************************************************
 * End of file
 ******************************************************************************/
