#ifndef __IIC_H
#define __IIC_H

#include "Qitas.h"

void IIC_Port_Init(void);    //初始化IIC的IO口	
void IIC_SET(void);    //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号 成功则返回1
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Write(u8 txd);			//IIC发送一个字节
u8 IIC_Read(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
	  
#endif

