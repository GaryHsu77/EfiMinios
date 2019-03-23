#ifndef UART1_H
#define UART1_H

#define COM1_BASE 0x3f8 //3f8~3ff
//#define COM2_BASE 0x2f8 //2f8~2ff..defined in uart2.h
#define COM3_BASE 0x3e8 //3e8~3ef
#define COM4_BASE 0x2e8 //2e8~2ef 

#define RXREG 0 //use with DLAB=0 (LCR.7) receive buffer for read,transmitter holding register for write
#define TXREG 0 //USE with DLAB=0 (LCR.7)
#define IER  1 //Interrupt Enable Register 
#define IIR  2 //Interrupt Identification Register  (read only)
#define FCR  2 //Fifo Control Register (write only)      
#define LCR  3 //Line Control Register 
#define MCR  4 //Modem Control Register      
#define LSR  5 //Line Status Register        
#define MSR  6 //Modem Status Register       
#define SR   7 //Scratch Register           
#define DLLR 0 //use with DLAB=1 (LCR.7) Divisor Latch Low Register  
#define DLHR 1 //use with DLAB=1 (LCR.7) Divisor Latch High Register

#define COM1_INT_EDA  0x01
#define COM1_INT_THRE 0x02
#define COM1_INT_RLS  0x04
#define COM1_INT_MS   0x08

#define COM1_INTERRUPTS (COM1_INT_EDA|COM1_INT_THRE|COM1_INT_RLS)

#define COM1_IID_MS      0x00
#define COM1_IID_TXEMPTY 0x01
#define COM1_IID_RXRDY   0x02
#define COM1_IID_RLS     0x03
#define COM1_IID_TIMEOUT 0x06

#define COM1_LSR_DR 0x01
#define COM1_LSR_OE 0x02
#define COM1_LSR_PE 0x04
#define COM1_LSR_FE 0x08
#define COM1_LSR_BI 0x10
#define COM1_LSR_THRE 0x20
#define COM1_LSR_TEMT 0x40
#define COM1_LSR_ER 0x80


// baudrate setting for clock 1.8342mhz...i find this in bochs source code
#define BAUDRATE_115200 0x01
#define BAUDRATE_57600  0x02
#define BAUDRATE_38400  0x03
#define BAUDRATE_19200  0x06
#define BAUDRATE_9600   0x0c
#define BAUDRATE_4800   0x18
#define BAUDRATE_2400   0x30

#define UART1_MAX_BUFFER_SIZE 500

typedef struct{
    UINT8 State;
    UINT8 HasData;
    UINT8 RxData;
    UINT8 UartTxTransmit; 
    UINT8 TxBufferStatus;
    UINT8 RxBufferStatus;
    UINT32 TxPut;
    UINT32 TxGet;
    UINT8  *pTxDataBuffer;
    UINT32 RxPut;
    UINT32 RxGet;
    UINT8  *pRxDataBuffer;
    OS_EVENT Uart1Event;
}UART1_CONTROL;

extern UART1_CONTROL *pOsDriverUart1;

void Uart1Init(void);
void Uart1Handler(void);
void Uart1Svc(void);
void Uart1BufferReset(void);
UINT8 Uart1RxBufferCheck(void);
UINT8 Uart1RxBufferCheckIsr(void);
void Uart1RxBufferPutIsr(UINT8 Data);
UINT8 Uart1RxBufferGet(void);
UINT8 Uart1TxBufferCheck(void);
void Uart1TxBufferPut(UINT8 Data);
UINT8 Uart1TxBufferGet(void);
UINT8 Uart1TxBufferCheckIsr(void);
UINT8 Uart1TxBufferGetIsr(void);
UINT8 Uart1TxBufferGetIsr(void);

#endif
