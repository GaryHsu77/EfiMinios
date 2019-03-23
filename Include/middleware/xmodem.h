#ifndef XMODEM_H
#define XMODEM_H

#define XMODEM_BLOCK_SIZE 128
#define XMODEM_RETRIES    20
#define XMODEM_SOH        0x01  // start of header 128 block size
#define XMODEM_STX        0x02  // start of header 1024 block size
#define XMODEM_EOT        0x04  // end of text
#define XMODEM_ACK        0x06  // acknoledge
#define XMODEM_NAK        0x15 // negative acknoledge
#define XMODEM_ETB        0x17 // negative acknoledge
#define XMODEM_CAN        0x18 // cancel
#define XMODEM_CHAR_C     0x43 // char c

typedef struct{
    UINT8  State;
    UINT8  SubState;
    UINT8  BlockNumber;
    UINT32 ByteCounter;
    UINT32 TotalBlock;
    UINT8 *pMemory;
    UINT8 Put;
    UINT8 Data[130];
    OS_TIMER XmodemTimer;
}XMODEM_CONTROL;

extern void XmodemInit(XMODEM_CONTROL *pXmodemCtrl);
extern void XmodemSvc(XMODEM_CONTROL *pXmodemCtrl);
extern BOOLEAN XmodemStatusCheck(XMODEM_CONTROL *pXmodemCtrl);
extern BOOLEAN XmodemCrcCheck(UINT8 *pData);

#endif

