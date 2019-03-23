#ifndef FDC2_H
#define FDC2_H


// port definition for secondary floppy disk driver
#define FDC2_BASE     0x370
#define FDC2_DOR_REG  0x372 //w,digital output register...xt,at
#define FDC2_MSR_REG  0x374 //r,main status register...xt,at
#define FDC2_DATA_REG 0x375 //r,w,data port...xt,at
#define FDC2_DIR_REG  0x377 //r,digital input register...at
#define FDC2_CCR_REG  0x377 //w,configuration control register...at

extern FDC_CONTROL Fdc2Ctrl;

void Fdc2Initial(void);
void Fdc2Handler(void);

#endif
