#include <includes.h>

UINT32 IoRead32 ( UINT16 port)
{
	UINT32 Buffer;
	PCIO->Io.Read(PCIO,EfiPciWidthUint32,port,1,&Buffer);
	return Buffer;
}

UINT8 IoRead8 ( UINT16 port)
{
	UINT8 Buffer;
	PCIO->Io.Read(PCIO,EfiPciWidthUint8,port,1,&Buffer);
	return Buffer;
}

VOID IoWrite32 ( UINT16 port, UINT32 data)
{
	PCIO->Io.Write(PCIO,EfiPciWidthUint32,port,1,&data);
}

VOID IoWrite8 ( UINT16 port, UINT32 data)
{
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,port,1,&data);
}

VOID PCIPrintDeviceType(CAPTION *pCaption, UINT32 bus, UINT32 dev, UINT32 fun)
{
/*
    UINT8 base_class = PCIRead8 (bus, dev, fun, 0x0B);
	UINT8 SubClass = PCIRead8 (bus, dev, fun, 0x0A);
	UINT8 pi = PCIRead8 (bus, dev, fun, 0x09);
	
    switch (base_class){
        case 0x00:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Device was built before Class Code definitions were finalized\n");
			break;
        case 0x01:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Mass Storage Controller\n");
            break;
		case 0x02:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Network controller\n");
            break;
		case 0x03:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Display controller\n");
            break;
		case 0x04:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Multimedia device\n");
            break;
		case 0x05:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Memory controller\n");
            break;
		case 0x06:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Bridge device\n");
            break;
		case 0x07:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Simple communication controllers\n");
            break;
		case 0x08:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Base system peripherals\n");
            break;
		case 0x09:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Input devices\n");
            break;
		case 0x0A:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Docking stations\n");
            break;
		case 0x0B:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Processors\n");
            break;
		case 0x0C:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Serial bus controllers\n");
            break;
		case 0x0D:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Wireless controller\n");
            break;
		case 0x0E:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Intelligent I/O controllers\n");
            break;
		case 0x0F:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Satellite communication controllers\n");
            break;
		case 0x10:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Encryption/Decryption controllers\n");
            break;
		case 0x11:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Data acquisition and signal processing controllers\n");
            break;
		case 0x12:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Reserved\n");
            break;
        default:
			CaptionStringPrint(&pCaption, " Bus");CaptionUINT32Print(&pCaption, Bus);
			CaptionStringPrint(&pCaption, " Dev");CaptionUINT32Print(&pCaption, Dev);
			CaptionStringPrint(&pCaption, " Fun");CaptionUINT32Print(&pCaption, Fun);
			CaptionStringPrint(&pCaption, ": Unknow\n");
        }
		*/
}

UINT32 PCIRead32(UINT32 B,UINT32 D,UINT32 F,UINT8 offset)
{
    IoWrite32 ( 0xCF8, PCIADDR(B,D,F,offset) );
    return IoRead32 ( 0xCFC );
}

UINT8 PCIRead8 ( UINT32 B, UINT32 D, UINT32 F, UINT8 offset )
{
    UINT8 byte_access = offset & 0x03;
    IoWrite32 ( 0xCF8, PCIADDR(B,D,F,offset) );
    return IoRead8 ( 0xCFC + byte_access );
}

VOID   PCIWrite32 ( UINT32 B, UINT32 D, UINT32 F, UINT8 offset, UINT32 data )
{
    IoWrite32 ( 0xCF8, PCIADDR(B,D,F,offset));
    IoWrite32 ( 0xCFC, data );
}

VOID   PCIWrite8 ( UINT32 B, UINT32 D, UINT32 F, UINT8 offset, UINT8 data )
{
    UINT8 byte_access = offset & 0x03;
    IoWrite32 ( 0xCF8, PCIADDR(B,D,F,offset ) );
    IoWrite8 ( 0xCFC + byte_access, data );
}

/*
VOID stringScanIn(char* result){
	UINT32 mode;
	UINTN HandleCount;
	EFI_STATUS Status ;
	EFI_HANDLE *HandleBuffer;
	UINTN HandleIndex;
	mode=1;
	while(mode==1){
		Status = GBS->LocateHandleBuffer (ByProtocol, &SimpleTextInputGuid, NULL, &HandleCount, &HandleBuffer);
		for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
			SIMPLE_INPUT_INTERFACE *MyConIn = NULL;
			EFI_STATUS Status;
			EFI_INPUT_KEY *Key ;
			Status = GBS->HandleProtocol(HandleBuffer[HandleIndex],&SimpleTextInputGuid,&MyConIn);
			//while ( MyConIn->ReadKeyStroke (MyConIn,Key) != EFI_SUCCESS )   ;
			Status = MyConIn->ReadKeyStroke(MyConIn,Key);
		
			if(Status == EFI_SUCCESS){
				Print (L"keybroad get it! Key = %c, HandleIndex = %d\r\n", &Key, HandleIndex); 
				mode=0;
			}
		}
		if(HandleBuffer!=NULL)
			GBS->FreePool(HandleBuffer);
	}
}
*/