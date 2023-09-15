/**
* @file logData.h
* @author TuanPA41
* @brief Job 5: Log data to flash simulation
* @version 0.1
* @date 2023-09-11
*
* @copyright Copyright (c) 2023
*
*/
#ifndef  _LOGDATA_H_
#define  _LOGDATA_H_

/*******************************************************************************
* Definitions
******************************************************************************/

/*
* @brief Enum status return of Function
*/
typedef enum
{
    RET_OK,
    RET_FAIL,
}status_t;

/*
* @brief Struct of Data Region Flash
*/
typedef struct DataRegion
{
    uint64_t beginAddress;   /* start address of data region */
    uint64_t endAddress;     /* end address of data region */
    uint16_t numberPackage;  /* number of package */
    uint16_t lengthPackage;         /* length of package */
}DataRegion_Struct_t;


#define LOG_DATA_NUMBER_OF_SECTOR          (64u)        /* 64 sector */
#define LOG_DATA_SECTOR_SIZE               (512u)       /* 512 byte */
#define LOG_DATA_SIZE_OF_PACKAGE           (64u)        /* 64 byte */
#define LOG_DATA_NUM_OF_PACKAGE_PER_SECTOR (LOG_DATA_SECTOR_SIZE/ LOG_DATA_SIZE_OF_PACKAGE ) /* number package per sector */

/*******************************************************************************
* Variable
******************************************************************************/

/*******************************************************************************
  * API
  ******************************************************************************/

  /**
  * @brief Check valid CRC
  *
  * @param dataRegion: struct log region init 
  * @param pu8package : package need check CRC
  *
  * @return OK or FAIL
  */
status_t logData_CheckValidCRC(DataRegion_Struct_t* dataRegion, uint8_t* pu8package);

/**
* @brief Funtion find last sector
*
* @param dataRegion: struct log region init
* @param pu32AddrLastSector: address last sector
*
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_FindLastSector(DataRegion_Struct_t* dataRegion, uint64_t* pu32AddrLastSector);

/**
* @brief Find last saved Pakage position
*
* @param dataRegion: struct log region init
* @param AddrLastPackage : address last package
*
* @return OK or FAIL
*/
status_t logData_FindLastPackage(DataRegion_Struct_t* dataRegion, uint64_t* AddrLastPackage);

/* Binary search */
/**
* @brief Find last saved Pakage position
*
* @param dataRegion: struct log region init
* @param AddrLastPackage : address last package
*
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_FindLastPackage_Binary(DataRegion_Struct_t* dataRegion, uint64_t* AddrLastPackage);

/**
* @brief Erase Log Region on Flash Memory
*
* @param dataRegion: struct log region init
* 
* @return OK or FAIL
*/
status_t logData_EraserLogRegion(DataRegion_Struct_t* dataRegion);

/**
* @brief Set Package Is Used
*
* @param dataRegion: struct log region init 
* @param u16packageIdx: position package
*
* @return OK or FAIL
*/
status_t logData_SetPackageIsUsed(DataRegion_Struct_t* dataRegion, uint16_t u16packageIdx);

/**
* @brief Find Next Package Position Address
*
* @param dataRegion: struct log region init 
* @param nextPackagePos: next package address 
* @param currentPackagePos: current package address
*
* @return OK or FAIL
*/
status_t logData_FindNextPackage(DataRegion_Struct_t* dataRegion, uint64_t* nextPackagePos, uint64_t currentPackagePos);

#endif /* _LOGDATA_H_ */
/*******************************************************************************
* EOF
******************************************************************************/

