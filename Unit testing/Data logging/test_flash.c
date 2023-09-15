#include <stdio.h>
#include <string.h>
#include "test_flash.h"

static FlashSim_Handle_Struct_t FlashHandle;

static void FlashErrorCallback(void);
static FlashSim_State_t FlashInit(void);
static TestFlashStatus_t TestFlash_InitFunc(void);
static TestFlashStatus_t TestFlash_ReadFlashFunc(void);
static TestFlashStatus_t TestFlash_WriteFlashFunc(void);
static TestFlashStatus_t TestFlash_EraseFlashFunc(void);

TestFlashStatus_t TestFlash(void)
{
	TestFlashStatus_t retVal = TEST_PASS;

	/* Test Function write data  */
	if (TEST_PASS == TestFlash_WriteFlashFunc())
	{
		printf("Test function write data to flash      : Pass\n\n");
	}
	else
	{
		printf("Test function write data to flash      : Failed\n\n");
	}

	/* Test Function Read data  */
	if (TEST_PASS == TestFlash_ReadFlashFunc())
	{
		printf("Test function Read data from flash     : Pass\n\n");
	}
	else
	{
		printf("Test function Read data from flash     : Failed\n\n");
	}

	/* Test Function erase data flash  */
	if (TEST_PASS == TestFlash_EraseFlashFunc())
	{
		printf("Test function erase data in flash     : Pass\n\n");
	}
	else
	{
		printf("Test function erase data in flash     : Failed\n\n");
	}

	/* Test Function Init flash */
	if (TEST_PASS == TestFlash_InitFunc())
	{
		printf("Test function Init flash              :	Pass\n\n");
	}
	else
	{
		printf("Test function Init flash              :	Failed\n\n");
	}
	return retVal;
}


static TestFlashStatus_t TestFlash_InitFunc(void)
{
	TestFlashStatus_t retVal = TEST_PASS;
	FlashSim_Handle_Struct_t FlashSimHandler;
	FlashSim_Handle_Struct_t* pFlashSimHandler[2] = { &FlashSimHandler, NULL };
	FlashSim_State_t resultVal[2] = { FLASH_SIM_STATE_OK,FLASH_SIM_STATE_ERROR_INVALID_PARAM };
	uint32_t testFailedCount = 0;
	int idx = 0;

	FlashSimHandler.lock = FLASH_SIM_UNLOCKED;
	FlashSimHandler.state = FLASH_SIM_STATE_OK;
	FlashSimHandler.ErrorCallbackPointer = NULL;

	for (idx = 0; idx < 2; idx++)
	{
		if (resultVal[idx] != FlashSim_Init(pFlashSimHandler[idx]))
		{
			retVal = TEST_FAILED;
			testFailedCount++;
			printf("Test function Init flash| test case : %d :	Failed\n", idx);
		}
	}
	printf("Count test 'FlashSim_Init' failed : %d \n", testFailedCount);

	return retVal;
}


