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
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>

 /*******************************************************************************
 * Definitions
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
}Queue_Instance_Struct_t;

/**
 * @brief Status of queue struct
 */
typedef enum Queue_Status {
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_FAIL,
    QUEUE_OK
}Queue_Status_t;


typedef void(*Error_CallbackFunction)(Queue_Status_t);

/*******************************************************************************
* API
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
                          uint16_t sizeElement);

/**
 * @brief Function is used to check queue full or not
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t- status of function
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
 * @param pQueueInstance   pointer to a queue struct
 * @param pPushData        pointer to data needs pushed to the queue
 * @param lengthDataPush   length of data for push to queue struct
 * @return Queue_Status_t  status of function
 */
Queue_Status_t Queue_Push(Queue_Instance_Struct_t* pQueueInstance,
                          uint8_t* pPushData,
                          uint16_t lengthDataPush);

/**
 * @brief Function is used to pop data from queue
 * @param pQueueInstance pointer to a queue struct
 * @param pPopData       pointer to data popped from the queue
 * @param lengthDataPop  the length of data to be pop from the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_Pop(Queue_Instance_Struct_t* pQueueInstance,
                         uint8_t* pPopData,
                         uint16_t lengthDataPop);

/**
 * @brief Function is used to get the available length of the queue
 * @param pQueueInstance pointer to a queue struct
 * @param pAvaibleLength pointer to the number of available length of the queue
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_GetAvailableLength(Queue_Instance_Struct_t* pQueueInstance,
                                       uint8_t* pAvailableLength);

/**
 * @brief Function is used to reset queue
 * @param pQueueInstance pointer to a queue struct
 * @return Queue_Status_t - status of function
 */
Queue_Status_t Queue_Reset(Queue_Instance_Struct_t* pQueueInstance);

/**
 * @brief function get callback function's address
 * @param addressCallbackFunction Error code
 * @return void
 */
Queue_Status_t Queue_UpdateAddressCallbackFunction(Error_CallbackFunction addressCallbackFunction);

#endif /*QUEUE_H_*/

/************************************************************************************
 * EOF
 * *********************************************************************************/