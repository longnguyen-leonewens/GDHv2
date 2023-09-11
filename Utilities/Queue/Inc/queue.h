/**
  ******************************************************************************
  * @file    queue.h
  * @author  HungDH14
  * @date    11st Sep 2027
  * @brief   JOB 4: Create queue and store data
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
#include "gyropacket.h"
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/**
 * @brief queue control struct
 */
typedef struct Queue_Instance{
    Package_FrameTypeDef dataFrame[QUEUE_MAX_SIZE];
    uint8_t size;
    uint8_t head;
    uint8_t tail;
}Queue_Instance_Struct_t;

/**
 * @brief Status of queue struct
 */
typedef enum Queue_Status{
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_OK
}Queue_Status_t;

/**
 * @brief calback function for error
 */
typedef void(*Error_callback_t)(Queue_Status_t);

/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/
#define QUEUE_MAX_SIZE (4U)
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
 * @brief Function is used to initilize for Queue struct
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t -status of function
 */
Queue_Status_t Queue_Init(Queue_Instance_Struct_t* pQueueInstance);

/**
 * @brief Function is used to check queue full or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t -status of function
 */
Queue_Status_t Queue_IsFull(Queue_Instance_Struct_t* pQueueInstance);

/**
 * @brief Function is used to check queue empty or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_IsEmpty(Queue_Instance_Struct_t* pQueueInstance);

/**
 * @brief Function is used to push data to queue
 * @param pQueueInstance pointer to a queue struct
 * @param pPushData pointer to data needs pushed to the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_Push(Queue_Instance_Struct_t* pQueueInstance, Package_FrameTypeDef* pPushData);

/**
 * @brief Function is used to pop data from queue
 * @param queueInstance pointer to a queue struct
 * @param popData pointer to data popped from the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_Pop(Queue_Instance_Struct_t* queueInstance, Package_FrameTypeDef* popData);

/**
 * @brief Function is used to get the available length of the queue
 * @param queueInstance pointer to a queue struct
 * @param avaibleLength pointer to the number of available length of the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_GetAvailableLength(Queue_Instance_Struct_t* queueInstance, uint8_t* availableLength);

#endif /* QUEUE_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/