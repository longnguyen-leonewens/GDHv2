/**
  ******************************************************************************
  * @file LogData.h
* @author TuanPA41
* @brief Job 5: Log data to flash simulation
* @version 0.1
* @date 2023-09-11
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
#ifndef  _LOGDATA_H_
#define  _LOGDATA_H_


/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "def.h"
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/**
* @brief Struct of Data Region Flash
*/
typedef struct DataRegion
{
    uint64_t beginAddress;   /* start address of data region */
    uint64_t endAddress;     /* end address of data region */
    uint16_t numberPackage;  /* number of package */
    uint16_t lengthPackage;         /* length of package */
}DataRegion_TypeDef;

/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/

#define LOG_DATA_NUMBER_OF_SECTOR          (64u)        /* 64 sector */
#define LOG_DATA_SECTOR_SIZE               (512u)       /* 512 byte */
#define LOG_DATA_SIZE_OF_PACKAGE           (64u)        /* 64 byte */
#define LOG_DATA_NUM_OF_PACKAGE_PER_SECTOR (LOG_DATA_SECTOR_SIZE/ LOG_DATA_SIZE_OF_PACKAGE ) /* number package per sector */

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
  * @brief Check valid CRC
  *
  * @param dataRegion: struct log region init 
  * @param pu8package : package need check CRC
  *
  * @return OK or FAIL
  */
StatusTypeDef LogData_CheckValidCRC(DataRegion_TypeDef* dataRegion, uint8_t* pu8package);

/**
* @brief Funtion find last sector
*
* @param dataRegion: struct log region init
* @param pu32AddrLastSector: address last sector
*
* @return StatusTypeDef RET_FAIL or RET_OK
*/
StatusTypeDef LogData_FindLastSector(DataRegion_TypeDef* dataRegion, uint64_t* pu32AddrLastSector);

/**
* @brief Find last saved Pakage position
*
* @param dataRegion: struct log region init
* @param AddrLastPackage : address last package
*
* @return OK or FAIL
*/
StatusTypeDef LogData_FindLastPackage(DataRegion_TypeDef* dataRegion, uint64_t* AddrLastPackage);

/* Binary search */
/**
* @brief Find last saved Pakage position
*
* @param dataRegion: struct log region init
* @param AddrLastPackage : address last package
*
* @return StatusTypeDef RET_FAIL or RET_OK
*/
StatusTypeDef LogData_FindLastPackage_Binary(DataRegion_TypeDef* dataRegion, uint64_t* AddrLastPackage);

/**
* @brief Erase Log Region on Flash Memory
*
* @param dataRegion: struct log region init
* 
* @return OK or FAIL
*/
StatusTypeDef LogData_EraserLogRegion(DataRegion_TypeDef* dataRegion);

/**
* @brief Set Package Is Used
*
* @param dataRegion: struct log region init 
* @param u16packageIdx: position package
*
* @return OK or FAIL
*/
StatusTypeDef LogData_SetPackageIsUsed(DataRegion_TypeDef* dataRegion, uint16_t u16packageIdx);

/**
* @brief Find Next Package Position Address
*
* @param dataRegion: struct log region init 
* @param nextPackagePos: next package address 
* @param currentPackagePos: current package address
*
* @return OK or FAIL
*/
StatusTypeDef LogData_FindNextPackage(DataRegion_TypeDef* dataRegion, uint64_t* nextPackagePos, uint64_t currentPackagePos);

#endif /* _LogData_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/
