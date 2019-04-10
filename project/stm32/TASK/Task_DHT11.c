
#include "Tasks.h"
#include "delay.h"

#define DHT_H   GPIO_SetBits(DHT11_PORT, DHT11_PIN)
#define DHT_L   GPIO_ResetBits(DHT11_PORT, DHT11_PIN)
#define DHT_I   GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN)
#define DHT_Wait   delay_us(35)

u8 DHT11_DATA[5];

void DHT_Delay(u16 nms)
{
	  u16 i;
		while(nms--) for(i=0;i<8400;i++);
}

void DHT11_IN_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
			GPIO_SetBits(DHT11_PORT,DHT11_PIN);
}

static void DHT11_OUT_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
			GPIO_SetBits(DHT11_PORT,DHT11_PIN);
}

static void DHT11_Rst(void)
{
	    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA,ENABLE );	
			DHT11_OUT_Init();
			DHT_L;
			DHT_Delay(19);
			DHT_H;
			DHT_Wait;
			DHT11_IN_Init();
}

static u8 DHT11_Check(void)
{
	DHT11_IN_Init();
	return (u8)DHT_I;
}


static u8 DHT11_Read_Bit(void)
{
		while(!DHT_I);
		DHT_Wait;
		if (DHT_I)
		{
				while(DHT_I);
				return 1;
		}
		return 0;
}
u8 DHT11_Read_Byte(void)
{
		int i;
		u8 Data = 0;
	  DHT11_IN_Init();
		for (i = 0; i < 8; i++)
		{
				Data <<= 1;
				Data |= DHT11_Read_Bit();
		}
		return Data;
}

u8 Convert_DHT11(void)
{
		u8 i = 0;
		DHT11_Rst();
		if (DHT11_Check() == 0)
		{
			while (!DHT_I);
			while(DHT_I);
			for (i = 0; i< 5; i++)
			{
				 DHT11_DATA[i] = DHT11_Read_Byte();
			}
			while(!DHT_I);
			DHT11_OUT_Init();
			DHT_H;
			if ((DHT11_DATA[0] + DHT11_DATA[1] + DHT11_DATA[2] + DHT11_DATA[3]) ==DHT11_DATA[4])
			{
				 return BACK_SUCCESS;
			}
			else
			{
				for (i = 0; i< 5; i++)
				{
					 DHT11_DATA[i] = 0;
				}
			}
		}
		return BACK_ERROR;
}


/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/
OS_TCB 		Task_GetDHT_TCB;
CPU_STK 	Task_GetDHT_STK[Task_GetDHT_SIZE];

void Task_GetDHT(void *p_arg)
{
		OS_ERR err;
	  u8 cnt;
		p_arg = p_arg;		 
		while(1)
		{
				OSSchedLock(&err);
				DHT11_OUT_Init();
				if(Convert_DHT11()==BACK_SUCCESS) 
				{
					 if(DHT11_DATA[2]>27)
					 {
						 OSTaskChangePrio(&Task_GetDHT_TCB,4,&err);
						 if(OS_ERR_NONE == err)
							{
									Write_Usart1_S("Task_GetDHT Change Prio To 4 Success\n");
							}
					 }
					 Write_Usart1(DHT11_DATA,6);	
				}
				OSSchedUnlock(&err);				
				OSTimeDlyHMSM(0,0,0,900,OS_OPT_TIME_HMSM_STRICT,&err); 
				printf("dht11_task\n");	
		}
}

 




 