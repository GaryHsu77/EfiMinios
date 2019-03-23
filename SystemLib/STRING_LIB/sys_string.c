#include <includes.h>

BOOLEAN StrEqual(UINT8* pString,UINT8* pString2, UINT16 len);
BOOLEAN SystemlibStringCompare(UINT8* pString,UINT8* pString2);
VOID OsLibStringCopy(UINT8* pDestination,UINT8* pSource);
UINT32 SystemlibString2int(UINT8 *pString);

VOID UnicodeStr2CStr(UINT16* UniStr, UINT8* CStr){
	EFI_STATUS Status;
	UINT8 len, i=0;
	UINT16* Tmp;
	
	Tmp=UniStr;
	while(Tmp!=0){
		i++;
		Tmp=(UINT16*)UniStr+i;
	}
	len = i;
	
	Status = gBS->AllocatePool(EfiBootServicesData, len+1, &CStr);
	if(Status != EFI_SUCCESS){
		GDP(L"ERROR : System lib 'UnicodeStr2CStr' allocated buffer fail.");
		return;
	}
	
	for(i=0;i<len;i++) CStr[i]=(UINT8)UniStr[i];
	CStr[len]='\0';
}

BOOLEAN StrEqual(UINT8* pString,UINT8* pString2, UINT16 len)
{
    UINT8 i;

	for(i=0;i<len;i++){
		if(pString[i]!=pString2[i])
			return FALSE;
	}
	if((pString[len]!=0)||(pString2[len]!=0))
		SystemGuiStringPrint(L"\nWarming : Function StrEqual maybe error(length).\n");
    return TRUE;
}

BOOLEAN SystemlibStringCompare(UINT8* pString,UINT8* pString2)
{
    UINT8 i;

    i=0;
    while((*pString!=0)&&(*pString2!=0)){
        if(i==250) return FALSE;
        if(*pString!=*pString2) return FALSE;	
        pString++;
        pString2++;
        i++;
    }
    if((*pString==0)&&(*pString2==0)) return TRUE;
    else return FALSE;
}

VOID OsLibStringCopy(UINT8* pDestination,UINT8* pSource){
	UINT8 i;
	
	i=0;
    while(*pSource!=0){
        *pDestination=*pSource;
        pDestination++;
        pSource++;
        i++;
    	if(i>=(OS_NAME_STRING_MAX-1)){
    		*pDestination=0;
    		return;
    	}
    }
    *pDestination=0;
}

UINT32 SystemlibString2int(UINT8 *pString){
    UINT32 i,j;	
    
    if(pString==(UINT8 *)NULL) return 0;
    i=0;
    j=0;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=i*0x10+*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=i*0x10+*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=i*0x10+*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=i*0x10+*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=i*0x10+*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=i*0x10+*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=i*0x10+*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=i*0x10+*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=i*0x10+*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=i*0x10+*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=i*0x10+*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=i*0x10+*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=i*0x10+*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=i*0x10+*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=i*0x10+*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=i*0x10+*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=i*0x10+*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=i*0x10+*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else{
        if((*pString>='0')&&(*pString<='9')) i=i*0x10+*pString-'0';
        else if((*pString>='a')&&(*pString<='f')) i=i*0x10+*pString-'a'+10;
        else if((*pString>='A')&&(*pString<='F')) i=i*0x10+*pString-'A'+10;
        else return 0; // invalid input
    }
    pString++;
    if(*pString==0) return i;
    else return 0; // string too long
}