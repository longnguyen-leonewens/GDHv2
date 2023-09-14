/**
  ******************************************************************************
  * @file    flash_sim.h
  * @author  VinhDeDe1
  * @date    11st Sep 2027
  * @brief   JOB 6: Flash simulator
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
#ifndef FLASH_H_
#define FLASH_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include <stdint.h>
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/
/* Function pointer report error */
typedef void (*p_FlashSim_ErrorCallback)(void);

/* Flash emulation state list */
typedef enum {
    FLASH_SIM_STATE_OK     = (0x0U),                          /* Process is ok */
    FLASH_SIM_STATE_ERROR_WRITE_TO_INVALID_ADDR,              /* Write to region difference 0xFF  */
    FLASH_SIM_STATE_ERROR_ACCESS_NOT_IN_FLASH_REGION,         /* Read/write to invalid address */
    FLASH_SIM_STATE_ERROR_PARAM_INVALID,                      /* Input parameter is invalid */
    FLASH_SIM_STATE_BUSY,                                     /* Flash is busy */
} FlashSim_State_t;

/* Lock structures definition */
typedef enum
{
  FLASH_SIM_UNLOCKED = 0x00U,
  FLASH_SIM_LOCKED   = 0x01U
} FlashSim_Lock_t;

/* Flash handle struct */
typedef struct FlashSim_Handle_Struct
{
    uint32_t FlashStartAddress;
    FlashSim_State_t state;
    FlashSim_Lock_t  lock;
    p_FlashSim_ErrorCallback ErrorCallbackPointer;
} FlashSim_Handle_Struct_t;

/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/
#define NUMBER_OF_SECTOR        (0x70U)         /* 64 sectors */
#define SECTOR_SIZE             (0x0200U)       /* 512 bytes/sec*/
#define FLASH_START_ADDRESS     (0x00000000U)

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
  * @brief  Initialized flash simulation.
  *         This function ...
  * @param  void
  * @retval void
  */
FlashSim_State_t FlashSim_Init(FlashSim_Handle_Struct_t * const FlashSimHandle);

/**
  * @brief  Read data from flash
  * @param  startAddress  -  start address in flash
  * @param  buff          -  pointer to buffer where store read data
  * @param  size          -  size of buffer
  * @retval FLASH_SIM_ERROR_t
  */
FlashSim_State_t FlashSim_Read(uint32_t startAddress, uint8_t * const buff, uint32_t size);

/**
  * @brief  Write data to flash
  * @param  startAddress  -  start address in flash
  * @param  buff          -  pointer to buffer where store data
  * @param  size          -  size of buffer
  * @retval FLASH_SIM_ERROR_t
  */
FlashSim_State_t FlashSim_Write(uint32_t startAddress, uint8_t * const buff, uint32_t size);

/**
  * @brief  Erase multi sectors
  * @param  sectorIndex - Index of start sector
  * @param  numOfSector - Number of sector
  * @retval FLASH_SIM_ERROR_t
  */
FlashSim_State_t FlashSim_EraseMultiSector(uint32_t sectorIndex, uint32_t numOfSector);

#endif /* FLASH_SIM_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/