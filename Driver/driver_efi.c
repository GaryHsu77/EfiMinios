#include <includes.h>

static EFI_GUID GOPGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP = NULL;
static EFI_GUID PciIoProtocol = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PCIO;
static EFI_GUID CPUArchGuid = EFI_CPU_ARCH_PROTOCOL_GUID;
EFI_CPU_ARCH_PROTOCOL *CpuArch = NULL;
static EFI_GUID SimpleTextInputGuid = {0x387477c1, 0x69c7, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b };
SIMPLE_INPUT_INTERFACE *gConIn ;
static EFI_GUID SimplePointerGuid = {0x31878c87,0xb75,0x11d5,0x9a,0x4f,0x0,0x90,0x27,0x3f,0xc1,0x4d};
EFI_SIMPLE_POINTER_PROTOCOL *SPP;

BOOLEAN dbSwitch = FALSE;

VOID EfiInit(VOID){
    EFI_STATUS Status ;
	
    Status = gBS->LocateProtocol(&GOPGuid, NULL, &GOP) ;
	if(Status!=EFI_SUCCESS){
		GDP(L"Error : LocateProtocol(EFI_GRAPHICS_OUTPUT_PROTOCOL)");while(1){};
	}
    Status = gBS->LocateProtocol(&PciIoProtocol, NULL, &PCIO) ;
	if(Status!=EFI_SUCCESS){
		GDP(L"Error : LocateProtocol(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL)");while(1){};
	}
	Status = gBS->LocateProtocol(&CPUArchGuid,NULL,&CpuArch);
	if(Status!=EFI_SUCCESS){
		GDP(L"Error : LocateProtocol(EFI_CPU_ARCH_PROTOCOL)");while(1){};
	}
	Status = gBS->LocateProtocol ( &SimpleTextInputGuid, NULL, &gConIn) ;
    if(Status!=EFI_SUCCESS){
		GDP(L"Error : LocateProtocol(SIMPLE_INPUT_INTERFACE)");while(1){};
	}
	Status = gBS->LocateProtocol ( &SimplePointerGuid, NULL, &SPP) ;
	if(Status!=EFI_SUCCESS){
		GDP(L"Error : LocateProtocol(EFI_SIMPLE_POINTER_PROTOCOL)");while(1){};
	}
}