#ifndef OSEFI_H
#define OSEFI_H

#include <..\efishell\shell.h>

#define USING_EFI_SHELL 1

#define EFIx64 1
extern EFI_SYSTEM_TABLE *gST;
extern EFI_BOOT_SERVICES *gBS;
extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_HANDLE MT_Handle;

extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PCIO;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
extern SIMPLE_INPUT_INTERFACE *gConIn;
extern EFI_CPU_ARCH_PROTOCOL *CpuArch;
extern EFI_SIMPLE_POINTER_PROTOCOL *SPP;

extern BOOLEAN dbSwitch;
VOID EfiInit(VOID);

#endif
