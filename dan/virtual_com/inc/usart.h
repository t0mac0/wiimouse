// usart.h

#ifndef __STM32F_USART
#define __STM32F_USART


void InitUSART2(void);
void InitUSART3(void);

void Uart2SendChar(unsigned char c);
void Uart3SendChar(unsigned char c);

unsigned char Uart2ReadChar(void);
unsigned char Uart3ReadChar(void);

void Uart2WriteStr(unsigned char* s);
void Uart3WriteStr(unsigned char* s);

#endif


