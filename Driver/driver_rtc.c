#include <includes.h>

RTC_CONTROL *pOsDriverRtc;

VOID RtcInit(VOID)
{
	EFI_STATUS Status ;	

	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(RTC_CONTROL),&pOsDriverRtc);
	if(Status != EFI_SUCCESS)return;
    //PicIrqDisable(IRQ8_RTC);
    pOsDriverRtc->HasUpdate=FALSE;
    pOsDriverRtc->HasAlarm=FALSE;
    pOsDriverRtc->HasPeriodic=FALSE;
    pOsDriverRtc->PeriodicCounter=PERIODIC_DELAY_TIME;
    pOsDriverRtc->Second=0;
    pOsDriverRtc->Minute=0;
    pOsDriverRtc->Hour=0;
    pOsDriverRtc->Day=0;
    pOsDriverRtc->Date=0;
    pOsDriverRtc->Month=0;
    pOsDriverRtc->Year=0;
    pOsDriverRtc->RegisterA=0x2f; // divider 32.768K,periodic interrupt 500 ms
    pOsDriverRtc->RegisterB=0x50; // update int,binary,24 hour, 
    pOsDriverRtc->RegisterC=0;
    pOsDriverRtc->RegisterD=0;
    //RtcByteWrite(RTC_REG_A,pOsDriverRtc->RegisterA);
    //RtcByteWrite(RTC_REG_B,pOsDriverRtc->RegisterB);
    OsEventAdd(&pOsDriverRtc->RtcEvent,"DRIVER_RTC",OS_EVENT_RTC);
    //InterruptIrqHandlerSet(IRQ8_RTC,RtcHandler);
    //PicIrqEnable(IRQ8_RTC);
	SystemGuiStringPrint(L">>> RtcInit end      <<<<<<<<<<\n");
}

VOID RtcHandler(VOID)
{
	UINT8 i;

	i=RtcByteRead(RTC_REG_C);
/*
    if(i&RTC_PF){ //periodic interrupt...for real time system use
        pOsDriverRtc->HasPeriodic=true;
        if(pOsDriverRtc->PeriodicCounter!=0) pOsDriverRtc->PeriodicCounter--;
    }	
    if(i&RTC_AF){ // alarm flag interrupt
         pOsDriverRtc->HasAlarm=true;
    }	
*/
    if(i&RTC_UF){ // update cycle interrupt...per second
    	pOsDriverRtc->Second=RtcByteRead(RTC_CLOCK_SECOND);
        pOsDriverRtc->Minute=RtcByteRead(RTC_CLOCK_MINUTE);
        pOsDriverRtc->Hour=RtcByteRead(RTC_CLOCK_HOUR);
        pOsDriverRtc->Day=RtcByteRead(RTC_CLOCK_DAY);
        pOsDriverRtc->Date=RtcByteRead(RTC_CLOCK_DATE);
        pOsDriverRtc->Month=RtcByteRead(RTC_CLOCK_MONTH);
        pOsDriverRtc->Year=RtcByteRead(RTC_CLOCK_YEAR);	
    	pOsDriverRtc->HasUpdate=TRUE;
    }	
}

VOID RtcByteWrite(UINT8 Address,UINT8 Data){
	OutByte(RTC_ADDRESS_PORT,Address);
	OutByte(RTC_DATA_PORT,Data);
}

UINT8 RtcByteRead(UINT8 Address){
	OutByte(RTC_ADDRESS_PORT,Address);
	return InByte(RTC_DATA_PORT);
}
