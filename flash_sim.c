/**
  ******************************************************************************
  * @file    flash_sim.c
  * @author  VinhDD1
  * @version
  * @date
  * @brief
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
#include <stdio.h>
#include <string.h>
#include "flash_sim.h"
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
static uint8_t s_FlashMem[NUMBER_OF_SECTOR][SECTOR_SIZE];

static FlashSim_ErrorCallback s_FlashErrorCallback;

static FlashSim_HandleTypeDef* pFlashSimHandle;
/******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES
 ******************************************************************************/

/******************************************************************************
 * PRIVATE FUNCTIONS
 ******************************************************************************/

/**
  * @brief  Initialized flash simulation.
  *         This function init Flash simulation
  * @param  FlashSimHandle pointer to init struct
  * @retval void
  */
FlashSim_StateTypeDef FlashSim_Init(FlashSim_HandleTypeDef* const FlashSimHandle)
{
    FlashSim_StateTypeDef retVal = FLASH_SIM_STATE_OK;
    /* check parameter*/
    if (NULL == FlashSimHandle)
    {
        retVal = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
    }
    else
    {
        if (FLASH_SIM_UNLOCKED == FlashSimHandle->lock)
        {
            /* Set flash state is busy */
            FlashSimHandle->state = FLASH_SIM_STATE_BUSY;
            s_FlashErrorCallback = FlashSimHandle->ErrorCallbackPointer;
            FlashSimHandle->lock = FLASH_SIM_LOCKED;

            pFlashSimHandle = FlashSimHandle;
            pFlashSimHandle->lock = FLASH_SIM_LOCKED;
            /* Clear all flash */
            memset(s_FlashMem, 0xFF, FLASH_SIZE);
            /* Set flash state is OK */
            FlashSimHandle->state = FLASH_SIM_STATE_OK;
        }
        else
        {
            retVal = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
        }
    }

    return retVal;
}

/**
  * @brief  Read data from flash
  * @param  startAddress  -  start address in flash
  * @param  buff          -  pointer to buffer where store read data
  * @param  size          -  size of buffer
  * @retval FlashSim_StateTypeDef
  */
FlashSim_StateTypeDef FlashSim_Read(uint64_t startAddress, uint8_t* const buff, uint32_t size)
{
    FlashSim_StateTypeDef retVal = FLASH_SIM_STATE_OK;
    uint8_t* p_data = (uint8_t*)(startAddress + &s_FlashMem[0][0]);

    /* Check parameter */
    if (FLASH_SIM_STATE_OK == pFlashSimHandle->state)
    {
        /* Check parameter */
        if ((NULL == buff) || (0 == size))
        {
            retVal = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
            pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
            if (NULL != s_FlashErrorCallback)
            {
                s_FlashErrorCallback();
            }
        }
        else
        {
            /* Check parameter */
            if ((startAddress >= FLASH_START_ADDRESS)\
                && ((startAddress < (FLASH_START_ADDRESS + FLASH_SIZE)))\
                && (size <= (FLASH_SIZE - (startAddress - FLASH_START_ADDRESS))))
            {
                /* Set flash state is busy */
                pFlashSimHandle->state = FLASH_SIM_STATE_BUSY;
                /* Read data from flash */
                memcpy(buff, p_data, size);
                /* Set flash state is OK */
                pFlashSimHandle->state = FLASH_SIM_STATE_OK;
            }
            else
            {
                retVal = FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE;
                pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE;
                if (NULL != s_FlashErrorCallback)
                {
                    s_FlashErrorCallback();
                }
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
  * @retval FlashSim_StateTypeDef
  */
FlashSim_StateTypeDef FlashSim_Write(uint64_t startAddress, uint8_t* const buff, uint32_t size)
{
    FlashSim_StateTypeDef retVal = FLASH_SIM_STATE_OK;
    uint8_t* p_data = (uint8_t*)(startAddress + &s_FlashMem[0][0]);
    uint8_t* buff_temp = buff;

    /* Check parameter */
    if (FLASH_SIM_STATE_OK == pFlashSimHandle->state)
    {
        /* Check parameter */
        if ((NULL == buff) || (0 == size))
        {
            retVal = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
            pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
            if (NULL != s_FlashErrorCallback)
            {
                s_FlashErrorCallback();
            }
        }
        else
        {
            /* Check parameter */
            if ((startAddress >= FLASH_START_ADDRESS)\
                && ((startAddress < (FLASH_START_ADDRESS + FLASH_SIZE))) \
                && ((size + startAddress) <= FLASH_SIZE))
            {
                /* Set flash state is busy */
                pFlashSimHandle->state = FLASH_SIM_STATE_BUSY;
                /* write to flash */
                while ((size--) && (FLASH_SIM_STATE_OK == retVal))
                {
                    /*check memorycell, value before write nead equal 0xFF */
                    if (0xFF != *p_data)
                    {
                        retVal = FLASH_SIM_STATE_ERROR_WRITE_TO_DIFF_FF;
                    }
                    else
                    {
                        *p_data = *buff_temp;
                        p_data++;
                        buff_temp++;
                    }
                }
                if (FLASH_SIM_STATE_BUSY == pFlashSimHandle->state)
                {
                    /* Set flash state is OK */
                    pFlashSimHandle->state = FLASH_SIM_STATE_OK;
                }

            }
            else
            {
                retVal = FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE;
                pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE;
                if (NULL != s_FlashErrorCallback)
                {
                    s_FlashErrorCallback();
                }
            }
        }
    }
    return retVal;
}

/**
  * @brief  Erase multi sectors
  * @param  sectorIndex - Index of start sector
  * @param  numOfSector - Number of sector
  * @retval FlashSim_StateTypeDef
  */
FlashSim_StateTypeDef FlashSim_EraseMultiSector(uint64_t sectorIndex, uint32_t numOfSector)
{
    FlashSim_StateTypeDef retVal = pFlashSimHandle->state;
    uint8_t* EraseStartAddr = 0;

    /* Check parameter */
    if (FLASH_SIM_STATE_OK == retVal)
    {
        /* Check parameter */
        if ((NUMBER_OF_SECTOR <= sectorIndex) || ((NUMBER_OF_SECTOR - sectorIndex) < numOfSector))
        {
            retVal = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
            pFlashSimHandle->state = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
            /* Call error Callback function */
            if (NULL != s_FlashErrorCallback)
            {
                s_FlashErrorCallback();
            }

        }
        else
        {
            /* Set flash state is busy */
            pFlashSimHandle->state = FLASH_SIM_STATE_BUSY;
            EraseStartAddr = &s_FlashMem[0][0] + SECTOR_SIZE * sectorIndex;
            /* Erase flash */
            memset(EraseStartAddr, 0xFF, SECTOR_SIZE * numOfSector);
            /* Set flash state is OK */
            pFlashSimHandle->state = FLASH_SIM_STATE_OK;
        }
    }

    return retVal;
}

/**
  * @brief  this func show content of sector
  * @param  sectorIndex - Index of sector
  * @retval FlashSim_StateTypeDef
  */
void FlashSim_ShowSector(uint16_t startSector, uint16_t endSector)
{
    uint8_t indx, indy;
    uint8_t* data = &s_FlashMem[0][0];
    uint32_t offset = startSector * 512U;
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
                printf("     %02X\t", *(i * 512 + data + indx * 16 + indy));
            }
            printf("\n");
        }
        printf("\n\n");
    }
}


/******************************************************************************
 * EOF
 ******************************************************************************/
