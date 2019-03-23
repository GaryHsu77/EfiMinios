#include "2048.h"


static UINTN rand = 1;

UINTN random(UINTN size)
{
    EFI_TIME time;
	//UINTN  seed;
    GRS->GetTime(&time,NULL);
	if(rand==0)rand+=1;
	//Print(L"rand=%d\n",rand);
	//Print(L"time.Second=%d",time.Second);
	return ((rand = rand * time.Second * 123123456789) % (size));
}
/*
UINTN random(int size)
{
    EFI_TIME time;
	UINTN  seed, tmp;
    gRS->GetTime(&time,NULL);
	tmp=ranNum;
	ranNum = (((rand * time.Second * 12345678)+12345)%(size)) ;
	while(tmp==ranNum){
	    ranNum = ((((rand+1) * time.Second * 7543289)+373737)%(size)) ;
	}
	rand = ((ranNum * 12345678)%100)+1;
	//Print(L"rand=%d\n",rand);
	//Print(L"num=%d\n",ranNum);
	return ranNum;
}
*/