/*******************************************************************************
* Include
******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "LogData.h"
#include "flash_sim.h"

/*******************************************************************************
* Definitions
******************************************************************************/

#define LOG_DATA_USED_VALUE                (0x00u)      /* value of field "USED" if package is used */
/* CRC16 - CCITT polynomial */
#define CRC16_POLY 0x1021

/*******************************************************************************
* Variable
******************************************************************************/
/* Static variable data region */
//static DataRegion_TypeDef dataRegion;

/*******************************************************************************
* Prototype
******************************************************************************/

/*******************************************************************************
* Code
******************************************************************************/
/**
* @brief Check valid CRC
*
* @param pu8package : package need check CRC
*
* @return StatusTypeDef ERROR or ERROR_NONE
*/
StatusTypeDef LogData_CheckValidCRC(DataRegion_TypeDef* dataRegion, uint8_t* pu8package)
{
    /* assert check input param*/
    assert_param(NULL != pu8package);

    StatusTypeDef retVal = ERROR;
    uint16_t crc_cal = 0u;   /* crc caculate */
    uint16_t crc_pack = *((uint16_t*)&pu8package[dataRegion->lengthPackage - 3u]); /* crc in package */
    uint16_t crc_ret = (crc_pack & 0xFF) << 8u | (crc_pack & 0xFF00) >> 8u;
    uint16_t length = (dataRegion->lengthPackage - 3u);
    uint8_t i;
    while (length)
    {
        length--;
        crc_cal = crc_cal ^ ((uint16_t)*pu8package++ << 8u);
        for (i = 0u; i < 8u; i++)
        {
            if (crc_cal & 0x8000u)
            {
                crc_cal = (crc_cal << 1u) ^ CRC16_POLY;/*0x1021 is polynomial of CRC16 */
            }
            else
            {
                crc_cal = crc_cal << 1u;
            }
        }
    }
    if (crc_cal == crc_ret)
    {
        retVal = ERROR_NONE;
    }

    return retVal;
}


/**
* @brief Funtion find last sector
*
* @param pu32AddrLastSector: address last sector
*
* @return StatusTypeDef ERROR or ERROR_NONE
*/
StatusTypeDef LogData_FindLastSector(DataRegion_TypeDef* dataRegion, uint64_t* pu64AddrLastSector)
{
    /* assert check input param*/
    assert_param(NULL != pu64AddrLastSector);

    StatusTypeDef retVal = ERROR;
    uint64_t index;            /*index for loop*/
    uint8_t temp = 0;              /* buffer */
    /* scan all find last sector */
    for (index = (dataRegion->beginAddress  + SECTOR_SIZE - LOG_DATA_SIZE_OF_PACKAGE); index <= dataRegion->endAddress; index = index + SECTOR_SIZE)
    {
        /* Read sector in Flash */
        if (FLASH_SIM_STATE_OK == FlashSim_Read(index, &temp, 1))
        {
            if (temp == 0xFF)
            {
                *pu64AddrLastSector = index - (SECTOR_SIZE - LOG_DATA_SIZE_OF_PACKAGE);
                retVal = ERROR_NONE;
                break;
            }
        }
    }
    
    if ((0 == *pu64AddrLastSector) && (retVal == ERROR_NONE))
    {
        retVal = (StatusTypeDef)FlashSim_Read(*pu64AddrLastSector, &temp, 1);
        if(0xFF == temp)
        {
            retVal = (StatusTypeDef)FlashSim_Read(*pu64AddrLastSector+SECTOR_SIZE, &temp, 1);
            if (0xFF == temp)
            {
                retVal = ERROR;
            }
            else{
                *pu64AddrLastSector = dataRegion->endAddress+1- SECTOR_SIZE;
            }
        }
    }
    return retVal;
}



/* sequential search*/
/**
* @brief Find last saved Pakage position
*
* @param AddrLastPackage : address last package
*
* @return StatusTypeDef ERROR or ERROR_NONE
*/
StatusTypeDef LogData_FindLastPackage(DataRegion_TypeDef* dataRegion, uint64_t* AddrLastPackage)
{
    /* assert check input param */
    assert_param(NULL != AddrLastPackage);

    StatusTypeDef retVal = ERROR;
    uint32_t index;
    uint8_t temp;
    uint64_t lastSectorPos; /* address last sector */

    LogData_FindLastSector(dataRegion, &lastSectorPos);

    for (index = 0; index < dataRegion->numberPackage; index++)
    {
        if (FLASH_SIM_STATE_OK == FlashSim_Read((lastSectorPos + (uint64_t)index * LOG_DATA_SIZE_OF_PACKAGE), &temp, 1))
        {
            if (temp == 0xFF)
            {
                /*Tail positon package */
                *AddrLastPackage = lastSectorPos + (uint64_t)(index - 1) * LOG_DATA_SIZE_OF_PACKAGE;
            }
            retVal = ERROR_NONE;
        }

    }

    return retVal;
}



