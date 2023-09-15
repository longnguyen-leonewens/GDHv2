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



static FlashSim_HandleTypeDef* pFlashSimHandle;
/******************************************************************************
* * API
******************************************************************************/
/**
  * @brief  Initialized flash simulation.
  *         This function ...
  * @param  void
  * @retval void
  */
FlashSim_StateTypeDef FlashSim_Init(FlashSim_HandleTypeDef* const FlashSimHandle)
{
    FlashSim_StateTypeDef retVal = FLASH_SIM_STATE_OK;



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
FlashSim_StateTypeDef FlashSim_Read(uint32_t startAddress, uint8_t* const buff, uint32_t size)
{
    FlashSim_StateTypeDef retVal = FLASH_SIM_STATE_OK;
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
FlashSim_StateTypeDef FlashSim_Write(uint32_t startAddress, uint8_t* const buff, uint32_t size)
{
    FlashSim_StateTypeDef retVal = FLASH_SIM_STATE_OK;
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
FlashSim_StateTypeDef FlashSim_EraseMultiSector(uint32_t sectorIndex, uint32_t numOfSector)
{
    FlashSim_StateTypeDef retVal = pFlashSimHandle->state;



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



void printfFlashMem(uint16_t startSector, uint16_t endSector)
{
    uint8_t indx, indy;
    uint8_t* data = &s_FlashMem[0][0];
    uint32_t offset = 0;
    printf("Offset      01\t02\t03\t04\t05\t06\t08\t09\t0A\t0B\t0C\t0D\t0E\t0F\n");
    for (uint16_t i = startSector; i < endSector; i++)
    {
        printf("Sector %d\n",i);
        for (indx = 0; indx < 32; indx++)
        {
            printf("%08d",offset);
            offset += 16U;
            for (indy = 0; indy < 16; indy++)
            {
                printf("     %02X\t", *(data + indx * 16 + indy));
            }
            printf("\n");
        }
        printf("\n\n");
    }
}

uint32_t FlashSim_getStartAddr(void)
{
    return ((uint32_t)(&s_FlashMem[0][0]));
}

/******************************************************************************
* * EOF
******************************************************************************/