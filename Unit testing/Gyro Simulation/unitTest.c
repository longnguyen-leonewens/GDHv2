#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "gyro_sim.h"
#include "gyro.h"

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
	
	return state;
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
	state_test = GyroSim_ReadData(0, data, &temp);
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
	state_test = GyroSim_ReadData(7, data, &temp);
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
	state_test = GyroSim_ReadData(4, data, &temp);
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
	state_test = GyroSim_ReadData(8, data, &temp);
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
	state_test = GyroSim_ReadData(4, data, NULL);
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
	state_test = GyroSim_ReadData(8, data, NULL);
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

double GyroSim_MainTest(void)
{
	uint8_t pass        = 0;
	uint8_t no_pass     = 0;
	float perform_Test  = 0;
	uint8_t testCase    = 1;
	StatusTypeDef current_State;
	while (testCase != 0)
	{
		switch (testCase)
	{
    		case 1:
    			current_State = Test1_StartGyroSim();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
	    			no_pass++;
	    			printf("\nError test 1");
    			}
    			testCase++;
    		    break;
		
    		case 2:
    			current_State = Test2_StartGyroSim();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 2");
    			}
    			testCase++;
    		    break;
					    
    		case 3:
    			current_State = Test3_StartGyroSim();
    			if (current_State == ERROR_NONE)
    			{
			    	pass++;
			    }
			    else
		    	{
	     			no_pass++;
	     			printf("\nError test 3");
    			}
    			testCase++;
    		    break;

    		case 4:
    			current_State = Test4_GyroSim_Deinit();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 4");
	    		}
	    		testCase++;
    		    break;
		
    		case 5:
    			current_State = Test5_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 5");
    			}
    			testCase++;
    		    break;
		    
    		case 6:
    			current_State = Test6_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
	    		}
	    		else
    	 		{
	    			no_pass++;
	    			printf("\nError test 6");
    			}
	    		testCase++;
    		    break;
		    
    		case 7:
    			current_State = Test7_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 7");
    			}
    			testCase++;
    		    break;
		    
    		case 8:
    			current_State = Test8_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 8");
    			}
    			testCase++;
    		    break;
    		    
    		case 9:
    			current_State = Test9_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 9");
    			}
    			testCase++;
    		    break;
    		    
    		case 10:
    			current_State = Test10_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 10");
    			}
    			testCase++;
    		    break;
		    
    		case 11:
    			current_State = Test11_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 11");
    			}
	    		testCase++;
    		    break;
		    
    		case 12:
    			current_State = Test12_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 12");
	    		}
    			testCase++;
    		    break;
		    
	    	case 13:
    			current_State = Test13_GyrSim_ReadData();
    			if (current_State == ERROR_NONE)
    			{
    				pass++;
    			}
    			else
    			{
    				no_pass++;
    				printf("\nError test 13");
    			}
    			testCase++;
		        break;
		    
		    case 14:
		    	current_State = Test14_GyrSim_ReadData();
	    		if (current_State == ERROR_NONE)
    			{
			    	pass++;
		    	}
	    		else
    			{
			    	no_pass++;
			    	printf("\nError test 14");
		    	}
	    		testCase++;
    		    break;
	    
    		default:
			    perform_Test = (pass * 100)/(testCase - 1);
			    printf("\nPerformence = %f%%", perform_Test);
			    testCase = 0;
		    	break;
	    }
	}
	
	return perform_Test;
}

void Test_PrintALLData(void)
{
	double data[6];
	int16_t temp;

    // Initialize gyro data and start thread
    Gyro_Init();

    // Main program loop to read gyro data (you can implement your own logic here)
    printf("\n-------------------------------------------------------------------------------------");
    printf("\n| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|", "Gyro X", "Gyro Y", "Gyro Z", "Acce X", "Acce Y", "Acce Z", "Temp");
    printf("\n-------------------------------------------------------------------------------------");
    while (1) {
    	Gyro_ReadData(SIMULATOR_READ_ALL, data, &temp);
        // Read gyro data as needed
        printf("\n| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10.2f| %-10.2d|", data[0], data[1], data[2], data[3], data[4], data[5], *((int16_t*)&data[6]));
        // Sleep or perform other operations as needed
        usleep(1000); // Sleep for 100ms
    }
}

int main()
{
	//Test_PrintALLData();
    GyroSim_MainTest();
    return 0;
}
