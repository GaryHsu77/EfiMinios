#ifndef OS_LIB_H
#define OS_LIB_H

extern MY_MUTEX OsEnterCritical();
extern VOID OsExitCritical(MY_MUTEX);

VOID OSTime_Delay(UINTN ns);

BOOLEAN StrEqual(UINT8* pString,UINT8* pString2, UINT16 len);
VOID OsLibStringCopy(UINT8 *pDestination,UINT8 *pSource);
VOID UnicodeStr2CStr(UINT16* UniStr, UINT8* CStr);

VOID SystemlibMemorySet(UINT8* pData,UINT8 Value,UINT32 Length);
VOID OsLibMemorySet(UINT8* pData,UINT8 Value,UINT32 Length);
VOID SystemlibMemoryCopy(UINT8* pSource,UINT8* pDestination,UINT32 Length);

VOID OutByte(UINT16 port, UINT32 data);
//void OutWord(UINT8 port, UINT16 value);
//void OutDword(UINT8 port, UINT8 value);

UINT8 InByte(UINT16 port);
//UINT16 InWord(UINT8 port);
//UINT8 InDword(UINT8 port);

#endif
