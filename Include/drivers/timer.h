#ifndef TIMER_H
#define TIMER_H

#define TIMER_PORT      0x40	 // I/O port base for 8254  
#define TIMER0          0x40	 // I/O port for timer 0   
#define TIMER1          0x41	 // I/O port for timer 1   
#define TIMER2          0x42	 // I/O port for timer 2  
#define TIMER_MODE      0x43	 // I/O port for timer mode control   

#define RATE_GENERATOR	0x34	 // timer 0,lsb-msb,rate generator,binary   
#define TIMER_FREQ	    1193182L // clock frequency for timer in PC AT   
#define HZ		        1000	 // 1000hz, divider=TIMER_FREQ/1000~1200

typedef struct{
    //U16 Timer;
    UINT16 TaskTick;
    OS_TIMER MyTimer;
}TIMER_CONTROL;

extern TIMER_CONTROL *pOsDriverTimer;

VOID TimerInit(VOID);
VOID TimerHandler(VOID);

#endif
