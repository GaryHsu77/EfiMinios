#ifndef _EFI_LIB_PLAT_H
#define _EFI_LIB_PLAT_H
/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efilibplat.h

Abstract:

    EFI to compile bindings



Revision History

--*/



VOID
InitializeLibPlatform (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
    );

#endif