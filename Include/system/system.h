#ifndef SYSTEM_H
#define SYSTEM_H

#define SaveFlag() __asm__ __volatile__("pushfd")
#define RestoreFlag()  __asm__ __volatile__("popfd")
#define DisableInterrupt() __asm__ __volatile__("cli")
#define EnableInterrupt()  __asm__ __volatile__("sti")
#define SystemHalt()  __asm__ __volatile__("hlt")

typedef struct{
    UINT16 OffsetLow;          // low word of handler addres
    UINT16 Selector;           // segment selector...same with code segment
    UINT8  Dcount;	            // call gate use this
    UINT8  Attribute;          //
    UINT16 OffsetHigh;         // low word of handler addres
}GATE;

#endif
