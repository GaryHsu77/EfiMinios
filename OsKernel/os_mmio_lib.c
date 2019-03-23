#include <includes.h>

VOID SystemlibMemoryCopy(UINT8* pSource,UINT8* pDestination,UINT32 Length)
{
	UINT32 U64Number;
	UINT32 U32Number;
	UINT32 U8Number;
	UINT32 i;
	UINT64 *pU64S,*pU64D;
	UINT32 *pU32S,*pU32D;
	UINT8  *pU8S,*pU8D;

	i=Length;
	U64Number=i/8;
	i=i-U64Number*8;
	U32Number=i/4;
	i=i-U32Number*4;
	U8Number=i;
	pU64S=(UINT64 *)pSource;
	pU64D=(UINT64 *)pDestination;
	while(U64Number>0){
		*pU64D=*pU64S;
		pU64D++;
		pU64S++;
		U64Number--;
    }
	pU32S=(UINT32 *)pU64S;
	pU32D=(UINT32 *)pU64D;
	while(U32Number>0){
		*pU32D=*pU32S;
		pU32D++;
		pU32S++;
		U32Number--;
    }
	pU8S=(UINT8 *)pU32S;
	pU8D=(UINT8 *)pU32D;
	while(U8Number>0){
		*pU8D=*pU8S;
		pU8D++;
		pU8S++;
		U8Number--;
    }
}

VOID SystemlibMemoryDump(CAPTION *pCaption,UINT8* pData,UINT16 Length){
	UINT8 i,j;
	UINT16 l;
	
    i=0;
    j=1;
    CaptionStringPrint(pCaption,"\n00h ");
    for(l=0;l<Length;l++){
    	if(i==16){
    		i=0;
            CaptionStringPrint(pCaption,"\n");
            CaptionUINT8Print(pCaption,j);
            CaptionStringPrint(pCaption,"h ");

            j++;
    	}
    	//if(i==8) CaptionStringPrint(pCaption," - ");
    	i++;
        //GDB GuiU8Print(pData[l]);
		CaptionUINT8Print(pCaption,pData[l]);
        CaptionStringPrint(pCaption," ");
    }
    CaptionStringPrint(pCaption," ");
}

VOID SystemlibMemorySet(UINT8* pData,UINT8 Value,UINT32 Length)
{
	gBS->SetMem(pData,Length,Value);
}

VOID OsLibMemorySet(UINT8* pData,UINT8 Value,UINT32 Length)
{
	gBS->SetMem(pData,Length,Value);
}

UINT8 InByte(UINT16 port)
{
	UINT8 Buffer;
	PCIO->Io.Read(PCIO,EfiPciWidthUint8,port,1,&Buffer);
	return Buffer;
}

VOID OutByte(UINT16 port, UINT32 data)
{
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,port,1,&data);
}