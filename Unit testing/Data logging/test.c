/*******************************************************************************

 * Include

 ******************************************************************************/

#include <stdio.h>

#include <stdint.h>

#include <string.h>

#include "logData.h"

#include "flash_sim.h"

#include "test.h"

/*******************************************************************************

 * Definitions

 ******************************************************************************/

#define LAST_PACKAGE_ADDR           (LOG_DATA_SECTOR_SIZE + LOG_DATA_SIZE_OF_PACKAGE * 3) /* address last package */

#define LOG_DATA_BEGIN_ADDRESS      (0x0000u) /* begin address in log data region */

#define LOG_DATA_END_ADDRESS        (0x3FFFu) /* end address in log data region */

#define LOG_DATA_NUMBER_PACKAGE     (256u) /* Number package */

#define LOG_DATA_LENGTH_PACKAGE     (64u) /* Number byte of package */

#define NUM_PACKAGE_TEST_AVAILABLE  (19u)

/*******************************************************************************

 * Variable

 ******************************************************************************/

/* variable Flash handle struct */
FlashSim_Handle_Struct_t fs_Handle;
/* variable write buffer */
uint8_t W_buff[LOG_DATA_SECTOR_SIZE];
/* variable struct data region */
DataRegion_Struct_t dataRegion;

/*******************************************************************************

 * Code

 ******************************************************************************/

/**
 * @brief Initialize Log Region
 *
 * @param dataRegion : struct init for data region
 *
 * @return status_t RET_OK or RET_FAIL
 */
status_t TEST_InitLogRegion(DataRegion_Struct_t *dataRegion)
{
    /* Initialize for log data region */
    dataRegion->beginAddress = LOG_DATA_BEGIN_ADDRESS;
    dataRegion->endAddress = LOG_DATA_END_ADDRESS;
    dataRegion->numberPackage = LOG_DATA_NUMBER_PACKAGE;
    dataRegion->lengthPackage = LOG_DATA_LENGTH_PACKAGE;

    return RET_OK;
}

/* test for function logData_FindLastSector () */
Test_status_t test_FindLastSector(void)
{
    status_t ret;               /*return value*/
    uint64_t addressLastSector; /* address last sector in log data region */
    Test_status_t TestRetVal = TEST_FAILED;
    int i;

    /* unlocked flash simulation */
    fs_Handle.lock = FLASH_SIM_UNLOCKED;
    /* Initialize for log data region */
    TEST_InitLogRegion(&dataRegion);
    /* Initialize for flash simulation */
    FlashSim_Init(&fs_Handle);
    /* Eraser log data region */
    logData_EraserLogRegion(&dataRegion);

    /* test case 2: first sector have last package */

    /* casting value 0x5A for flash simulation */
    /* write data of flash simulation */
    for (i = 0; i < NUM_PACKAGE_TEST_AVAILABLE; i++)
    {
        memset(W_buff, i, LOG_DATA_SIZE_OF_PACKAGE);
        FlashSim_Write(FLASH_START_ADDRESS + i * 64, W_buff, LOG_DATA_SIZE_OF_PACKAGE);
    }

    /* get address of last sector saved */
    ret = logData_FindLastSector(&dataRegion, &addressLastSector);

    /* check address return for function "logData_FindLastSector" */
    if ((ret == RET_OK) && (addressLastSector == (LOG_DATA_BEGIN_ADDRESS + (uint32_t)(NUM_PACKAGE_TEST_AVAILABLE / LOG_DATA_NUM_OF_PACKAGE_PER_SECTOR) * LOG_DATA_SECTOR_SIZE)))
    {
        TestRetVal = TEST_PASS;
    }

    return TestRetVal;
}

/* test for function logData_FindLastPackage_Binary*/
Test_status_t test_FindLastPackage(void)
{
    uint64_t addressLastPackage;
    Test_status_t TestRetVal = TEST_PASS;
    int i = 0;

    fs_Handle.lock = FLASH_SIM_UNLOCKED;
    TEST_InitLogRegion(&dataRegion);
    FlashSim_Init(&fs_Handle);
    logData_EraserLogRegion(&dataRegion);

    /* test case 2: first sector have last package */
    /* write data of flash simulation */
    for (i = 0; i < NUM_PACKAGE_TEST_AVAILABLE; i++)
    {
        memset(W_buff, i, LOG_DATA_SIZE_OF_PACKAGE);
        FlashSim_Write(dataRegion.beginAddress + i * 64, W_buff, LOG_DATA_SIZE_OF_PACKAGE);
    }

    if (RET_OK == logData_FindLastPackage_Binary(&dataRegion, &addressLastPackage))
    {
        if (addressLastPackage != (dataRegion.beginAddress + (NUM_PACKAGE_TEST_AVAILABLE - 1u)*LOG_DATA_SIZE_OF_PACKAGE))
        {
            TestRetVal = TEST_FAILED;
        }

    }

    return TestRetVal;
}

