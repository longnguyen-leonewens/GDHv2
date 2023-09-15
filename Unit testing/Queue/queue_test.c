#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

/*******************************************************************************
* Definitions
******************************************************************************/
#define QUEUE_SIZE              (4U)
#define ELEMENT_SIZE            (3U)
#define LENGTH_DATA_TEST_1_FAIL (0U)
#define LENGTH_DATA_TEST_2_FAIL (ELEMENT_SIZE+1)

/*******************************************************************************
* Prototypes
******************************************************************************/
/**
 * @brief The function is used to test function queue init
 * 
 */
static void Test_Queue_Init(void);

/**
 * @brief The function is used to test function Queue_IsEmty
 * 
 */
static void Test_Queue_IsEmpty(void);

/**
 * @brief The function is used to test function Queue_IsFull
 * 
 */
static void Test_Queue_IsFull(void);

/**
 * @brief The function is used to test function Queue_Push
 * 
 */
static void Test_Queue_Push(void);

/**
 * @brief The function is used to test function Queue_Pop
 * 
 */
static void Test_Queue_Pop(void);

/**callback function used to testing*/
int callbackFunctionforTest(void);

/**
 * @brief The function is used to test function Queue_GetAvailableLength
 * 
 */
static void Test_Queue_GetAvailableLength(void);

/**
 * @brief The function is used to test function Queue_Reset
 *
 */
static void Test_Queue_Reset(void);

/*******************************************************************************
* Variables
******************************************************************************/

static Queue_TypeDef queueTest;
static Queue_TypeDef expectedValue;
static uint8_t bufferTest[40];

/*******************************************************************************
* Code
******************************************************************************/

int main_test_queue(void)
{
    Test_Queue_Init();
    Test_Queue_IsEmpty();
    Test_Queue_IsFull();
    Test_Queue_Push();
    Test_Queue_Pop();
    Test_Queue_GetAvailableLength();
    return 0;
}

/**
 * @brief The function is used to test function queue init
 * 
 */
static void Test_Queue_Init(void)
{
    /*prepare parameter input*/
    Queue_Init(&queueTest,bufferTest, QUEUE_SIZE, ELEMENT_SIZE);

    if (queueTest.pQueueElement ==  bufferTest && queueTest.head == 0                   && queueTest.tail == 0 && 
        queueTest.queueSize == QUEUE_SIZE      && queueTest.elementSize == ELEMENT_SIZE && queueTest.levelQueue == 0)
    {
        printf("Function Queue_Init pass\n");
    }
    else
    {
        printf("Function Queue_Init fail\n");
    }
}

/**
 * @brief The function is used to test function Queue_IsEmty
 * 
 */
static void Test_Queue_IsEmpty(void)
{
    Queue_Init(&queueTest,bufferTest, QUEUE_SIZE, ELEMENT_SIZE);
    Queue_StatusTypeDef status = Queue_IsEmpty(&queueTest);
    if(status == QUEUE_EMPTY)
    {
        printf("Function Queue_IsEmpty pass\n");
    }
    else
    {
        printf("Function Queue_IsEmpty fail\n");
    }
}

/**
 * @brief The function is used to test function Queue_IsFull
 * 
 */
static void Test_Queue_IsFull(void)
{
    /*prepare parameter input*/
    Queue_Init(&queueTest,bufferTest, QUEUE_SIZE,ELEMENT_SIZE);
    queueTest.levelQueue = QUEUE_SIZE;
    Queue_StatusTypeDef status = Queue_IsFull(&queueTest);


    if(status == QUEUE_FULL)
    {
        printf("Function Queue_IsFull pass\n");
    }
    else
    {
        printf("Function Queue_IsFull fail\n");    
    }
}

/**
 * @brief The function is used to test function Queue_Push
 * 
 */
static void Test_Queue_Push(void)
{
    uint8_t i      = 0;
    uint8_t k      = 0;
    bool valueTest = true;
    Queue_StatusTypeDef statusReturn;
    uint8_t dataPush[4][3] = { {1,2,3},
                               {4,5,6},
                               {7,8,9},
                               {10,11,12} };

    Queue_Init(&queueTest,bufferTest, QUEUE_SIZE, ELEMENT_SIZE);
    Queue_UpdateAddressCallbackFunction(&callbackFunctionforTest);

    /*Check param fail lengthData*/
    if (Queue_Push(&queueTest, (uint8_t*)&dataPush[i], LENGTH_DATA_TEST_1_FAIL) != QUEUE_FAIL || Queue_Push(&queueTest, (uint8_t*)&dataPush[i], LENGTH_DATA_TEST_1_FAIL) != QUEUE_FAIL)
    {
        valueTest = false;
    }

    for(i=0;i<4;i++)
    {
        Queue_Push(&queueTest, (uint8_t*)&dataPush[i],sizeof(dataPush[i]));
    }
    for (i = 0;i < QUEUE_SIZE;i++)
    {
        for (k = 0;k < ELEMENT_SIZE;k++)
        {
            if (queueTest.pQueueElement[i*ELEMENT_SIZE + k] != dataPush[i][k])
            {
                valueTest = false;
            }
        }
    }

    /*test for queue full*/
    queueTest.levelQueue = QUEUE_SIZE;
    statusReturn = Queue_Push(&queueTest, (uint8_t*)&dataPush[i], sizeof(dataPush[i]));
    if (statusReturn != QUEUE_FULL)
    {
        valueTest = false;
    }

    if (valueTest == false)
    {
        printf("Function Queue_Push fail\n");
    }
    else
    {
        printf("Function Queue_Push pass\n");
    }

}


