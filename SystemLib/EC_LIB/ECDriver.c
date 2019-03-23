#include "ECDriver.h"

EFI_GUID PciRootGuid = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
EFI_GUID DriverBindingGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
EFI_GUID PciIOGuid = EFI_PCI_IO_PROTOCOL_GUID;
EFI_GUID EzECRamRWGuid = EZ_EC_RAM_RW_GUID;

EFI_SYSTEM_TABLE *GST;
EFI_RUNTIME_SERVICES *GRS;
EFI_BOOT_SERVICES *GBS;
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PCIO;
SIMPLE_TEXT_OUTPUT_INTERFACE *TOI;

EFI_STATUS ECRAMSupport (EFI_DRIVER_BINDING_PROTOCOL *This, EFI_HANDLE ControllerHandle, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath);
EFI_STATUS ECRAMStart (EFI_DRIVER_BINDING_PROTOCOL *This,EFI_HANDLE ControllerHandle, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath);
EFI_STATUS ECRAMStop (EFI_DRIVER_BINDING_PROTOCOL *This,EFI_HANDLE ControllerHandle, UINTN NumberOfChildren,EFI_HANDLE *ChildHandleBuffer);

extern EFI_STATUS InternalRamRead (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 *Data);
extern EFI_STATUS InternalRamWrite (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 Data);
extern EFI_STATUS ExternalRamRead (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 *Data);
extern EFI_STATUS ExternalRamWrite (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 Data);

EFI_DRIVER_BINDING_PROTOCOL MyDriverBinding =
{
    ECRAMSupport,
    ECRAMStart,
    ECRAMStop,
    0,
    NULL,
    NULL
};

EZ_EC_RAM_RW_PROTOCOL EzECRamRWProtocol =
{
    0,
	1000,
	1000,
	InternalRamRead,
	InternalRamWrite,
	ExternalRamRead,
	ExternalRamWrite
};

EFI_STATUS ecDriver (EFI_HANDLE Handle, EFI_SYSTEM_TABLE *ST)
{
		EFI_STATUS Status ;	
		GST = ST;
		GRS = ST->RuntimeServices;
		GBS = ST->BootServices;
	
		InitializeLib(Handle,GST);
		//Status = GST->BootServices ->LocateProtocol ( &DBProtocol, NULL, &DP) ;
		//DP->DebugPrintf(DP, "~~Start");
		MyDriverBinding.ImageHandle = Handle;
		Status = ST->BootServices->InstallProtocolInterface (&(MyDriverBinding.DriverBindingHandle),
															&DriverBindingGuid,EFI_NATIVE_INTERFACE, 
															&MyDriverBinding);
		Status = ST->BootServices->LocateProtocol ( &PciRootGuid, NULL, &PCIO) ;
		
        return EFI_SUCCESS ;
}

EFI_STATUS ECRAMSupport (EFI_DRIVER_BINDING_PROTOCOL *This, EFI_HANDLE ControllerHandle, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath)
{
    EFI_STATUS Status;
    UINT8 baseCo, subCo, interface;
    EFI_PCI_IO_PROTOCOL *PciIo;
	Status = GST->BootServices ->LocateProtocol ( &PciIOGuid, NULL, &PciIo) ;
	Status = ST->BootServices->OpenProtocol (ControllerHandle, 
											&PciIOGuid, 
											&PciIo, 
											This->DriverBindingHandle, 
											ControllerHandle, 
											EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    if (EFI_ERROR(Status)) return Status;
	PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0x0B, 1, &baseCo);
	PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0x0A, 1, &subCo);
	PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0x09, 1, &interface);
	if((baseCo==6)&&(subCo==1)&&(interface==0)){
		return EFI_SUCCESS;
	}else{
		return EFI_UNSUPPORTED;
	}
}

EFI_STATUS ECRAMStart (EFI_DRIVER_BINDING_PROTOCOL *This,EFI_HANDLE ControllerHandle, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath)
{
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
	//delete this column will error!
    Status = ST->BootServices->OpenProtocol ( ControllerHandle, 
											&PciIOGuid, 
											(VOID **)&PciIo, 
											This->DriverBindingHandle, 
											ControllerHandle, 
                                            EFI_OPEN_PROTOCOL_BY_DRIVER );
    if(EFI_ERROR(Status)) return Status;

    ST->BootServices->InstallProtocolInterface (&ControllerHandle, &EzECRamRWGuid, EFI_NATIVE_INTERFACE, &EzECRamRWProtocol);


    return EFI_SUCCESS;
}

EFI_STATUS ECRAMStop (EFI_DRIVER_BINDING_PROTOCOL *This,EFI_HANDLE ControllerHandle, UINTN NumberOfChildren,EFI_HANDLE *ChildHandleBuffer)
{
    EFI_STATUS Status;
    EZ_EC_RAM_RW_PROTOCOL *pEzECRamRW;

    Status = ST->BootServices->OpenProtocol (ControllerHandle, 
											& EzECRamRWGuid,  
											&pEzECRamRW,
                                            This->DriverBindingHandle, 
											ControllerHandle, 
                                            EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

    Status = ST->BootServices->UninstallMultipleProtocolInterfaces (ControllerHandle, &EzECRamRWGuid, pEzECRamRW, NULL);

    Status = ST->BootServices->CloseProtocol (ControllerHandle,&PciIOGuid, This->DriverBindingHandle, ControllerHandle);

    return EFI_SUCCESS;
}

