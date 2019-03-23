#include <includes.h>

VOID dirAllNvramVarName(CAPTION *pCaption) {
    EFI_STATUS Status;
    UINTN VarNameSize, colum;
    CHAR16* VarName;
    CHAR16* OldNames;
	UINT8* C_str;
    EFI_GUID VarGuid;
	
/*GDB
	gBS->AllocatePool(EfiBootServicesData, 100*(sizeof(CHAR16)), &VarName);
	gBS->AllocatePool(EfiBootServicesData, 100*(sizeof(CHAR16)), &OldNames);
	gBS->AllocatePool(EfiBootServicesData, 100*(sizeof(CHAR16)), &VarGuid);
	
    colum = 0;
    while (!EFI_ERROR(Status)) {
        Status = gRT->GetNextVariableName (&VarNameSize, VarName, &VarGuid);
        if (Status==EFI_BUFFER_TOO_SMALL) {
            Status = gRT->GetNextVariableName (&VarNameSize, VarName, &VarGuid);
            if (EFI_ERROR(Status)) return;
        } else if (EFI_ERROR(Status)) return;

        //I want remove this check step;
        //if (StrCmp(VarName, L"StdDefaults")==0) count++;
        //if (count==2)return;
		
		UnicodeStr2CStr(VarName, C_str);
		CaptionStringPrint(&pCaption, "VarName = ");
		CaptionStringPrint(&pCaption, C_str);
		CaptionStringPrint(&pCaption, "\n");

		//GDB : I forget why do this.
        StrCpy(OldNames, VarName);
        gBS->AllocatePool (EfiBootServicesData, VarNameSize, &VarName);
        StrCpy(VarName, OldNames);
    }
	
	gBS->FreePool(C_str);
	gBS->FreePool(VarName);
	gBS->FreePool(OldNames);
GDB*/
}

VOID ReadVarBlock(UINTN index) 
{
    EFI_STATUS Status;
    UINTN VarSize, st, bufSize, i, cl;
    UINT8 *varBuffer = NULL;
    static CHAR16 VarName[100];
    static CHAR16 oldName[100];
    static EFI_GUID VarGuid;
    st = 0;//ReadVarBlock will run form st= 0 to st = index
    while (!EFI_ERROR(Status)) {
        Status = gRT->GetNextVariableName (&VarSize, VarName, &VarGuid);
        if (Status==EFI_BUFFER_TOO_SMALL) {
            Status = gRT->GetNextVariableName (&VarSize, VarName, &VarGuid);
            if (EFI_ERROR(Status))return;
        } else if (EFI_ERROR(Status))return;          

        if (st == index) {
            Print (L"VarName = %s(%d)\r\n", VarName, index);
			//GetVariable Start :
            bufSize = 0;
            Status = gRT->GetVariable(VarName, &VarGuid, NULL, &bufSize, varBuffer);
            Status = gBS->AllocatePool (EfiBootServicesData, bufSize, &varBuffer);
            if ( varBuffer == NULL )return;
            Status = gRT->GetVariable(VarName, &VarGuid, NULL, &bufSize, varBuffer);
            if (EFI_ERROR(Status))return;
			//GetVariable Success!
            cl =  0;//cl : the number of index column
            Print (L"%08x  ",cl);
            for (i = 0 ; i < bufSize ; i++) {
                Print (L"%02x, ", *(varBuffer+i));
                if (((i+1)%16)==0) {
                    cl+=16;
                    Print (L"\r\n%08x  ",cl);
                }
            }
        }
        st++;
        //if (StrCmp(VarName, L"StdDefaults")==0) count++;
        //if (count==2)return;
        StrCpy(oldName, VarName);
        gBS->AllocatePool (EfiBootServicesData, VarSize, &VarName);
        StrCpy(VarName, oldName);
    }
}

VOID NVReadBlock(CHAR16* BlockName, EFI_GUID VarGuid) {
    EFI_STATUS Status ;
    UINTN varSize, i, cl;
    UINT8 *varBuffer = NULL;

    //STEP 1
    varSize = 0;
    Status = gRT->GetVariable(BlockName, &VarGuid, NULL, &varSize, varBuffer);
    if (EFI_ERROR(Status))PrintEfiStatusStr(Status);

    //STEP 2
    Status = gBS->AllocatePool (EfiBootServicesData, varSize, &varBuffer);
    if ( varBuffer == NULL )Print (L"Buffer == NULL\r\n");

    //STEP 3
    Status = gRT->GetVariable(BlockName, &VarGuid, NULL, &varSize, varBuffer);
    if (EFI_ERROR(Status))PrintEfiStatusStr(Status);
    else Print (L"EFI_SUCCESS, varSize = %d.\r\n", varSize);

    for (i = 0 ; i < varSize ; i++) {
        Print (L"%02x, ", *(varBuffer+i));
        if (((i+1)%16)==0) {
            cl+=16;
            Print (L"\r\n%08x  ",cl);
        }
    }
}