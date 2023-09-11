/**
  ******************************************************************************
  * @file    logdata.h
  * @author  TuanPA41
  * @date    11th Sep 2027
  * @brief   JOB 5: Log data to FLAsH
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
#ifndef LOGDATA_H_
#define LOGDATA_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include <stdint.h>
/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/*
* @brief Enum status return of Function
*/
typedef enum
{
    OK,
    FAIL,
}status_t;

/*
* @brief Struct of Data Region Flash
*/
typedef struct DataRegion
{
    uint32_t beginAddress;   /* start address of data region */
    uint32_t endAddress;     /* end address of data region */
    uint16_t numberPackage;  /* number of package */
    uint16_t position;       /* positon of package */
    uint16_t length;         /* length of package */
}DataRegion_Struct_t;

/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/

/** @defgroup Example of constants
 * @{
 */
#define MODULE_CONST_1
#define MODULE_CONST_2
/**
 * @}
 */

/******************************************************************************
 * EXPORTED MACROS
 ******************************************************************************/

/**
 * @brief Example of macros
 */
#define MARCO(X)                  (X+3)

/******************************************************************************
 * EXPORTED VARIABLES
 ******************************************************************************/
/* Static variable data region */
static DataRegion_Struct_t dataRegion;
/******************************************************************************
 * EXPORTED FUNCTIONS PROTOTYPES
 ******************************************************************************/
/*
* @brief  Init for Flash
* @param  dataInit: address of struct data init
* @return OK or FAIL
*/
status_t logData_InitFlash(DataRegion_Struct_t * dataInit);

/*
* @brief Check valid CRC
* @param package : package need check CRC
* @return OK or FAIL
*/
status_t logData_CheckValidCRC(uint8_t * package);

/*
* @brief Find last saved Pakage position
* @param None
* @return OK or FAIL
*/
status_t logData_FindLastPackage(void);

/*
* @brief Erase Log Region on Flash Memory
* @param None
* @return OK or FAIL
*/
status_t logData_EraserLogRegion(void);

/*
* @brief Set Package Is Used
* @param packageIdx: position package
* @return OK or FAIL
*/
status_t logData_SetPackageIsUsed(uint16_t packageIdx);

/*
* @brief Function Process Thread 3 (Log Data to Flash)
* @param *vargp:
* @return OK or FAIL
*/
status_t * logData_SaveData(void *vargp);

#endif /* LOGDATA_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/