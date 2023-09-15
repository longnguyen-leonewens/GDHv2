/**
  ******************************************************************************
  * @file queue.h
 * @author HungDH14
 * @brief J0B 4- QUEUE
 * @version 0.1
 * @date 2023-09-11
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
#ifndef _QUEUE_H_
#define _QUEUE_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include <stdint.h>
#include "def.h"
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/
/**
  * @brief queue control struct
  */
typedef struct Queue_Instance
{
    uint8_t  *pQueueElement;
    uint16_t elementSize;
    uint8_t  queueSize;
    uint8_t  levelQueue;
    uint8_t  head;
    uint8_t  tail;
}Queue_TypeDef;

/**
 * @brief Status of queue struct
 */
typedef enum Queue_Status {
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_FAIL,
    QUEUE_OK
}Queue_StatusTypeDef;


typedef void(*Error_CallbackFunction)(Queue_StatusTypeDef);

/******************************************************************************
 * EXPORTED FUNCTIONS PROTOTYPES
 ******************************************************************************/

/**
 * @brief Function is used to initialize for Queue struct
 * @param pQueueInstance pointer to a queue struct
 * @param bufferQueue    buffer used as a queue
 * @param sizeQueue      number of element of queue
 * @param sizeElement    size of data element
 * @return Queue_StatusTypeDef- status of function
 */
Queue_StatusTypeDef Queue_Init(Queue_TypeDef* pQueueInstance,
                          uint8_t* bufferQueue,
                          uint8_t sizeQueue,
                          uint16_t sizeElement);

/**
 * @brief Function is used to check queue full or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_StatusTypeDef- status of function
 */
Queue_StatusTypeDef Queue_IsFull(Queue_TypeDef* pQueueInstance);

/**
 * @brief Function is used to check queue empty or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_StatusTypeDef - status of function
 */
Queue_StatusTypeDef Queue_IsEmpty(Queue_TypeDef* pQueueInstance);

/**
 * @brief Function is used to push data to queue
 * @param pQueueInstance   pointer to a queue struct
 * @param pPushData        pointer to data needs pushed to the queue
 * @param lengthDataPush   length of data for push to queue struct
 * @return Queue_StatusTypeDef  status of function
 */
Queue_StatusTypeDef Queue_Push(Queue_TypeDef* pQueueInstance,
                          uint8_t* pPushData,
                          uint16_t lengthDataPush);

/**
 * @brief Function is used to pop data from queue
 * @param pQueueInstance pointer to a queue struct
 * @param pPopData       pointer to data popped from the queue
 * @param lengthDataPop  the length of data to be pop from the queue
 * @return Queue_StatusTypeDef - status of function
 */
Queue_StatusTypeDef Queue_Pop(Queue_TypeDef* pQueueInstance,
                         uint8_t* pPopData,
                         uint16_t lengthDataPop);

/**
 * @brief Function is used to get the available length of the queue
 * @param pQueueInstance pointer to a queue struct
 * @param pAvaibleLength pointer to the number of available length of the queue
 * @return Queue_StatusTypeDef - status of function
 */
Queue_StatusTypeDef Queue_GetAvailableLength(Queue_TypeDef* pQueueInstance,
                                       uint8_t* pAvailableLength);

/**
 * @brief Function is used to reset queue
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_StatusTypeDef - status of function
 */
Queue_StatusTypeDef Queue_Reset(Queue_TypeDef* pQueueInstance);

/**
 * @brief function get callback function's address
 * @param addressCallbackFunction Error code
 * @return void
 */
Queue_StatusTypeDef Queue_UpdateAddressCallbackFunction(Error_CallbackFunction addressCallbackFunction);

#endif /*QUEUE_H_*/

/************************************************************************************
 * EOF
 * *********************************************************************************/