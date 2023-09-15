#include "test_flash.h"
#include <stdio.h>

static FlashSim_Handle_Struct_t FlashHandle;

FlashSim_State_t FlashInit(void);
void FlashErrorCallback(void);

int main (void)
{
    uint8_t readBuff[1000];
    uint8_t writeBuff[1000];
    int indx = 0;
    int indy = 0;

    FlashInit();

//    for(indx =0; indx <1000; indx++)
//    {
//        writeBuff[indx] = indx % 15;
//    }
//    
//    if (FLASH_SIM_STATE_OK == FlashSim_Write(FLASH_START_ADDRESS + 15, writeBuff, 100))
//    {
//        printf(" true\n");
//    }
//    else
//    {
//        printf(" false\n");
//    }
//
//    FlashSim_Read(FLASH_START_ADDRESS, readBuff, 512);
//    FlashSim_ShowSector(1);
//    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
//    for(indx =0; indx <64; indx++)
//    {
//        for(indy =0; indy <8; indy++)
//        {
//           printf("%d\t", readBuff[indx*8+indy]);
//        }
//        printf("\n");
//    }

	TestFlash();
    return 0;
}

FlashSim_State_t FlashInit(void)
{
    FlashSim_State_t retVal = FLASH_SIM_STATE_OK;
    FlashHandle.ErrorCallbackPointer    = FlashErrorCallback;
    FlashHandle.lock                    = FLASH_SIM_UNLOCKED;
    FlashHandle.state                   = FLASH_SIM_STATE_OK;
    retVal = FlashSim_Init(&FlashHandle);
    
    return retVal;
}

void FlashErrorCallback(void)
{
	FlashHandle.state = FLASH_SIM_STATE_OK;
}
