#ifndef SYSTEM_CGA_H
#define SYSTEM_CGA_H

#define SYSTEM_CGA_ADDRESS_PORT 0x3d4
#define SYSTEM_CGA_DATA_PORT 0x3d5

#define SYSTEM_CGA_HTR  0x00 //horizontal total register
#define SYSTEM_CGA_EHDR 0x01 //end horizontal display register
#define SYSTEM_CGA_SHBR 0x02
#define SYSTEM_CGA_EHBR 0x03
#define SYSTEM_CGA_SHRR 0x04
#define SYSTEM_CGA_EHRR 0x05
#define SYSTEM_CGA_VTR  0x06
#define SYSTEM_CGA_OR   0x07
#define SYSTEM_CGA_PRSR 0x08
#define SYSTEM_CGA_MSLR 0x09
#define SYSTEM_CGA_CSR  0x0a
#define SYSTEM_CGA_CER  0x0b
#define SYSTEM_CGA_SAHR 0x0c //start address high register
#define SYSTEM_CGA_SALR 0x0d //start address low register
#define SYSTEM_CGA_CLHR 0x0e //cursor location high register
#define SYSTEM_CGA_CLLR 0x0f //cursor location low register
#define SYSTEM_CGA_VRSR 0x10
#define SYSTEM_CGA_VRER 0x11
#define SYSTEM_CGA_VDER 0x12
#define SYSTEM_CGA_OR   0x13
#define SYSTEM_CGA_ULR  0x14
#define SYSTEM_CGA_SVBR 0x15
#define SYSTEM_CGA_EVB  0x16
#define SYSTEM_CGA_CMCR 0x17
#define SYSTEM_CGA_LCR  0x18

typedef struct{
    U32 CursorPosition;
    U8 CharacterAttribute;
}SYSTEM_CGA_CONTROL;

extern SYSTEM_CGA_CONTROL SystemCgaCtrl;

void SystemCgaInit();
void SystemCgaCursorSet();
void SystemCgaScrollUp();
void SystemCgaCharPut(U8 CharValue);
void SystemCgaScreenClean();
void SystemCgaBackSpace();
void SystemCgaChangeLine();

#endif
