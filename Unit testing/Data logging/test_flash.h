#ifndef _TEST_FLASH_H_
#define _TEST_FLASH_H_

#include "flash_sim.h"
typedef enum
{
	TEST_PASS = 0x00,
	TEST_FAILED
}TestFlashStatus_t;

TestFlashStatus_t TestFlash(void);

#endif /* _TEST_FLASH_H_ */