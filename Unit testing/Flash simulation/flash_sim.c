
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

static FlashSim_Handle_Struct_t * pFlashSimHandle;
/******************************************************************************
* * API
******************************************************************************/
/**
  * @brief  Initialized flash simulation.
  *         This function init Flash simulation
  * @param  FlashSimHandle pointer to init struct
  * @retval void
  */
FlashSim_State_t FlashSim_Init(FlashSim_Handle_Struct_t * const FlashSimHandle)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
	/* check parameter*/
    if(NULL == FlashSimHandle)
    {
        retVal = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
    }
    else
    {
        if (FLASH_SIM_UNLOCKED == FlashSimHandle->lock)
        {
        	/* Set flash state is busy */
        	FlashSimHandle->state = FLASH_SIM_STATE_BUSY;
            s_FlashErrorCallback  = FlashSimHandle->ErrorCallbackPointer;
            FlashSimHandle->lock  = FLASH_SIM_LOCKED;            

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
  * @retval FlashSim_State_t
  */
FlashSim_State_t FlashSim_Read(uint32_t startAddress, uint8_t * const buff, uint32_t size)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
    uint8_t * p_data = (uint8_t *)(startAddress+&s_FlashMem[0][0]);

	/* Check parameter */
    if( FLASH_SIM_STATE_OK == pFlashSimHandle->state )
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
            	&&((startAddress < (FLASH_START_ADDRESS+FLASH_SIZE)))\
                && (size <= (FLASH_SIZE - (startAddress - FLASH_START_ADDRESS))))
            {
            	/* Set flash state is busy */
            	pFlashSimHandle->state =  FLASH_SIM_STATE_BUSY;
            	/* Read data from flash */
            	memcpy(buff, p_data, size);
            	/* Set flash state is OK */
            	pFlashSimHandle->state =  FLASH_SIM_STATE_OK;
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
  * @retval FlashSim_State_t
  */
FlashSim_State_t FlashSim_Write(uint32_t startAddress, uint8_t * const buff, uint32_t size)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
    uint8_t * p_data = (uint8_t *)(startAddress+&s_FlashMem[0][0]);
    uint8_t * buff_temp = buff;

	/* Check parameter */
    if (FLASH_SIM_STATE_OK == pFlashSimHandle->state)
    {
    	/* Check parameter */
        if((NULL == buff) || (0 == size))
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
            	&&((startAddress < (FLASH_START_ADDRESS+FLASH_SIZE))) \
                && ((size + startAddress) <= FLASH_SIZE))
            {
            	/* Set flash state is busy */
            	pFlashSimHandle->state = FLASH_SIM_STATE_BUSY;
            	/* write to flash */
                while((size--) && (FLASH_SIM_STATE_OK == retVal))
                {
                	/*check memorycell, value before write nead equal 0xFF */
                    if (0xFF != *p_data)
                    {
                        retVal = FLASH_SIM_STATE_ERROR_WRITE_TO_DIFF_FF;
                    }
                    else
                    {
                        *p_data = *buff_temp;
                        p_data      ++;
                        buff_temp   ++;
                    }
                }
                if(FLASH_SIM_STATE_BUSY == pFlashSimHandle->state)
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
  * @retval FlashSim_State_t
  */
FlashSim_State_t FlashSim_EraseMultiSector(uint32_t sectorIndex, uint32_t numOfSector)
{
    FlashSim_State_t retVal = pFlashSimHandle->state;
	uint8_t *EraseStartAddr  = 0;
	
	/* Check parameter */
    if( FLASH_SIM_STATE_OK == retVal )
    {
    	/* Check parameter */
        if ((NUMBER_OF_SECTOR <= sectorIndex) || ((NUMBER_OF_SECTOR-sectorIndex) < numOfSector))
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
        	EraseStartAddr = &s_FlashMem[0][0] + SECTOR_SIZE*sectorIndex;
        	/* Erase flash */
            memset(EraseStartAddr, 0xFF, SECTOR_SIZE*numOfSector);
            /* Set flash state is OK */
            pFlashSimHandle->state = FLASH_SIM_STATE_OK;
        }
    }

    return retVal;
}

/**
  * @brief  this func show content of sector
  * @param  sectorIndex - Index of sector
  * @retval FlashSim_State_t
  */
FlashSim_State_t FlashSim_ShowSector(uint32_t sectorIndex)
{
	uint8_t indx, indy;
	uint8_t *data = &s_FlashMem[0][0] + sectorIndex*SECTOR_SIZE;
	FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
	
	if (NUMBER_OF_SECTOR <= sectorIndex)
	{
        retVal = FLASH_SIM_STATE_ERROR_INVALID_PARAM;
    }
    else
    {
    	for(indx =0; indx <64; indx++)
    	{
	        for(indy = 0; indy <8; indy++)
	        {
	        	/* print each byte */
	           printf("%X\t", *(data + indx*8 + indy));
	        }
	        printf("\n");
	    }
	}

	return retVal;
}

/******************************************************************************
* * EOF
******************************************************************************/
