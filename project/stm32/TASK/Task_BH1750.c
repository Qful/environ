

#include "Tasks.h"
#include "I2C.h"
#include "IIC.h"
#include "delay.h"

#define BH1750_NUM     2

#define BH1750_Add  0x46

#define BH1750_ON   0x01
#define BH1750_CON  0x10
#define BH1750_ONE  0x20
#define BH1750_RSET 0x07

u8    BH1750_BUF[5]={0};
u16   LX_BUF[BH1750_NUM]={0};

void BH1750_Delay(u8 nms)
{
	  delay_ms(nms);
}

void Write_IIC_BH1750(u8 cmd)
{
    IIC_Start();              
    IIC_Write(BH1750_Add+0);   
		while(IIC_Wait_Ack());
		IIC_Write(cmd);  
		while(IIC_Wait_Ack());
		IIC_Stop();               
		BH1750_Delay(5);
}
void Write_I2C_BH1750(u8 cmd)
{
			I2C_Start();              
			I2C_Write(BH1750_Add+0);   
			while(I2C_Wait_Ack());
			I2C_Write(cmd);  
			while(I2C_Wait_Ack());
			I2C_Stop();               
			BH1750_Delay(5);
}


void Start_BH1750(u8 chan)
{
		if(chan & 0X03)
		{
				Write_IIC_BH1750(BH1750_ON);
				Write_I2C_BH1750(BH1750_ON);
				Write_IIC_BH1750(BH1750_RSET);	
				Write_I2C_BH1750(BH1750_RSET);	 		
				Write_IIC_BH1750(BH1750_ONE); 
				Write_I2C_BH1750(BH1750_ONE); 
		}
		else if(chan & 0X01)
		{				
			  Write_IIC_BH1750(BH1750_ON);
				Write_IIC_BH1750(BH1750_RSET);	 		
				Write_IIC_BH1750(BH1750_ONE); 			
		}	
		else if(chan & 0X02)
		{				
			  Write_I2C_BH1750(BH1750_ON);
				Write_I2C_BH1750(BH1750_RSET);	 		
				Write_I2C_BH1750(BH1750_ONE); 			
		}		
}


void Read_BH1750(u8 chan)
{ 
				Start_BH1750(2);	
				BH1750_Delay(150);
				if(chan & 0X01)
				{
						 IIC_Start();  
						 IIC_Write(BH1750_Add+1);  
					   while(IIC_Wait_Ack());
						 BH1750_BUF[0]=IIC_Read(1); 
						 BH1750_BUF[1]=IIC_Read(0); 
						 IIC_Stop();  
						 LX_BUF[0]=BH1750_BUF[0];
						 LX_BUF[0]=(LX_BUF[0]<<8)+BH1750_BUF[1]; 
						 LX_BUF[0]=(u16)LX_BUF[0]/1.2;
				}
				if(chan & 0X02)
				{		
						I2C_Start();                  
						I2C_Write(BH1750_Add+1); 
					  while(I2C_Wait_Ack());
						BH1750_BUF[2]=I2C_Read(1); 
						BH1750_BUF[3]=I2C_Read(0);  
					  I2C_Stop();  
						LX_BUF[1]=BH1750_BUF[2];
						LX_BUF[1]=(LX_BUF[chan]<<8)+BH1750_BUF[3]; 
						LX_BUF[1]=(u16)LX_BUF[1]/1.2;
				}			
				Write_Usart1(BH1750_BUF,5);
				
}

/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/
OS_TCB 		Task_GetLX_TCB;
CPU_STK 	Task_GetLX_STK[Task_GetLX_SIZE];

void Task_GetLX(void *p_arg)
{
		OS_ERR err;
		u16 result_lx;
		p_arg = p_arg;
	  
		while(1)
		{
				OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); 
				I2C_Port_Init();
			  IIC_Port_Init();
				Read_BH1750(3);
				OSTimeDlyHMSM(0,0,1,900,OS_OPT_TIME_HMSM_STRICT,&err); 
				printf("LX_task\n");	
		}
}







