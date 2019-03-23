#ifndef LPTPORT1_H
#define LPTPORT1_H

#define LPT1_BASE 0x378 //0x378~0x37f
//#define LPT2_BASE 0x278 //0x278~0x27f...declaration in lptport2.h
#define LPT3_BASE 0x3bc //??this port is used parrallel port which was incorporated onto video card
                        //??this port don't support ECP address
                        //??this port is not used any more in 80x86 pc.

#define LPT1_DATA_PORT     LPT1_BASE
#define LPT1_STATUS_PORT   (LPT1_BASE+1)
#define LPT1_CONTROL_PORT  (LPT1_BASE+2)

#define LPT_CONTORL_STROBE   0x01
#define LPT_CONTORL_AUTOFDXT 0x02
#define LPT_CONTORL_INITB    0x04
#define LPT_CONTORL_SLCTIN   0x08
#define LPT_CONTORL_INTEN    0x10 //interrupt enable...we can use this as external interrupt
#define LPT_CONTORL_DIR_READ 0x20 //data port direction...0 for data port output(write),1 for data port input(read)
#define LPT_CONTORL_BIT6     0x40 //reserved
#define LPT_CONTORL_BIT7     0x80 //reserved

#define LPT_STATUS_ERRORB  0x08
#define LPT_STATUS_SLCT    0x10
#define LPT_STATUS_PE      0x20
#define LPT_STATUS_ACKNLGB 0x40
#define LPT_STATUS_BUSYB   0x80

typedef struct{
    UINT8 State;
    UINT8 Data;
    UINT8 Status;
    UINT8 Control;
}LPT1_CONTROL;

extern LPT1_CONTROL *pOsDriverLpt1;

void Lpt1Init(void);
void Lpt1Handler(void);
void Lpt1Svc(void);
UINT8 Lpt1DataRegistRead(void);
void Lpt1DataRegistWrite(UINT8 Data);
UINT8 Lpt1StatusRegisterRead(void);
void Lpt1ControlPortWrite(UINT8 Data);
void Lpt1DataSetOutput(void);
void Lpt1DataSetInput(void);
void Lpt1InterruptEnable(void);
void Lpt1InterruptDisable(void);
#endif