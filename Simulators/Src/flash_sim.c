
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

static p_FlashSim_ErrorCallback s_FlashErrorCallback;

static FlashSim_Handle_Struct_t * s_p_FlashSimHandle;
/******************************************************************************
* * API
******************************************************************************/
/**
  * @brief  Initialized flash simulation.
  *         This function ...
  * @param  void
  * @retval void
  */
FlashSim_State_t FlashSim_Init(FlashSim_Handle_Struct_t * const FlashSimHandle)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;

    if(NULL == FlashSimHandle)
    {
        retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
        FlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
    }
    else
    {
        if (FLASH_SIM_UNLOCKED == FlashSimHandle->lock)
        {
            if ( 0 < FlashSimHandle->size)
            {
                s_FlashErrorCallback  = FlashSimHandle->ErrorCallbackPointer;
                FlashSimHandle->lock  = FLASH_SIM_UNLOCKED;
                FlashSimHandle->state = FLASH_SIM_STATE_OK;

                s_p_FlashSimHandle = FlashSimHandle;
                memset(s_FlashMem, 0xFF, FlashSimHandle->size);
            }
            else
            {
                retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            }

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
FlashSim_State_t FlashSim_Read(uint32_t startAddress, uint8_t * const buff, uint32_t size)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
    uint8_t * p_data = (uint8_t *)(startAddress+&s_FlashMem[0][0]);

    if( FLASH_SIM_STATE_OK == s_p_FlashSimHandle->state )
    {
        if ((NULL == buff) || (0 == size))
        {
            retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            s_p_FlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            if (NULL != s_FlashErrorCallback)
            {
                s_FlashErrorCallback();
            }
        }
        else
        {
            if ((startAddress >= s_p_FlashSimHandle->FlashStartAddress)\
                && (size < (s_p_FlashSimHandle->size - (startAddress - s_p_FlashSimHandle->FlashStartAddress))))
            {
               memcpy(buff, p_data, size);
            }
            else
            {
                retVal = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
                s_p_FlashSimHandle->state = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
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
FlashSim_State_t FlashSim_Write(uint32_t startAddress, uint8_t * const buff, uint32_t size)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
    uint8_t * p_data = (uint8_t *)(startAddress+&s_FlashMem[0][0]);
    uint8_t * buff_temp = buff;

    if (FLASH_SIM_STATE_OK == s_p_FlashSimHandle->state)
    {
        if((NULL == buff) || (0 == size))
        {
            retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            s_p_FlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
        }
        else
        {
            if ((startAddress >= s_p_FlashSimHandle->FlashStartAddress)\
                && (size < (s_p_FlashSimHandle->size - (startAddress - s_p_FlashSimHandle->FlashStartAddress))))
            {
                while((size--) && (FLASH_SIM_STATE_OK == retVal))
                {
                    if (0xFF != *p_data)
                    {
                        retVal = FLASH_SIM_STATE_ERROR_WRITE_TO_INVALID_ADDR;
                    }
                    else
                    {
                        *p_data = *buff_temp;
                        p_data      ++;
                        buff_temp   ++;
                    }
                }
            }
            else
            {
                retVal = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
                s_p_FlashSimHandle->state = FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION;
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
    FlashSim_State_t retVal = s_p_FlashSimHandle->state;

    if( FLASH_SIM_STATE_OK == retVal )
    {
        if ((NUMBER_OF_SECTOR <= sectorIndex) || ((NUMBER_OF_SECTOR-sectorIndex) <= numOfSector))
        {
            retVal = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
            s_p_FlashSimHandle->state = FLASH_SIM_STATE_ERROR_PARAM_INVALID;
        }
        else
        {
            while(numOfSector --)
            {
                memset(s_FlashMem[sectorIndex], 0xFF, SECTOR_SIZE);
            }
        }
    }

    return retVal;
}

/******************************************************************************
* * EOF
******************************************************************************/
