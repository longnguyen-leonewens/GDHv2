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
    uint32_t beginAddress;   /* start address of data region */
    uint32_t endAddress;     /* end address of data region */
    //uint16_t numberPackage;  /* number of package */
    //uint16_t position;       /* positon of package */
    uint16_t length;         /* length of package */
}DataRegion_Struct_t;

#define LOG_DATA_BEGIN_ADDRESS             (0x0000u)    /* begin address in log data region */
#define LOG_DATA_END_ADDRESS               (0x7FFFu)    /* end address in log data region */
#define LOG_DATA_NUMBER_PACKAGE            (70u)        /* Number package */
#define LOG_DATA_LENGTH_PACKAGE            (64u)        /* Number byte of package */
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
  * @brief  Init for Log Region
  *
  * @param  dataInit: address of struct data init
  *
  * @return OK or FAIL
  */
status_t logData_InitLogRegion(void);

/**
* @brief Check valid CRC
*
* @param pu8package : package need check CRC
*
* @return OK or FAIL
*/
status_t logData_CheckValidCRC(uint8_t* pu8package);

/**
 * @brief Funtion find last sector
 *
 * @param pu32AddrLastSector: address last sector
 *
 * @return status_t RET_FAIL or RET_OK
 */
status_t logData_FindLastSector(uint32_t* pu32AddrLastSector);

/**
* @brief Find last saved Pakage position
*
* @param AddrLastPackage : address last package
*
* @return OK or FAIL
*/
status_t logData_FindLastPackage(uint32_t* AddrLastPackage);

/* Binary search */
/**
* @brief Find last saved Pakage position
*
* @param AddrLastPackage : address last package
*
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_FindLastPackage_Binary(uint32_t* AddrLastPackage);

/**
* @brief Erase Log Region on Flash Memory
*
* @param u32startAddEraser: address start Eraser
* @param u32endAddEraser  : address end Eraser
*
* @return OK or FAIL
*/
status_t logData_EraserLogRegion(void);

/**
* @brief Set Package Is Used
*
* @param packageIdx: position package
*
* @return OK or FAIL
*/
status_t logData_SetPackageIsUsed(uint16_t u16packageIdx);

#endif /* _LOGDATA_H_ */
/*******************************************************************************
* EOF
******************************************************************************/