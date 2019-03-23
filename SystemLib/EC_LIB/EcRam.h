#include "ECDriver.h"
#ifndef EC_H
#define EC_H

#define EZ_EC_RAM_RW_GUID  \
     {0xa545a0c7, 0xc03, 0x4df6,0x8f, 0x80, 0xbb, 0x90, 0x9a, 0xe8, 0x11, 0x0d}
	 
EFI_INTERFACE_DECL(EZ_EC_RAM_RW_PROTOCOL);//??
	 
typedef 
EFI_STATUS
(EFIAPI *EZ_EC_RAM_RW_PROTOCOL_InternalRamRead) (
  IN     struct _EZ_EC_RAM_RW_PROTOCOL  *This,
  IN     UINT16                         Offset,
  OUT    UINT8                          *Data
); 

typedef 
EFI_STATUS
(EFIAPI *EZ_EC_RAM_RW_PROTOCOL_InternalRamWrite) (
  IN     struct _EZ_EC_RAM_RW_PROTOCOL  *This,
  IN     UINT16                         Offset,
  OUT    UINT8                          Data
); 

typedef 
EFI_STATUS
(EFIAPI *EZ_EC_RAM_RW_PROTOCOL_ExternalRamRead) (
  IN     struct _EZ_EC_RAM_RW_PROTOCOL  *This,
  IN     UINT16                         Offset,
  OUT    UINT8                          *Data
); 

typedef 
EFI_STATUS
(EFIAPI *EZ_EC_RAM_RW_PROTOCOL_ExternalRamWrite) (
  IN     struct _EZ_EC_RAM_RW_PROTOCOL  *This,
  IN     UINT16                         Offset,
  OUT    UINT8                          Data
); 
	 
typedef struct _EZ_EC_RAM_RW_PROTOCOL {
	UINT64 		Revision;
	UINT64      InternalRamSize;
	UINT64      ExternalRamSize;
	EZ_EC_RAM_RW_PROTOCOL_InternalRamRead  InternalRamRead;
	EZ_EC_RAM_RW_PROTOCOL_InternalRamWrite InternalRamWrite;
	EZ_EC_RAM_RW_PROTOCOL_ExternalRamRead  ExternalRamRead;
	EZ_EC_RAM_RW_PROTOCOL_ExternalRamWrite ExternalRamWrite;
} EZ_EC_RAM_RW_PROTOCOL;

#endif

