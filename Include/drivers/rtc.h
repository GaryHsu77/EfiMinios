#ifndef RTC_H
#define RTC_H

#define RTC_ADDRESS_PORT 0x70
#define RTC_DATA_PORT 0x71

// address definitions for address port
#define RTC_CLOCK_SECOND 0x00
#define RTC_ALARM_SECOND 0x01
#define RTC_CLOCK_MINUTE 0x02
#define RTC_ALARM_MINUTE 0x03
#define RTC_CLOCK_HOUR 0x04
#define RTC_ALARM_HOUR 0x05
#define RTC_CLOCK_DAY 0x06
#define RTC_CLOCK_DATE 0x07
#define RTC_CLOCK_MONTH 0x08
#define RTC_CLOCK_YEAR 0x09
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_C 0x0C
#define RTC_REG_D 0x0D

#define RTC_PF 0x40
#define RTC_AF 0x20
#define RTC_UF 0x10

#define PERIODIC_DELAY_TIME 10 //10*0.5 sec= 5sec

typedef struct{
    BOOLEAN HasUpdate;
    BOOLEAN HasAlarm;
    BOOLEAN HasPeriodic;
    UINT8 PeriodicCounter;
    UINT8 Second;
    UINT8 Minute;
    UINT8 Hour;
    UINT8 Day;
    UINT8 Date;
    UINT8 Month;
    UINT8 Year;
    UINT8 RegisterA;
    UINT8 RegisterB;
    UINT8 RegisterC;
    UINT8 RegisterD;
    OS_EVENT RtcEvent;
}RTC_CONTROL;

extern RTC_CONTROL *pOsDriverRtc;

void RtcInit(void);
void RtcHandler(void);
void RtcByteWrite(UINT8 Address,UINT8 Data);
UINT8 RtcByteRead(UINT8 Address);

#endif