static TestFlashStatus_t TestFlash_ReadFlashFunc(void)
{
	TestFlashStatus_t retVal = TEST_PASS;
	uint8_t buffTest[FLASH_SIZE];
	uint32_t startAddrTestValArr[5] = { FLASH_START_ADDRESS - 2, 			\
										FLASH_START_ADDRESS,				\
										FLASH_START_ADDRESS + 2,				\
										FLASH_START_ADDRESS + FLASH_SIZE - 1,	\
										FLASH_START_ADDRESS + FLASH_SIZE + 2 };
	uint8_t* buffTestValArr[2] = { buffTest, NULL };
	uint32_t sizeTestValArr[4] = { 0, 2, FLASH_SIZE, FLASH_SIZE + 1 };
	uint32_t testFailedCount = 0;
	uint16_t idx = 0;
	uint16_t idy = 0;
	uint16_t idz = 0;
	
	static FlashSim_State_t resultVal[5][2][4] = { \
		/* 0-7 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 8-15 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_OK,FLASH_SIM_STATE_OK, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 16-23 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_OK,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 24-31 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 32-39 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}} };

	for (idx = 0; idx < 5; idx++)
	{
		for (idy = 0; idy < 2; idy++)
		{
			for (idz = 0; idz < 4; idz++)
			{
				FlashSim_State_t result = FlashSim_Read(startAddrTestValArr[idx], buffTestValArr[idy], sizeTestValArr[idz]);
				if (resultVal[idx][idy][idz] != result)
				{
					retVal = TEST_FAILED;
					testFailedCount++;
					printf("Test function 'FlashSim_Read' test case %d :	Failed %d\n", idx * 2 * 4 + idy * 4 + idz, result);
				}
			}
		}
	}

	printf("Count test 'FlashSim_Read' failed : %d \n", testFailedCount);

	return retVal;
}


static TestFlashStatus_t TestFlash_WriteFlashFunc(void)
{
	TestFlashStatus_t retVal = TEST_PASS;
	uint8_t buffTest[FLASH_SIZE];
	uint32_t startAddrTestValArr[5] = { FLASH_START_ADDRESS - 1, \
										FLASH_START_ADDRESS,\
										FLASH_START_ADDRESS + 1,\
										FLASH_START_ADDRESS + FLASH_SIZE - 1,\
										FLASH_START_ADDRESS + FLASH_SIZE };
	uint8_t* buffTestValArr[2] = { buffTest, NULL };
	uint32_t sizeTestValArr[4] = { 0, 2, FLASH_SIZE - FLASH_START_ADDRESS, FLASH_SIZE + 1 };
	uint32_t testFailedCount = 0;
	uint16_t idx = 0;
	uint16_t idy = 0;
	uint16_t idz = 0;

	/* 0-7 */
	static FlashSim_State_t resultVal[5][2][4] = { {{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
														{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 8-15 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_OK,FLASH_SIM_STATE_OK, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 16-23 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_OK,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 24-31 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}},\
		/* 32-39 */
		{{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE,FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE, FLASH_SIM_STATE_ERROR_ACCESS_OUT_RANGE},\
		{FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM,FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM}} };


	memset(buffTest, 0xA5, FLASH_SIZE);
	for (idx = 0; idx < 5; idx++)
	{
		for (idy = 0; idy < 2; idy++)
		{
			for (idz = 0; idz < 4; idz++)
			{
				FlashSim_EraseMultiSector(0, 64);
				FlashSim_State_t result = FlashSim_Write(startAddrTestValArr[idx], buffTestValArr[idy], sizeTestValArr[idz]);
				if (resultVal[idx][idy][idz] != result)
				{
					FlashSim_ShowSector(63);
					FlashSim_ShowSector(64);
					retVal = TEST_FAILED;
					testFailedCount++;
					//					printf("Test function write| test case %d :	Failed\n", idx*2*4 +idy *4 +idz);
					printf("Test function 'FlashSim_Write' test case %d :	Failed %d\n", idx * 2 * 4 + idy * 4 + idz, result);



				}
			}
		}
	}
	printf("Count test 'FlashSim_Write' failed : %d \n", testFailedCount);

	return retVal;
}



static TestFlashStatus_t TestFlash_EraseFlashFunc(void)
{
	TestFlashStatus_t retVal = TEST_PASS;

	uint32_t SectorIndexTestValArr[4] = { 0, 	\
											5,	\
											(FLASH_SIZE / SECTOR_SIZE) - 1,\
											FLASH_SIZE / SECTOR_SIZE };

	uint32_t NumOfSecTestValArr[4] = { 0,  \
										2,	\
										FLASH_SIZE / SECTOR_SIZE, \
										FLASH_SIZE / SECTOR_SIZE + 1 };

	FlashSim_State_t resultVal[4][4] = \
	{FLASH_SIM_STATE_OK, FLASH_SIM_STATE_OK, FLASH_SIM_STATE_OK, FLASH_SIM_STATE_ERROR_INVALID_PARAM, \
		FLASH_SIM_STATE_OK, FLASH_SIM_STATE_OK, FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM, \
		FLASH_SIM_STATE_OK, FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM, \
		FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM, FLASH_SIM_STATE_ERROR_INVALID_PARAM};

	uint32_t testFailedCount = 0;
	uint16_t idx = 0;
	uint16_t idy = 0;

	for (idx = 0; idx < 4; idx++)
	{
		for (idy = 0; idy < 4; idy++)
		{
			if (resultVal[idx][idy] != FlashSim_EraseMultiSector(SectorIndexTestValArr[idx], NumOfSecTestValArr[idy]))
			{
				retVal = TEST_FAILED;
				testFailedCount++;
				printf("Test function 'FlashSim_EraseMultiSector' test case %d :	Failed\n", idx * 4 + idy);
			}
		}
	}
	printf("Count test 'FlashSim_EraseMultiSector' failed : %d \n", testFailedCount);

	return retVal;
}


void FlashErrorCallback(void)
{
	FlashHandle.state = FLASH_SIM_STATE_OK;
}


FlashSim_State_t FlashInit(void)
{
	FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
	FlashHandle.ErrorCallbackPointer = FlashErrorCallback;
	FlashHandle.lock = FLASH_SIM_UNLOCKED;
	FlashHandle.state = FLASH_SIM_STATE_OK;
	retVal = FlashSim_Init(&FlashHandle);

	return retVal;
}

int main(void)
{
	FlashInit();

	TestFlash();

	return 0;
}