/**
 * @brief The function is used to test function Queue_Pop
 * 
 */
static void Test_Queue_Pop(void)
{
    uint8_t i = 0;
    uint8_t k = 0;
    uint8_t dataPop[QUEUE_SIZE][ELEMENT_SIZE] = { {0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF} };
    uint8_t expected[QUEUE_SIZE*ELEMENT_SIZE] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
 
    bool valueTest = true;
    Queue_StatusTypeDef statusReturn;

    Queue_Init(&queueTest, bufferTest, QUEUE_SIZE, ELEMENT_SIZE);
    Queue_UpdateAddressCallbackFunction(&callbackFunctionforTest);

    /*Check param fail lengthData*/
    if(Queue_Pop(&queueTest, (uint8_t*)&dataPop,LENGTH_DATA_TEST_1_FAIL) != QUEUE_FAIL || Queue_Pop(&queueTest, (uint8_t*)&dataPop, LENGTH_DATA_TEST_2_FAIL) != QUEUE_FAIL)
    {
        valueTest = false;
    }
    /*Push value to queue*/
    for (i = 0;i < QUEUE_SIZE*ELEMENT_SIZE;i++)
    {
        queueTest.pQueueElement[i] = expected[i];
    }
    queueTest.levelQueue = QUEUE_SIZE;

    /*check queue pop with true data*/
    for (i = 0;i < QUEUE_SIZE;i++)
    {
        Queue_Pop(&queueTest, (uint8_t*)&dataPop[i], ELEMENT_SIZE);
    }
    for (i = 0;i < ELEMENT_SIZE;i++)
    {
        for (k = 0;k < QUEUE_SIZE;k++)
        {
            if (dataPop[i][k] != expected[i*ELEMENT_SIZE +k])
            {
                valueTest = false;
            }
        }
    }
    /*check with queue empty*/
    queueTest.levelQueue = 0;
    statusReturn = Queue_Pop(&queueTest, (uint8_t*)&dataPop[i], ELEMENT_SIZE);
    if (statusReturn != QUEUE_EMPTY)
    {
        valueTest = false;
    }

    if (valueTest == false)
    {
        printf("Function Queue_Pop fail\n");
    }
    else
    {
        printf("Function Queue_Pop pass\n");
    }
}


/**
 * @brief The function is used to test function Queue_GetAvailableLength
 * 
 */
static void Test_Queue_GetAvailableLength(void)
{
    uint8_t availableLength;
    uint8_t expectedAvailableLength;
    bool valueTest = true;

    Queue_Init(&queueTest, bufferTest, QUEUE_SIZE, ELEMENT_SIZE);
    queueTest.levelQueue = 2;
    expectedAvailableLength = QUEUE_SIZE - queueTest.levelQueue;

    availableLength = Queue_GetAvailableLength(&queueTest, &availableLength);

    if (availableLength != expectedAvailableLength)
    {
        valueTest = false;
    }
    if (valueTest = false)
    {
        printf("Function Queue_GetAvailableLength fail\n");
    }
    else
    {
        printf("Function Queue_GetAvailableLength pass\n");
    }
}

static void Test_Queue_Reset(void)
{
    bool valueTest = true;
    uint16_t i;

    Queue_Reset(&queueTest);
    if (queueTest.tail != 0 || queueTest.head != 0 || queueTest.levelQueue != 0)
    {
        valueTest = false;
    }
    for (i = 0;i < QUEUE_SIZE*ELEMENT_SIZE;i++)
    {
        if (queueTest.pQueueElement[i] != 0)
        {
            valueTest = false;
        }
    }
    if (valueTest = false)
    {
        printf("Function Queue_Reset fail\n");
    }
    else
    {
        printf("Function Queue_Reset pass\n");
    }
}

/**callback function used to testing*/
int callbackFunctionforTest(void)
{
    return 0;
}

