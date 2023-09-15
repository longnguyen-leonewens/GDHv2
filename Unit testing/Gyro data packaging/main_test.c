
#include "gyropacket.h"
#include <stdio.h>

ErrorStatus result = ERROR;
int i;
uint8_t* array_NULL = NULL;
uint8_t array[64] = {0xAB,0xCD\
					,0x01\
					,0x11,0x22,0x33,0x44,0x55,0x66\
					,0xf6,0x41,0x96,0x5,0x13,0x9f,0x1c,0x40\
					,0x1,0x35,0xb5,0x6c,0xad,0xaf,0x11,0xc0\
					,0x4e,0x9a,0x6,0x45,0xf3,0,0xe1,0x3f\
					,0xd5,0x24,0x78,0x43,0x1a,0xa5,0x16,0x40\
					,0xd1,0xcb,0x28,0x96,0x5b,0x5a,0xfd,0xbf\
					,0x9a,0x99,0x99,0x99,0x99,0x99,0xc9,0x3f\
					,0xBB,0xAA\
					,0\
					,0,0};
Gyro_DataFrameTypeDef* pFrame_NUll = NULL;
Gyro_DataFrameTypeDef pFrame;
Gyro_DataFrameTypeDef pFrame_result = {.Fields.Preamble	  = {0xAB,0xCD},\
									   .Fields.PackageVer = 0x01,\
									   .Fields.Timestamp  = {0x11,0x22,0x33,0x44,0x55,0x66},\
									   .Fields.Data 	  = {.axisX = 7.155346,\
								   					         .axisY = -4.42156,\
								   					         .axisZ = 0.531366,\
								   					         .acceX = 5.661233,\
								   					         .acceY = -1.83456,\
								   					         .acceZ = 0.2,\
								   					         .temp  = 0xAABB},\
									   .Fields.Reserved   = 0,\
									   .Fields.Used       = 0,\
									   .Fields.CRC 	      = 0};
Gyro_ParamsTypeDef* pSensorData_NULL = NULL;
Gyro_ParamsTypeDef pSensorData;
Gyro_ParamsTypeDef pSensorData_result = {.axisX = 7.155346,
								  		 .axisY = -4.42156,
								  		 .axisZ = 0.531366,
								  		 .acceX = 5.661233,
								  		 .acceY = -1.83456,
								  		 .acceZ = 0.2,
								  		 .temp  = 0xAABB};


			  
void Test_GyroPackage_build(void)
{
	printf("Testcases of GyroPackage_Build:\n");
	printf("Testcase 1 the first param = NULL\n");	
	result = GyroPackage_Build(pFrame_NUll,&pSensorData);
	printf("%d",result);
	if(ERROR == result)
	{
		printf("testcase is fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}

	printf("testcase 2 the Data param = NULL\n");
	result = GyroPackage_Build(&pFrame,pSensorData_NULL);
	if(ERROR == result)
	{
		printf("testcase is fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}



	printf("testcase 3 two param = NULL\n");
	result = GyroPackage_Build(pFrame_NUll,pSensorData_NULL);
	if(ERROR == result)
	{
		printf("testcase is fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}
	
	printf("testcases 4 two param is valid\n");
	result = GyroPackage_Build(&pFrame,&pSensorData_result);
	if(ERROR == result)
	{
		printf("testcase is fail\n");
	}
	else
	{
		if(pFrame_result.Fields.Data.acceX == pFrame.Fields.Data.acceX &&
		   pFrame_result.Fields.Data.acceY == pFrame.Fields.Data.acceY &&
		   pFrame_result.Fields.Data.acceZ == pFrame.Fields.Data.acceZ &&
		   pFrame_result.Fields.Data.axisX == pFrame.Fields.Data.axisX &&
		   pFrame_result.Fields.Data.axisY == pFrame.Fields.Data.axisY &&
		   pFrame_result.Fields.Data.axisZ == pFrame.Fields.Data.axisZ &&
		   pFrame_result.Fields.Data.temp == pFrame.Fields.Data.temp )
		{
			printf("testcase is success\n");
		}
		else
		{
			printf("testcase is fail\n");
		}
	}	
}

void Test_GyroPackage_PackageToArray(void)
{
	printf("testcases of GyroPackage_PackageToArray\n");
	printf("testcase 1 the Data input = NULL\n");
	result = GyroPackage_PackageToArray(pFrame_NUll,array);
	if (ERROR == result)
	{
		printf("testcase iS fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}


	printf("testcase 2 the second param = NULL\n");
	result = GyroPackage_PackageToArray(&pFrame,array_NULL);
	if (ERROR == result)
	{
		printf("testcase if fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}


	printf("testcase 3 2 param = NULL\n");
	result = GyroPackage_PackageToArray(pFrame_NUll,array_NULL);
	if (ERROR == result)
	{
		printf("testcase iS fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}

	printf("testcase 4 2 param is valid\n");
	result = GyroPackage_PackageToArray(&pFrame_result,array);
	if (ERROR == result)
	{
		printf("testcase if fail\n");
	}
	else
	{
		if(strcmp(array,pFrame_result.ByteFrame))
		{
			printf("testcase is fail\n");
		}
		else
		{
			printf("testcase is success\n");
		}
		
	}
}



void Test_GyroPackage_ArrayToPackage(void)
{
	printf("testcases of GyroPackage_ArrayToPackage\n");
	printf("testcase 1 the Data input = NULL\n");
	result = GyroPackage_ArrayToPackage(array,pFrame_NUll);
	if (ERROR == result)
	{
		printf("testcase iS fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}


	printf("testcase 2 the second param = NULL\n");
	result = GyroPackage_ArrayToPackage(array_NULL,&pFrame);
	if (ERROR == result)
	{
		printf("testcase iS fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}


	printf("testcase 3 2 param = NULL\n");
	result = GyroPackage_ArrayToPackage(array_NULL,pFrame_NUll);
	if (ERROR == result)
	{
		printf("testcase iS fail\n");
	}
	else
	{
		printf("testcase is success\n");
	}

	printf("testcase 4 2 param is valid\n");
	result = GyroPackage_ArrayToPackage(array,&pFrame_result);
	if (ERROR == result)
	{
		printf("testcase is fail\n");
	}
	else
	{
		if(strcmp(array,pFrame_result.ByteFrame))
		{
			printf("testcase is fail\n");
		}
		else
		{
			printf("testcase is success\n");
		}
	}
}
ErrorStatus main_test_job3()
{
	Test_GyroPackage_build();
	Test_GyroPackage_ArrayToPackage();
	Test_GyroPackage_PackageToArray();
	return SUCCESS;
}


