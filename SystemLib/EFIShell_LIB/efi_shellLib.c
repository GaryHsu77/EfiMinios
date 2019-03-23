#include <includes.h>

VOID PrintGuidStr(CAPTION *pCaption, EFI_GUID guid) {
    UINT16* Str;
	UINT8* C_str;
	
	gBS->AllocatePool(EfiBootServicesData, 100*(sizeof(UINT16)), &Str);
	if(USING_EFI_SHELL){
		//GDB : Here need to do tranfer because it's uint16 string.
		GuidToString(Str,&guid);
		UnicodeStr2CStr(Str, C_str);
		CaptionStringPrint(&pCaption, C_str);
		gBS->FreePool(C_str);
		gBS->FreePool(Str);
	}
}

VOID PrintEfiStatusStr(CAPTION *pCaption, EFI_STATUS Status) {
    CHAR16* Str;
	UINT8* C_str;
	
	gBS->AllocatePool(EfiBootServicesData, 100*(sizeof(CHAR16)), &Str);
	if(USING_EFI_SHELL){
		//GDB : Here need to do tranfer because it's uint16 string.
		StatusToString(Str,Status);
		UnicodeStr2CStr(Str, C_str);
		CaptionStringPrint(&pCaption, Str);
		gBS->FreePool(C_str);
		gBS->FreePool(Str);
	}
}