#ifndef __USART_H
#define	__USART_H

#include "Qitas.h"

void USART1_INIT(void);
void NVIC_USART1(void);
void Write_Usart1_S(u8 *p);
u8 Write_Usart1_C(u8 ch);
void Write_Usart1(u8 *p,u16 cnt);

void USART3_INIT(void);
void NVIC_USART3(void);
void Write_Usart3_S(u8 *p);
u8 Write_Usart3_C(u8 ch);
void Write_Usart3(u8 *p,u16 cnt);

#endif /* __USART1_H */

