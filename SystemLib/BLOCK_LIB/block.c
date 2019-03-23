#include <efi.h>
#include <efilib.h>
#include <..\efishell\shell.h>
#include "ComponentName2.h"

#pragma optimize( "", off )

#define _SATA_DEV			19
#define _SATA_FUN			0
#define END_NODE_SUBTYPE	0xFF
EFI_SYSTEM_TABLE *GST;
EFI_RUNTIME_SERVICES *GRS;
EFI_BOOT_SERVICES *GBS;

EFI_BLOCK_IO *BIP;

EFI_GUID BlkIOGuid = {0x964e5b21,0x6459,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b};
EFI_GUID EfiDevicePathProtocolGuid =  {0x09576e91,0x6d3f,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b};
EFI_GUID EfiComponentProtocolGuid =  {0x6a7a5cff, 0xe8d9, 0x4f70, 0xba, 0xda, 0x75, 0xab, 0x30, 0x25, 0xce, 0x14};
EFI_GUID EfiDriverBindGuid =  EFI_DRIVER_BINDING_PROTOCOL_GUID;

EFI_DEVICE_PATH_PROTOCOL* nextNode(EFI_DEVICE_PATH_PROTOCOL *node){
	return (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(node) + ((node)->Length[0]+((node)->Length[1]<<8)));
}

void getDriverName(){
	EFI_STATUS Status ;
	UINTN i, HandleCount;
	EFI_HANDLE *HandleBuffer;
	CHAR16 *Drivername = NULL;
	CHAR16 *CtrlName = NULL;
	GBS->LocateHandleBuffer(ByProtocol,&EfiComponentProtocolGuid,NULL,&HandleCount,&HandleBuffer);
	for(i=0;i<HandleCount;i++){
		EFI_COMPONENT_NAME2_PROTOCOL *ComponentName2Protocol = NULL;
		GBS->HandleProtocol(HandleBuffer[i],&EfiComponentProtocolGuid,&ComponentName2Protocol);
		if(ComponentName2Protocol != NULL){
			CHAR16 *Drivername = NULL;
			ComponentName2Protocol->GetDriverName(ComponentName2Protocol,ComponentName2Protocol->SupportedLanguages,&Drivername);
			if(Drivername != NULL){
				Print (L"Drivername = %s ;\r\n", Drivername);
			}
			ComponentName2Protocol->GetControllerName (ComponentName2Protocol, 
														HandleBuffer[i], 
														NULL, 
														ComponentName2Protocol->SupportedLanguages, 
														&CtrlName); 
			if(CtrlName != NULL){
				Print (L"CtrlName = %s ;\r\n", CtrlName);
			}
		}
	}
	if(HandleBuffer) GBS->FreePool(HandleBuffer);
}

void devicePathFunc(){
	EFI_STATUS Status ;
	UINTN HandleCount, HandleIndex;
	EFI_HANDLE *HandleBuffer;
	EFI_DEVICE_PATH_PROTOCOL *DevicePath;
	EFI_DEVICE_PATH_PROTOCOL *DevicePathNode;
	PCI_DEVICE_PATH *PciDevicePath;
	Status = GBS->LocateHandleBuffer (ByProtocol, &BlkIOGuid, NULL, &HandleCount, &HandleBuffer);

	for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
		//(VOID *)&DevicePath????
		Status = GBS->HandleProtocol(HandleBuffer[HandleIndex],&EfiDevicePathProtocolGuid,(VOID *)&DevicePath);
		if(Status != EFI_SUCCESS) continue;
		PciDevicePath = NULL;
		DevicePathNode = DevicePath;
		while (DevicePathNode->SubType != END_NODE_SUBTYPE ){
 			if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) && (DevicePathNode->SubType == HW_PCI_DP)){
				PciDevicePath = (PCI_DEVICE_PATH *)DevicePathNode;
				break;
			} 
			DevicePathNode = nextNode(DevicePathNode);
		} 
		if (PciDevicePath == NULL) continue;
		
		if ((PciDevicePath->Device == _SATA_DEV) && (PciDevicePath->Function == _SATA_FUN)){
			Print (L"_SATA_DEV get! ;\r\n");
		}
	}	
}

void getControllerName(){
	EFI_STATUS Status ;
	UINTN HandleCount, HandleIndex;
	EFI_HANDLE *HandleBuffer, devHandle;
	EFI_DEVICE_PATH_PROTOCOL *DevicePath;
	CHAR16 *CtrlName = NULL;
	CHAR16 *str = NULL;
	EFI_COMPONENT_NAME2_PROTOCOL *ComponentName2Protocol = NULL;
	Status = GBS->LocateHandleBuffer (ByProtocol, &EfiDevicePathProtocolGuid, NULL, &HandleCount, &HandleBuffer);
	if(Status != EFI_SUCCESS) return;
	for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
		Status = GBS->HandleProtocol(HandleBuffer[HandleIndex],&EfiDevicePathProtocolGuid,&DevicePath);
		if(Status != EFI_SUCCESS) 
			Print (L"HandleProtocol {EfiDevicePathProtocolGuid} : ERROR ;\r\n");
		else
			Print (L"DevicePath : %d, %d ;\r\n", DevicePath->Type, DevicePath->SubType);
		
		Status = GBS->LocateDevicePath(&EfiDevicePathProtocolGuid, &DevicePath, &devHandle);
		if(Status != EFI_SUCCESS) 
			Print (L"LocateDevicePath : ERROR ;\r\n");
		
		
		
 		Status = GBS->LocateProtocol ( &EfiComponentProtocolGuid, NULL, &ComponentName2Protocol) ;
		if(Status != EFI_SUCCESS) {
			Print (L"HandleProtocol {EfiComponentProtocolGuid} : ERROR ;\r\n");
		}
		Status = ComponentName2Protocol->GetControllerName (ComponentName2Protocol, 
														//HandleBuffer[HandleIndex],
														devHandle,
														NULL, 
														ComponentName2Protocol->SupportedLanguages, 
														&CtrlName); 
		if(Status != EFI_SUCCESS) {
			StatusToString (str, Status); 
			Print (L"GetControllerName : ERROR( %s );\r\n", str);
		}
		if(CtrlName != NULL){
			Print (L"CtrlName = %s (%d / %d);\r\n", CtrlName, HandleIndex, HandleCount);
			CtrlName = NULL;
		}	 
	}
}

EFI_STATUS EFIDevApp (EFI_HANDLE Handle, EFI_SYSTEM_TABLE *ST)
{
	GST = ST;
	GRS = ST->RuntimeServices;
	GBS = ST->BootServices;
	
	InitializeShellApplication(Handle, ST);
	InitializeLib(Handle,ST);
	
	getControllerName();
	
    return EFI_SUCCESS ;
}




