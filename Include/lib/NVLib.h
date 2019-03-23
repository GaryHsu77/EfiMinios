#ifndef NV_H
#define NV_H

#define DEFAULTS_GUID   {0x4599d26f, 0x1a11, 0x49b8, 0xb9, 0x1f, 0x85, 0x87, 0x45, 0xcf, 0xf8, 0x24}
#define FASTOPTION_GUID {0xB540A530, 0x6978, 0x4DA7, 0x91, 0xCB, 0x72, 0x07, 0xD7, 0x64, 0xD2, 0x62}

extern VOID dirAllNvramVarName(CAPTION *pCaption);
extern VOID ReadVarBlock(UINTN index);
extern VOID NVReadBlock(CHAR16* BlockName, EFI_GUID VarGuid);

#endif