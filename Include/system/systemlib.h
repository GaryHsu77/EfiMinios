#ifndef SYSTEMLIB_H
#define SYSTEMLIB_H

BOOLEAN SystemlibStringCompare(UINT8* pString,UINT8* pString2);
void SystemlibMemoryDump(CAPTION *pCaption,UINT8* pData,UINT16 Length);
void SystemlibMemorySet(UINT8* pData,UINT8 Value,UINT32 Length);
UINT8 SystemlibStringLength(UINT8* pString);
BOOLEAN SystemlibAreaOverlapCheck(GRAPHIC_AREA *pArea,GRAPHIC_AREA *pArea2);
BOOLEAN SystemlibAreaPositionCheck(GRAPHIC_AREA *pArea,GRAPHIC_POSITION *pPosition);
UINT32 SystemlibString2int(UINT8 *pString);

#endif
