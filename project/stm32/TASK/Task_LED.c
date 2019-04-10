

#include "Qitas.h" 
#include "Tasks.h"

#define LED_L  GPIO_ResetBits(LED_PORT,LED_PIN)
#define LED_H  GPIO_SetBits(LED_PORT,LED_PIN)

OS_TCB 		Task_LED_TCB;
CPU_STK 	Task_LED_STK[LED0_STK_SIZE];



void Task_LED(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
			LED_L;
			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); 
			LED_H;
			OSTimeDlyHMSM(0,0,0,900,OS_OPT_TIME_HMSM_STRICT,&err); 
		  printf("LED_task\n");
	
	}
}
