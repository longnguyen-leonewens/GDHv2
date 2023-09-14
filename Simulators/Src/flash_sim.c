/******************************************************************************
* Include
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "flash_sim.h"



/******************************************************************************
* * Definitions
******************************************************************************/
static uint8_t s_FlashMem[NUMBER_OF_SECTOR][SECTOR_SIZE];



static FlashSim_ErrorCallback s_FlashErrorCallback;



static FlashSim_Handle_Struct_t* pFlashSimHandle;
/******************************************************************************
* * API
******************************************************************************/
/**
  * @brief  Initialized flash simulation.
  *         This function ...
  * @param  void
  * @retval void
  */
FlashSim_State_t FlashSim_Init(FlashSim_Handle_Struct_t* const FlashSimHandle)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;



    if (NULL == FlashSimHandle)
    {
        retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
        FlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
    }
    else
    {
        if (FLASH_SIM_UNLOCKED == FlashSimHandle->lock)
        {
            s_FlashErrorCallback = FlashSimHandle->ErrorCallbackPointer;
            FlashSimHandle->lock = FLASH_SIM_UNLOCKED;
            FlashSimHandle->state = FLASH_SIM_STATE_OK;



            pFlashSimHandle = FlashSimHandle;
            memset(s_FlashMem, 0xFF, FLASH_SIZE);
        }
        else
        {
            retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
        }
    }



    return retVal;
}



/**
  * @brief  Read data from flash
  * @param  startAddress  -  start address in flash
  * @param  buff          -  pointer to buffer where store read data
  * @param  size          -  size of buffer
  * @retval FLASH_SIM_ERROR_t
  */
FlashSim_State_t FlashSim_Read(uint32_t startAddress, uint8_t* const buff, uint32_t size)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
    uint8_t* p_data = (uint8_t*)(startAddress + &s_FlashMem[0][0]);



    if (FLASH_SIM_STATE_OK == pFlashSimHandle->state)
    {
        if ((NULL == buff) || (0 == size))
        {
            retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            if (NULL != s_FlashErrorCallback)
            {
                s_FlashErrorCallback();
            }
        }
        else
        {
            if ((startAddress >= FLASH_START_ADDRESS)\
                && (size < (FLASH_SIZE - (startAddress - FLASH_START_ADDRESS))))
            {
                memcpy(buff, p_data, size);
            }
            else
            {
                retVal = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
                pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
            }
        }
    }



    return retVal;
}



/**
  * @brief  Write data to flash
  * @param  startAddress  -  start address in flash
  * @param  buff          -  pointer to buffer where store data
  * @param  size          -  size of buffer
  * @retval FLASH_SIM_ERROR_t
  */
FlashSim_State_t FlashSim_Write(uint32_t startAddress, uint8_t* const buff, uint32_t size)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
    uint8_t* p_data = (uint8_t*)(startAddress + &s_FlashMem[0][0]);
    uint8_t* buff_temp = buff;



    if (FLASH_SIM_STATE_OK == pFlashSimHandle->state)
    {
        if ((NULL == buff) || (0 == size))
        {
            retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
        }
        else
        {
            if ((startAddress >= FLASH_START_ADDRESS)\
                && (size < (FLASH_SIZE - (startAddress - FLASH_START_ADDRESS))))
            {
                while ((size--) && (FLASH_SIM_STATE_OK == retVal))
                {
                    if (0xFF != *p_data)
                    {
                        retVal = FLASH_SIM_STATE_ERROR_WRITE_TO_INVALID_ADDR;
                    }
                    else
                    {
                        *p_data = *buff_temp;
                        p_data++;
                        buff_temp++;
                    }
                }
            }
            else
            {
                retVal = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
                pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
            }
        }
    }
    return retVal;
}



/**
  * @brief  Erase multi sectors
  * @param  sectorIndex - Index of start sector
  * @param  numOfSector - Number of sector
  * @retval FLASH_SIM_ERROR_ts
  */
FlashSim_State_t FlashSim_EraseMultiSector(uint32_t sectorIndex, uint32_t numOfSector)
{
    FlashSim_State_t retVal = pFlashSimHandle->state;



    if (FLASH_SIM_STATE_OK == retVal)
    {
        if ((NUMBER_OF_SECTOR <= sectorIndex) || ((NUMBER_OF_SECTOR - sectorIndex) <= numOfSector))
        {
            retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
        }
        else
        {
            while (numOfSector--)
            {
                memset(s_FlashMem[sectorIndex], 0xFF, SECTOR_SIZE);
            }
        }
    }



    return retVal;
}



void printfFlashMem(void)
{
    uint8_t indx, indy;
    uint8_t* data = &s_FlashMem[0][0];
    for (indx = 0; indx < 20; indx++)
    {
        for (indy = 0; indy < 10; indy++)
        {
            printf("%d\t", *(data + indx * 10 + indy));
        }
        printf("\n");
    }
}

uint32_t FlashSim_getStartAddr(void)
{
    return ((uint32_t)(&s_FlashMem[0][0]));
}

/******************************************************************************
* * EOF
******************************************************************************/