/* test for function check valid CRC */
Test_status_t test_CheckValidCRC(void)
{
    Test_status_t TestRetVal = TEST_FAILED;
    static uint8_t buff_package[64];
    memset(buff_package, 0x6a, 61);
    buff_package[61] = 0x4B;
    buff_package[62] = 0xE8;
    TEST_InitLogRegion(&dataRegion);
    if (RET_OK == logData_CheckValidCRC(&dataRegion, buff_package))
    {
        TestRetVal = TEST_PASS;
    }

    return TestRetVal;
}

/* test for function EraseLogRegion */
Test_status_t test_CheckEraseLogRegion(void)
{
    Test_status_t TestRetVal = TEST_FAILED;
    static uint8_t buff_package_2[64];
    memset(buff_package_2, 0x7a, 61);

    /* Initialize for flash simulation */
    FlashSim_Init(&fs_Handle);
    TEST_InitLogRegion(&dataRegion);
    if (RET_OK == logData_EraserLogRegion(&dataRegion))
    {
        TestRetVal = TEST_PASS;
    }

    return TestRetVal;
}

Test_status_t test_CheckSetPackageIsUsed(void)
{
    Test_status_t TestRetVal = TEST_FAILED;
    /* 0: test case 1, 2: test case 2, 255: test case 3, 258: test case 4 */
    uint16_t buff_Idx[4] = {0, 2, LOG_DATA_NUMBER_PACKAGE - 1, LOG_DATA_NUMBER_PACKAGE + 2};
    /* return value for function logData_SetPackageIsUsed */
    status_t retTestVal[4] = {RET_OK, RET_OK, RET_OK, RET_FAIL};
    uint8_t i; /* index */

    /* unlocked flash simulation */
    fs_Handle.lock = FLASH_SIM_UNLOCKED;
    /* Initialize for log data region */
    TEST_InitLogRegion(&dataRegion);
    /* Initialize for flash simulation */
    FlashSim_Init(&fs_Handle);
    /* Eraser log data region */
    logData_EraserLogRegion(&dataRegion);
    /* looping check test case */
    for (i = 0; i < 4; i++)
    {
        if (retTestVal[i] == logData_SetPackageIsUsed(&dataRegion, buff_Idx[i]))
        {
            TestRetVal = TEST_PASS;
        }
    }

    return TestRetVal;
}

Test_status_t test_FindNextPackage()
{
    Test_status_t ret = TEST_PASS;
    uint16_t i;
    uint16_t numPackage = 254;
    uint64_t nextPackagePos;
    uint64_t currentPackagePos;
    FlashSim_State_t retVal;

    TEST_InitLogRegion(&dataRegion);
    /* Initialize for flash simulation */
    FlashSim_Init(&fs_Handle);
    /* Eraser log data region */
    logData_EraserLogRegion(&dataRegion);
    /* write data of flash simulation */

    for (i = 0; i < numPackage; i++)
    {
        memset(W_buff, i / 2, LOG_DATA_SIZE_OF_PACKAGE);
        retVal = FlashSim_Write(FLASH_START_ADDRESS + i * 64, W_buff, LOG_DATA_SIZE_OF_PACKAGE);
    }
    status_t stt = logData_FindLastPackage_Binary(&dataRegion, &currentPackagePos);
    logData_FindNextPackage(&dataRegion, &nextPackagePos, currentPackagePos);

    return ret;
}

void test_logData(void)
{
    /* Test Function Find Last Sector */
    if (TEST_PASS == test_FindLastSector())
    {
        printf("Test function Find Last Sector       : Pass\n");
    }
    else
    {
        printf("Test function Find Last Sector       : Failed\n");
    }

    /* Test Function Find Last Package */
    if (TEST_PASS == test_FindLastPackage())
    {
        printf("Test function Find Last Package      : Pass\n");
    }
    else
    {
        printf("Test function Find Last Package      : Failed\n");
    }

    /* Test Function Check Valid CRC  */
    if (TEST_PASS == test_CheckValidCRC())
    {
        printf("Test function Check Valid CRC        : Pass\n");
    }
    else
    {
        printf("Test function Check Valid CRC        : Failed\n");
    }

    /* Test Function Check Erase Log Region  */

    if (TEST_PASS == test_CheckEraseLogRegion())
    {
        printf("Test function Check Erase Log Region : Pass\n");
    }
    else
    {
        printf("Test function Check Erase Log Region : Failed\n");
    }

    /* Test Function CheckSetPackageIsUsed */

    if (TEST_PASS == test_CheckSetPackageIsUsed())
    {
        printf("Test function CheckSetPackageIsUsed  : Pass\n");
    }
    else
    {
        printf("Test function CheckSetPackageIsUsed  : Failed\n");
    }
    
    if (TEST_PASS == test_FindNextPackage())
    {
        printf("Test function FindNextPackage        : Pass\n");
    }
    else
    {
        printf("Test function FindNextPackage        : Failed\n");
    }
}

//int main(void)
//{
//    test_logData();
//
//    return 0;
//}