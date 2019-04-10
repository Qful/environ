

#include "Tasks.h"
#include "I2C.h"
#include "IIC.h"
#include "delay.h"


#define SI7021_Addr 				0x80
#define	HUMI_HOLD_MASTER		0xE5
#define	TEMP_HOLD_MASTER		0xE3
#define	HUMI_NOHOLD_MASTER	0xF5
#define	TEMP_NOHOLD_MASTER	0xF3

float result_temp=0;
float result_humi=0;

u8 BUF[4]={0};
u16 result=0;

u8 Sys_status=0;

void SI7021_Delay(uint16_t nms) 
{
	u16 i;
	while(nms--) for(i=0;i<8400;i++);
}


void Cmd_Write_SI7021(u8 cmd)
{
    I2C_Start();                
    I2C_Write(SI7021_Addr+0); 
		if(I2C_Wait_Ack())
		{
			Sys_status=0x12;
		}
    I2C_Write(cmd);          
		if(I2C_Wait_Ack())
		{
			Sys_status=0x14;
		}
    //SI7021_SendByte(REG_data);  
    I2C_Stop();                 
		SI7021_Delay(5);
}

void Read_SI7021(void)
{   	
    I2C_Start();                        
    I2C_Write(SI7021_Addr+1);       
		if(I2C_Wait_Ack())
		{
			Sys_status=0x16;
		}
		SI7021_Delay(12);
		BUF[0]=I2C_Read(1); 
		BUF[1]=I2C_Read(0); 
    I2C_Stop();               
    SI7021_Delay(5);
}

void Convert_Humi(void)
{
	Cmd_Write_SI7021(0xE5);
	Read_SI7021();
	result=BUF[0];
	result=(result<<8)+BUF[1];  
	result_humi=(result*125.0/65536) - 6;
}

void Convert_Temp(void)
{
	Cmd_Write_SI7021(0xE3);
	Read_SI7021();
	result=BUF[0];
	result=(result<<8)+BUF[1];  
	result_temp=(result*175.72/65536) - 46.85;
	Write_Usart1_S(BUF);
}

/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/
OS_TCB 		Task_SI_TEMP_TCB;
CPU_STK 	Task_SI_TEMP_STK[Task_SI_TEMP_SIZE];

void Task_SI_TEMP(void *p_arg)
{
		OS_ERR err;
	  char *outusart;
		p_arg = p_arg;	  
		while(1)
		{
				I2C_Port_Init();
			  //IIC_Port_Init();
				Convert_Temp();
			 // sprintf(outusart,"%f",result_temp); 
				OSTimeDlyHMSM(0,0,0,900,OS_OPT_TIME_HMSM_STRICT,&err); 
				//printf("LX_task\n");	
		}
}

OS_TCB 		Task_SI_HUMI_TCB;
CPU_STK 	Task_SI_HUMI_STK[Task_SI_HUMI_SIZE];
void Task_SI_HUMI(void *p_arg)
{
		OS_ERR err;
	  char *outusart;
		p_arg = p_arg;	  
		while(1)
		{
				I2C_Port_Init();
			  IIC_Port_Init();
			  Convert_Humi();
				sprintf(outusart,"%f",result_humi); 
			  Write_Usart1_S(outusart);
				OSTimeDlyHMSM(0,0,0,900,OS_OPT_TIME_HMSM_STRICT,&err); 
				printf("LX_task\n");	
		}
}



