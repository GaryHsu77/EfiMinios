#include <includes.h>

GUI_CONTROL GuiCtrl;

VOID GuiInit(VOID)
{
	//OsResourceAdd(&GuiCtrl.GuiResource,"GUI",OS_RESOURCE_GUI);
}

VOID GuiCharPrint(UINT8 CharValue)
{
	if(OsResourceAllocate(&GuiCtrl.GuiResource,1000)==OS_FALSE) return;
    GuiTextCharPut(CharValue);
    OsResourceRelease(&GuiCtrl.GuiResource);
}

BOOLEAN GuiStringPrint(UINT8* pString)
{
	if(OsResourceAllocate(&GuiCtrl.GuiResource,1000)==OS_FALSE) return OS_FALSE;
	while(*pString!=0){
		if(*pString==0x0a) GuiTextCr();
		else if(*pString==0x0d); // 0x0a 0x0d is change line ,too.
		else GuiTextCharPut(*pString);
		pString++;
	}
    OsResourceRelease(&GuiCtrl.GuiResource);
    return OS_TRUE;
}

VOID GuiBackSpace(VOID)
{
	if(OsResourceAllocate(&GuiCtrl.GuiResource,1000)==OS_FALSE) return;
	GuiTextDel();
	OsResourceRelease(&GuiCtrl.GuiResource);
}

VOID GuiUINT8Print(UINT8 Number)
{
    UINT8 i;

	if(OsResourceAllocate(&GuiCtrl.GuiResource,1000)==OS_FALSE) return;
    i=(Number&0xf0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=Number&0x0f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    OsResourceRelease(&GuiCtrl.GuiResource);
}

VOID GuiUINT16Print(UINT16 Number)
{
    UINT16 i;

	if(OsResourceAllocate(&GuiCtrl.GuiResource,1000)==OS_FALSE) return;
    i=(Number&0xf000)>>12;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x0f00)>>8;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x00f0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=Number&0x000f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
	OsResourceRelease(&GuiCtrl.GuiResource);
}

VOID GuiUINT32Print(UINT32 Number)
{
    UINT32 i;
    
	if(OsResourceAllocate(&GuiCtrl.GuiResource,1000)==OS_FALSE) return;
    i=(Number&0xf0000000)>>28;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x0f000000)>>24;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x00f00000)>>20;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x000f0000)>>16;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x0000f000)>>12;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x00000f00)>>8;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=(Number&0x000000f0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    i=Number&0x0000000f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    GuiTextCharPut(i);
    OsResourceRelease(&GuiCtrl.GuiResource);
}
