#ifndef UART2_H
#define UART2_H

#define COM2_BASE 0x2f8 //2f8~2ff

typedef struct{
    UINT8 State;
    UINT8 HasData;
    UINT8 RxData;
    OS_EVENT Uart2Event;
}UART2_CONTROL;

extern UART2_CONTROL *pOsDriverUart2;

void Uart2Init(void);
void Uart2Handler(void);

#endif
