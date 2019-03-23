#ifndef PIC_H
#define PIC_H
#include <efi.h>
#include <efilib.h>
#include "EcRam.h"
#include "Debug.h"
#include <..\efishell\shell.h>
#pragma optimize( "", off )

#define PCIADDR(b,d,f,off) (0x80000000+((b)<<16)+((d)<<11)+((f)<<8)+((off)&0xFC))

//extern EFI_GUID SimpleTextOutputInterface;
//extern EFI_GUID SimpleTextInputGuid;

//extern SIMPLE_TEXT_OUTPUT_INTERFACE *TOI;
//extern SIMPLE_INPUT_INTERFACE *ConIn ;
extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PCIO;

extern EFI_SYSTEM_TABLE *GST;
extern EFI_RUNTIME_SERVICES *GRS;
extern EFI_BOOT_SERVICES *GBS;
/*
extern void PrintDeviceType ( UINT32 bus, UINT32 dev, UINT32 fun);
extern void testValue (UINTN x);
*/
extern UINT8 PCIRead8 ( UINT32 B, UINT32 D, UINT32 F, UINT8 OFF );
extern UINT32 PCIRead32 ( UINT32 B, UINT32 D, UINT32 F, UINT8 OFF );
extern UINT8 IoRead8 ( UINT16 port);
extern void IoWrite32 ( UINT16 port, UINT32 data);
extern void PCIWrite8 ( UINT32 B, UINT32 D, UINT32 F, UINT8 OFF, UINT8 data );
extern void IoWrite8 ( UINT16 port, UINT32 data);

#endif