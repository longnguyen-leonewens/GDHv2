/*******************************************************************************
* Include
******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "logData.h"
#include "flash_sim.h"
#include "assert_param.h"

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
//static DataRegion_Struct_t dataRegion;

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
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_CheckValidCRC(DataRegion_Struct_t* dataRegion, uint8_t* pu8package)
{
    /* assert check input param*/
    ASSERT(NULL != pu8package);

    status_t retVal = RET_FAIL;
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
        retVal = RET_OK;
    }

    return retVal;
}


/**
* @brief Funtion find last sector
*
* @param pu32AddrLastSector: address last sector
*
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_FindLastSector(DataRegion_Struct_t* dataRegion, uint64_t* pu64AddrLastSector)
{
    /* assert check input param*/
    ASSERT(NULL != pu64AddrLastSector);

    status_t retVal = RET_FAIL;
    uint64_t index;            /*index for loop*/
    uint8_t temp;              /* buffer */
    /* scan all find last sector */
    for (index = (dataRegion->beginAddress + SECTOR_SIZE - LOG_DATA_SIZE_OF_PACKAGE); index <= dataRegion->endAddress; index = index + SECTOR_SIZE)
    {
        /* Read sector in Flash */
        if (FLASH_SIM_STATE_OK == FlashSim_Read(index, &temp, 1))
        {
            if (temp == 0xFF)
            {
                *pu64AddrLastSector = index - (SECTOR_SIZE - LOG_DATA_SIZE_OF_PACKAGE);
                retVal = RET_OK;
                break;
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
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_FindLastPackage(DataRegion_Struct_t* dataRegion, uint64_t* AddrLastPackage)
{
    /* assert check input param */
    ASSERT(NULL != AddrLastPackage);

    status_t retVal = RET_FAIL;
    uint32_t index;
    uint8_t temp;
    uint64_t lastSectorPos; /* address last sector */

    logData_FindLastSector(dataRegion, &lastSectorPos);

    for (index = 0; index < dataRegion->numberPackage; index++)
    {
        if (FLASH_SIM_STATE_OK == FlashSim_Read((lastSectorPos + (uint64_t)index * LOG_DATA_SIZE_OF_PACKAGE), &temp, 1))
        {
            if (temp == 0xFF)
            {
                /*Tail positon package */
                *AddrLastPackage = lastSectorPos + (uint64_t)(index - 1) * LOG_DATA_SIZE_OF_PACKAGE;
            }
            retVal = RET_OK;
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
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_FindLastPackage_Binary(DataRegion_Struct_t* dataRegion, uint64_t* AddrLastPackage)
{
    /* assert check input param*/
    ASSERT(NULL != AddrLastPackage);

    status_t retVal = RET_OK;                               /* return value */
    uint64_t addrOffset;                                   /* address last sector */
    uint8_t left = 0;                                       /* left element */
    uint8_t right = LOG_DATA_NUM_OF_PACKAGE_PER_SECTOR - 1; /* right element */
    uint8_t mid;                                            /* middle element */
    uint8_t temp;

    /* if finding address last sector ok */
    if (RET_OK == logData_FindLastSector(dataRegion, &addrOffset))
    {
        while (((left + 1) < right) && (RET_OK == retVal))
        {
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
                retVal = RET_OK;
            }
            else
            {
                retVal = RET_FAIL;
            }
        }
        *AddrLastPackage = addrOffset + (left * LOG_DATA_SIZE_OF_PACKAGE);
    }

    return retVal;
}

status_t logData_FindNextPackage(DataRegion_Struct_t* dataRegion, uint64_t* nextPackagePos, uint64_t currentPackagePos)
{
    ASSERT(NULL != dataRegion);
    status_t retVal = RET_OK;
    if ((dataRegion->endAddress - LOG_DATA_SIZE_OF_PACKAGE) == currentPackagePos)
    {
        *nextPackagePos = dataRegion->beginAddress;
    }
    else
    {
        *nextPackagePos = currentPackagePos + LOG_DATA_SIZE_OF_PACKAGE;
    }
    if (((*nextPackagePos) % LOG_DATA_SECTOR_SIZE) == 0)
    {
        FlashSim_EraseMultiSector((*nextPackagePos), 1);
    }
    return retVal;
}


/**
* @brief Erase Log Region Data on Flash Memory
*
* @param None
*
* @return status_t RET_FAIL or RET_OK
*/
status_t logData_EraserLogRegion(DataRegion_Struct_t* dataRegion)
{
    status_t retVal = RET_FAIL;
    uint32_t sectorPos;     /* variable calulate position sector eraser */
    uint32_t numberSector;   /* variable caculate number sector eraser */

    /* caculate sector positon */
    sectorPos = (uint32_t)((dataRegion->beginAddress) / LOG_DATA_SECTOR_SIZE);
    /* caculate number sector */
    numberSector = ((uint32_t)((dataRegion->beginAddress) / LOG_DATA_SECTOR_SIZE)) - sectorPos;

    /* Eraser sector*/
    if (FLASH_SIM_STATE_OK == FlashSim_EraseMultiSector(sectorPos, numberSector))
    {
        retVal = RET_OK;
    }

    return retVal;
}



/**
* @brief Set Package Is Used
*
* @param u16packageIdx: position package need set used
*
* @return status_t RET_FAIL or RET_OK
**/
status_t logData_SetPackageIsUsed(DataRegion_Struct_t* dataRegion, uint16_t u16packageIdx)
{
    status_t retVal = RET_FAIL;
    //uint8_t addrPackagePos;
    uint8_t writeVal = LOG_DATA_USED_VALUE;
    uint64_t packageUsedFieldPos;

    packageUsedFieldPos = dataRegion->beginAddress + (uint64_t)(u16packageIdx * LOG_DATA_SIZE_OF_PACKAGE) + (uint64_t)(LOG_DATA_SIZE_OF_PACKAGE - 1u);

    if (FLASH_SIM_STATE_OK == FlashSim_Write(packageUsedFieldPos, &writeVal, 1))
    {
        retVal = RET_OK;
    }

    return retVal;
}
/*******************************************************************************
* EOF
******************************************************************************/
