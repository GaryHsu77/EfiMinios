#ifndef PIClib_H
#define PIClib_H

#define PCIADDR(b,d,f,off) (0x80000000+((b)<<16)+((d)<<11)+((f)<<8)+((off)&0xFC))

extern VOID PCIPrintDeviceType(CAPTION *pCaption, UINT32 bus, UINT32 dev, UINT32 fun);
extern UINT8 PCIRead8 (UINT32 B, UINT32 D, UINT32 F, UINT8 offset);
extern UINT32 PCIRead32 (UINT32 B, UINT32 D, UINT32 F, UINT8 offset);
extern UINT8 IoRead8 (UINT16 port);
extern VOID IoWrite32 (UINT16 port, UINT32 data);
extern VOID PCIWrite8 (UINT32 B, UINT32 D, UINT32 F, UINT8 offset, UINT8 data);
extern VOID IoWrite8 (UINT16 port, UINT32 data);

#endif