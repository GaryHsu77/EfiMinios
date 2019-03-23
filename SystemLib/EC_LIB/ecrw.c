#include "EcRam.h"
#include "ECDriver.h"
//#include "pciLib.h"


EFI_STATUS InternalRamRead (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 *Data){
	UINT8 hNum, lNum;	
	//1
	lNum = (Offset&0xff);
	hNum = ((Offset>>8)&0xff);
	//2
	while((IoRead8(0x25D)&0x02)!=0){}
	//3
	//PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25D,1, 0x80);
	IoWrite8(0x25D,0x80);
	//4
	while((IoRead8 (0x25D)&0x02)!=0){}
	//5
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25C,1, &hNum);
	//6
	while((IoRead8 (0x25D)&0x02)!=0){}
	//7
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25C,1, &lNum);
	//8
	while((IoRead8 (0x25D)&0x02)!=0){}
	//9
	while((IoRead8 (0x25D)&0x01)!=1){}
	PCIO->Io.Read(PCIO,EfiPciWidthUint8,0x25C,1,Data);
	//*Data = IoRead8(0x25C);
	return EFI_SUCCESS;
}
EFI_STATUS InternalRamWrite (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 Data){
	UINT8 hNum, lNum;	
	//1
	lNum = (Offset&0xff);
	hNum = ((Offset>>8)&0xff);
	//2
	while((IoRead8(0x25D)&0x02)!=0){}
	//3
	//PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25D,1, 0x80);
	IoWrite8(0x25D,0x81);
	//4
	while((IoRead8 (0x25D)&0x02)!=0){}
	//5
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25C,1, &hNum);
	//6
	while((IoRead8 (0x25D)&0x02)!=0){}
	//7
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25C,1, &lNum);
	//8
	while((IoRead8 (0x25D)&0x02)!=0){}

	PCIO->Io.Read(PCIO,EfiPciWidthUint8,0x25C,1,Data);
	//*Data = IoRead8(0x25C);
	return EFI_SUCCESS;
}

EFI_STATUS ExternalRamRead (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 *Data){
	UINT8 hNum, lNum;	
	//1
	lNum = (Offset&0xff);
	hNum = ((Offset>>8)&0xff);
	//2
	while((IoRead8(0x25D)&0x02)!=0){}
	//3
	//PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25D,1, 0x80);
	IoWrite8(0x25D,0x81);
	//4
	while((IoRead8 (0x25D)&0x02)!=0){}
	//5
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25C,1, &hNum);
	//6
	while((IoRead8 (0x25D)&0x02)!=0){}
	//7
	PCIO->Io.Write(PCIO,EfiPciWidthUint8,0x25C,1, &lNum);
	//8
	while((IoRead8 (0x25D)&0x02)!=0){}
	//9
	while((IoRead8 (0x25D)&0x01)!=1){}
	PCIO->Io.Read(PCIO,EfiPciWidthUint8,0x25C,1,Data);
	//*Data = IoRead8(0x25C);
	return EFI_SUCCESS;
}

EFI_STATUS ExternalRamWrite (EZ_EC_RAM_RW_PROTOCOL *This, UINT16 Offset, UINT8 Data){
	//*Data = 100;
	return EFI_SUCCESS;
}
//EFI_STATUS InternalRamRead (this, IN UINT16 Offset, OUT UINT8 *Data);
// EFI_STATUS InternalRamWrite (this, IN UINT16 Offset, IN UINT8 Data);
// EFI_STATUS ExternalRamRead (this, IN UINT16 Offset, OUT UINT8 *Data);
// EFI_STATUS ExternalRamWrite (this, IN UINT16 Offset, IN UINT8 Data);
