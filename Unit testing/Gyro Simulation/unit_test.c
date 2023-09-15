#include "gyro.h"
#include "gyro_sim.h"

#define FALSE_FREQUENCY            (0U)
#define MIN_FREQUENCY              (60U)
#define MAX_FREQUENCY              (0xFFFFFFFF)

StatusTypeDef Test1_StartGyroSim(void)
{
	StatusTypeDef state;
	if(ERROR == GyroSim_StartSimulation(FALSE_FREQUENCY))
    {
    	state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
}

StatusTypeDef Test2_StartGyroSim(void)
{
	StatusTypeDef state;
	if(ERROR == GyroSim_StartSimulation(MIN_FREQUENCY))
    {
    	state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
}

StatusTypeDef Test3_StartGyroSim(void)
{
	StatusTypeDef state;
	if(ERROR == GyroSim_StartSimulation(MAX_FREQUENCY))
    {
    	state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
}

StatusTypeDef Test4_GyroSim_Deinit(void)
{
	StatusTypeDef state;
	GyroSim_StopSimulation();
	if (return_test_deinit() == 0)
	{
		state = ERROR_NONE;
	}
	else
	{
		state =ERROR;
	}
	
	return state;
}

StatusTypeDef Test5_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(0, &data, &temp);
	if(state_test == ERROR_NONE)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test6_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(7, &data, &temp);
	if(state_test == ERROR_NONE)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test7_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(4, &data, &temp);
	if(state_test == ERROR_NONE)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test8_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(8, &data, &temp);
	if(state_test == ERROR)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test9_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(4, NULL, &temp);
	if(state_test == ERROR)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test10_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(4, &data, NULL);
	if(state_test == ERROR)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test11_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(4, NULL, NULL);
	if(state_test == ERROR)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test12_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(8, &data, NULL);
	if(state_test == ERROR)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test13_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(8, NULL, &temp);
	if(state_test == ERROR)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

StatusTypeDef Test14_GyrSim_ReadData(void)
{
	StatusTypeDef state;
	StatusTypeDef state_test;
	double data[6];
	int16_t temp;
	state_test = GyroSim_ReadData(8, NULL, NULL);
	if(state_test == ERROR)
	{
		state = ERROR_NONE;
	}
	else
	{
		state = ERROR;
	}
	
	return state;
}

void GyroSim_MainTest(void)
{
	
}
