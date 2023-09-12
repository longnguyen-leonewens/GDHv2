/**
  ******************************************************************************
  * @file   queue.h
  * @author HungDH14
  * @brief  J0B 4- QUEUE
  * @date   2023-09-11
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023
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
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/**
 * number element of queue
*/
#define QUEUE_MAX_SIZE (4U)

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
    QUEUE_FAIL,
    QUEUE_OK
}Queue_Status_t;

/**
 * @brief calback function for error
 */
typedef void(*Error_CallbackFunction)(Queue_Status_t);

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

/**
 * @brief Function is used to initialize for Queue struct
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
Queue_Status_t Queue_Push(Queue_Instance_Struct_t* pQueueInstance,
                          Package_FrameTypeDef* pPushData);

/**
 * @brief Function is used to pop data from queue
 * @param pQueueInstance pointer to a queue struct
 * @param pPopData pointer to data popped from the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_Pop(Queue_Instance_Struct_t* pQueueInstance,
                         Package_FrameTypeDef* pPopData);

/**
 * @brief Function is used to get the available length of the queue
 * @param queueInstance pointer to a queue struct
 * @param avaibleLength pointer to the number of available length of the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_GetAvailbleLength(Queue_Instance_Struct_t* pQueueInstance,
                                       uint8_t* pAvailableLength);

#endif /*QUEUE_H_*/

/******************************************************************************
 * EOF
 ******************************************************************************/