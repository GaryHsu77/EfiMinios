#ifndef PIC_H
#define PIC_H

#define PIC_INT_VECTOR_IRQ0 0x20
#define PIC_INT_VECTOR_IRQ8 0x28
#define	PIC_MASTER      0x20
#define	PIC_MASTER2     0x21
#define	PIC_SLAVE       0xA0
#define	PIC_SLAVE2      0xA1

//irq0  timer 8254
//irq1  keyboard 8042
//irq2  slave pic 8259
//irq3  com2
//irq4  com1
//irq5  lpt2
//irq6  fdc
//irq7  lpt1

//irq8  rtc
//irq9  redir irq2
//irq10 user
//irq11 user
//irq12 user
//irq13 fpu
//irq14 hdc
//irq15 reserve

void PicInit(void);

#endif