/* Binary search */
/**
* @brief Find last saved Pakage position
*
* @param AddrLastPackage : address last package
*
* @return StatusTypeDef ERROR or ERROR_NONE
*/
StatusTypeDef LogData_FindLastPackage_Binary(DataRegion_TypeDef* dataRegion, uint64_t* AddrLastPackage)
{
    /* assert check input param*/
    assert_param(NULL != AddrLastPackage);

    StatusTypeDef retVal = ERROR;                               /* return value */
    uint64_t addrOffset;                                   /* address last sector */
    uint8_t left = 0;                                       /* left element */
    uint8_t right = LOG_DATA_NUM_OF_PACKAGE_PER_SECTOR - 1; /* right element */
    uint8_t mid;                                            /* middle element */
    uint8_t temp;

    /* if finding address last sector ok */
    if (ERROR_NONE == LogData_FindLastSector(dataRegion, &addrOffset))
    {
        retVal = ERROR_NONE;
        while (((left + 1) < right) && (ERROR_NONE == retVal))
        {
            printf("Found last sector\n");
            /*finding the middle index "mid" */
            mid = left + (right - left) / 2;
            if (FLASH_SIM_STATE_OK == FlashSim_Read((addrOffset + mid * LOG_DATA_SIZE_OF_PACKAGE), &temp, 1))
            {
                if (temp == 0xFF)
                {
                    right = mid;
                }
                else
                {
                    left = mid;
                }
                retVal = ERROR_NONE;
            }
            else
            {
                retVal = ERROR;
            }
        }
        *AddrLastPackage = addrOffset + (left * LOG_DATA_SIZE_OF_PACKAGE);
    }

    return retVal;
}

StatusTypeDef LogData_FindNextPackage(DataRegion_TypeDef* dataRegion, uint64_t* nextPackagePos, uint64_t currentPackagePos)
{
    assert_param(NULL != dataRegion);
    StatusTypeDef retVal = ERROR_NONE;
    if ((dataRegion->endAddress + 1U - LOG_DATA_SIZE_OF_PACKAGE) == currentPackagePos)
    {
        *nextPackagePos = dataRegion->beginAddress;
    }
    else
    {
        *nextPackagePos = currentPackagePos + LOG_DATA_SIZE_OF_PACKAGE;
    }
    if (((*nextPackagePos) % LOG_DATA_SECTOR_SIZE) == 0)
    {
        FlashSim_EraseMultiSector((*nextPackagePos)/LOG_DATA_SECTOR_SIZE, 1);
    }
    return retVal;
}


/**
* @brief Erase Log Region Data on Flash Memory
*
* @param None
*
* @return StatusTypeDef ERROR or ERROR_NONE
*/
StatusTypeDef LogData_EraserLogRegion(DataRegion_TypeDef* dataRegion)
{
    StatusTypeDef retVal = ERROR;
    uint32_t sectorPos;     /* variable calulate position sector eraser */
    uint32_t numberSector;   /* variable caculate number sector eraser */

    /* caculate sector positon */
    sectorPos = (uint32_t)((dataRegion->beginAddress) / LOG_DATA_SECTOR_SIZE);
    /* caculate number sector */
    numberSector = ((uint32_t)((dataRegion->beginAddress) / LOG_DATA_SECTOR_SIZE)) - sectorPos;

    /* Eraser sector*/
    if (FLASH_SIM_STATE_OK == FlashSim_EraseMultiSector(sectorPos, numberSector))
    {
        retVal = ERROR_NONE;
    }

    return retVal;
}



/**
* @brief Set Package Is Used
*
* @param u16packageIdx: position package need set used
*
* @return StatusTypeDef ERROR or ERROR_NONE
**/
StatusTypeDef LogData_SetPackageIsUsed(DataRegion_TypeDef* dataRegion, uint16_t u16packageIdx)
{
    StatusTypeDef retVal = ERROR;
    //uint8_t addrPackagePos;
    uint8_t writeVal = LOG_DATA_USED_VALUE;
    uint64_t packageUsedFieldPos;

    packageUsedFieldPos = dataRegion->beginAddress + (uint64_t)(u16packageIdx * LOG_DATA_SIZE_OF_PACKAGE) + (uint64_t)(LOG_DATA_SIZE_OF_PACKAGE - 1u);

    if (FLASH_SIM_STATE_OK == FlashSim_Write(packageUsedFieldPos, &writeVal, 1))
    {
        retVal = ERROR_NONE;
    }

    return retVal;
}
/*******************************************************************************
* EOF
******************************************************************************/
