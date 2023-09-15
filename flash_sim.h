/**
  ******************************************************************************
  * @file    flash_sim.h
  * @author  VinhDD1
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
#ifndef FLASH_SIM_H_
#define FLASH_SIM_H_

  /******************************************************************************
   * INCLUDES
   ******************************************************************************/
#include <stdint.h>
   /******************************************************************************
    * EXPORTED TYPEDEF
    ******************************************************************************/
    /* Function pointer report error */
typedef void (*FlashSim_ErrorCallback)(void);

/* Flash emulation state list */
typedef enum {
    FLASH_SIM_STATE_OK = (0x0U),                          /* Process is ok */
    FLASH_SIM_STATE_ERROR_WRITE_TO_DIFF_FF,                   /* Write to region difference 0xFF  */
    FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE,                   /* Read/write to invalid address */
    FLASH_SIM_STATE_ERROR_INVALID_PARAM,                      /* Input parameter is invalid */
    FLASH_SIM_STATE_BUSY,                                     /* Flash is busy */
} FlashSim_StateTypeDef;

/* Lock structures definition */
typedef enum
{
    FLASH_SIM_UNLOCKED = 0x00U,
    FLASH_SIM_LOCKED = 0x01U
} FlashSim_LockTypeDef;

/* Flash handle struct */
typedef struct FlashSim_Handle_Struct
{
    FlashSim_StateTypeDef state;
    FlashSim_LockTypeDef  lock;
    FlashSim_ErrorCallback ErrorCallbackPointer;
} FlashSim_HandleTypeDef;

/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/
#define NUMBER_OF_SECTOR        (0x40U)                           /* 64 sectors */
#define SECTOR_SIZE             (0x0200U)                         /* 512 bytes/sec*/
#define FLASH_SIZE              (NUMBER_OF_SECTOR * SECTOR_SIZE)  /* size of flash */
#define FLASH_START_ADDRESS     (0x00000000U)                     /* flash start address*/

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
      *         This function init Flash simulation
      * @param  FlashSimHandle pointer to init struct
      * @retval void
      */
FlashSim_StateTypeDef FlashSim_Init(FlashSim_HandleTypeDef* const FlashSimHandle);

/**
  * @brief  Read data from flash
  * @param  startAddress  -  start address in flash
  * @param  buff          -  pointer to buffer where store read data
  * @param  size          -  size of buffer
  * @retval FlashSim_StateTypeDef
  */
FlashSim_StateTypeDef FlashSim_Read(uint64_t startAddress, uint8_t* const buff, uint32_t size);

/**
  * @brief  Write data to flash
  * @param  startAddress  -  start address in flash
  * @param  buff          -  pointer to buffer where store data
  * @param  size          -  size of buffer
  * @retval FlashSim_StateTypeDef
  */
FlashSim_StateTypeDef FlashSim_Write(uint64_t startAddress, uint8_t* const buff, uint32_t size);

/**
  * @brief  Erase multi sectors
  * @param  sectorIndex - Index of start sector
  * @param  numOfSector - Number of sector
  * @retval FlashSim_StateTypeDef
  */
FlashSim_StateTypeDef FlashSim_EraseMultiSector(uint64_t sectorIndex, uint32_t numOfSector);

/**
  * @brief  this func show content of sector
  * @param  sectorIndex - Index of sector
  * @retval FlashSim_StateTypeDef
  */
FlashSim_StateTypeDef FlashSim_ShowSector(uint32_t sectorIndex);

void printfFlashMem(uint16_t startSector, uint16_t endSector);

#endif /* FLASH_SIM_H_ */

/******************************************************************************
* EOF
******************************************************************************/
