#include <includes.h>

#define	RAND_MAX	0x7fffffff
static	UINTN next = 1;

//Critical Section function >>>
MY_MUTEX OsEnterCritical()
{
	EFI_TPL PreviousTPL = gBS->RaiseTPL(TPL_HIGH_LEVEL);
	return (MY_MUTEX)PreviousTPL;
}

VOID OsExitCritical(MY_MUTEX mutex)
{
	 gBS->RestoreTPL((EFI_TPL)mutex);
}
//Critical Section function <<<

//Random function >>>
UINTN MultiThread_random()
{
	return ((next = next * 1103515245 + 12345) % ((unsigned long)RAND_MAX + 1));
}

VOID sandom()
{
	EFI_TIME Time;

	gRT->GetTime(&Time,NULL);
	next = (Time.Year<<24) + (Time.Month<<20) + (Time.Day<<16) + (Time.Hour<<12) + (Time.Minute<<8) + Time.Second;
}

VOID OSTime_Delay(UINTN ns)
{
	UINT64 TimerValue, TimerValue2, TimerPeriod, value;
	EFI_STATUS Status;

	if(CpuArch == NULL) return;

	Status = CpuArch->GetTimerValue(CpuArch,0,&TimerValue,&TimerPeriod);
	if(Status != EFI_SUCCESS) return;

	if(TimerPeriod == 0) return;

	value = ((UINT64)ns) * 1000 * 1000 * 1000; //change to the unit of femtoseconds
	value /= TimerPeriod;

	do{
		Status = CpuArch->GetTimerValue(CpuArch,0,&TimerValue2,NULL);
		if(Status != EFI_SUCCESS) return;
		if((TimerValue2-TimerValue) >= value) break;
		OsYield(NULL,NULL);
	}while(1);
}
//Random function <<<