/**************
*function:header file of fdc1.c
*description:this header file is according to intel 82077aa spec.
*----------------------------------------------------------------------
*DOR...digital output register
*bit:   7      6      5       4        3        2       1       0
*       motor3 motor2 motor1  motor0   /dmagate /reset  drive1  driver0
*----------------------------------------------------------------------
*DSR...datarate selecte register
*bit:   7      6      5       4        3        2        1        0
*       sw     power  0       precomp2 precomp1 precomp0 daterate datarate
*       reset  down                                     select1  select0
*----------------------------------------------------------------------
*MSR...main status reigster
*bit:   7      6      5       4        3        2        1        0
*       rqm    dio    nondma  cmd      drv3     drv2     drv1     drv0 
*                             busy     busy     busy     busy     busy
*----------------------------------------------------------------------
*DIR...digital input register
*bit:   7      6      5       4        3        2        1        0
*       disk   x      x       x        x        x        x        x
*       change   
*----------------------------------------------------------------------
*CCR...configuration control register
*bit:   7      6      5       4        3        2        1        0
*       -      -      -       -        -        -        datarate datarate
*                                                        select0  select1 
*----------------------------------------------------------------------
*
***************/
#ifndef FDC_H
#define FDC_H

#define FDC_DMA_EANBLE 1
#define FDC_DMA_CHANNEL 2
#define FDC_IRQ 6

#define FDC_NO_ERROR 0
#define FDC_ERROR    1
#define FDC_NODISK   2
#define FDC_TIMEROUT 3

#define FDC_WRITE 0 //same to DMA_READ
#define FDC_READ  1 //same to DMA_WRITE

// port definition for primary floppy disk driver
#define FDC_BASE        0x3f0
#define FDC_STATUS_A    0x3f0 //status register a,ps/2
#define FDC_STATUS_B    0x3f1 //status register b,ps/2
#define FDC_DOR_REG     0x3f2 //w,digital output register
#define FDC_MSR_REG     0x3f4 //r,main status register...xt,at
#define FDC_DSR_REG     0x3f4 //datarate select reigster
#define FDC_FIFO_REG    0x3f5 //r,w,data port...xt,at
#define FDC_DIR_REG     0x3f7 //r,digital input register...at
#define FDC_CCR_REG     0x3f7 //w,configuration control register...at pc

#define FDC_MSR_FDD0_BUSY    0x01 //fdd 0:busy in seek mode
#define FDC_MSR_FDD1_BUSY    0x02 //fdd 1:busy in seek mode
#define FDC_MSR_FDD2_BUSY    0x04 //fdd 2:busy in seek mode
#define FDC_MSR_FDD3_BUSY    0x08 //fdd 3:busy in seek mode
#define FDC_MSR_FDC_BUSY     0x10 //1:busy,0:not busy
#define FDC_MSR_NON_DMA      0x20 //1:fdc not in dma mode,0:fdc in dma mode
#define FDC_MSR_DIO          0x40 //1:fdc has data for cpu,0:fdc expecting data from cpu
#define FDC_MSR_RQM          0x80 //memory request...1:data register is ready,0:data register is not ready

#define FDC_DOR_DEVICENUM0   0x00 //device number 0
#define FDC_DOR_DEVICENUM1   0x01 //device number 1
#define FDC_DOR_DEVICENUM2   0x10 //device number 2
#define FDC_DOR_DEVICENUM3   0x11 //device number 3
#define FDC_DOR_RESETB       0x04 ///reset fdc ic..low active
#define FDC_DOR_DMAGATE      0x08 //enable fdc interrupt and drq
#define FDC_DOR_MOTORON_FDD0 0x10 //fdd 0 motor
#define FDC_DOR_MOTORON_FDD1 0x20 //fdd 1 motor
#define FDC_DOR_MOTORON_FDD2 0x40 //fdd 2 motor
#define FDC_DOR_MOTORON_FDD3 0x80 //fdd 3 motor


#define FDC_DIR_DISKCHANGE 0x80

#define CCR_DTR_MASK     0x03 //DTR: data transfer rate 
#define CCR_DTR_500K     0x00 //DTR=500kbits/sec
#define CCR_DTR_300K     0x01 //DTR=300kbits/sec
#define CCR_DTR_250K     0x10 //DTR=250kbits/sec
#define CCR_DTR_1M       0x11 //DTR=1mbits/sec

//fdc command definitions
//fdc data transfer commands
#define FDC_CMD_READDATA          0x06  //bit765=MT.MFM.SK
#define FDC_CMD_READDELETEDATA    0x0c  //bit765=MT.MFM.SK
#define FDC_CMD_READTRACK         0x02  //bit6=MFM
#define FDC_CMD_WRITEDATA         0x05  //bit76=MT.MFM
#define FDC_CMD_WRITEDELETEDATA   0x09  //bit76=MT.MFM
#define FDC_CMD_VERIFY            0x16  //bit765=MT.MFM.SK
#define FDC_CMD_FORMATTRACK       0x0d  //bit6=MFM
//fdc scan commands
#define FDC_CMD_SCANEQUAL         0x11  //bit765=MT.MFM.SK
#define FDC_CMD_SCANLOWEQUAL      0x19  //bit765=MT.MFM.SK
#define FDC_CMD_SCANHIGHEQUAL     0x1d  //bit765=MT.MFM.SK
//fdc control commands
#define FDC_CMD_READID            0x0a  //bit6=MFM
#define FDC_CMD_RECALIBRATE       0x07
#define FDC_CMD_SEEK              0x0f  
#define FDC_CMD_SENSEINTERRUPTSTATUS 0x08
#define FDC_CMD_SENSEDRIVESTATUS  0x04
#define FDC_CMD_SPECIFY           0x03 
#define FDC_CMD_CONFIGURE         0x13
#define FDC_CMD_VERSION           0x10 
#define FDC_CMD_RELATIVESEEK      0x8f  //bit6=DIR
#define FDC_CMD_DUMPREG           0x0e
//fdc command set enhencement
#define FDC_CMD_PERPENDICULARMODE 0x12
#define FDC_CMD_LOCK              0x14  //bit7=LOCK

#define FDC_MT   0x80        //multi track...treat track0 at head 0 track0 at head as a track
#define FDC_MFM  0x40      //modified fm...set 1 if floppy is double density
#define FDC_SK   0x20        //skip delete...set 1 it will skip sector that is marked as delete
#define FDC_COMMAND_ATTRIBUTE (FDC_MT|FDC_MFM|FDC_SK)

#define FDC_HEAD_PER_DISK 2
#define FDC_TRACK_PER_HEAD 80
#define FDC_SECTOR_PER_TRACK 18
#define FDC_TOTAL_SECTOR (FDC_HEAD_PER_DISK*FDC_TRACK_PER_HEAD*FDC_SECTOR_PER_TRACK) //2880
#define FDC_GAP3 0x1b
#define FDC_RATE CCR_DTR_500K //500 kbits/sec
#define FDC_HEAD_UNLOAD_TIME 0xcf
#define FDC_GAP3_FORMATING 0x6c

#define FDC_DMA_READ 0x44
#define FDC_DMA_WRITE 0x48

#define FDC_DEVICE_NONE     0
#define FDC_DEVICE_NEC765   1
#define FDC_DEVICE_ENHENCED 2

#define FDC_DISK_CHANGE 0x01
#define FDC_SPIN_UP     0x02
#define FDC_SPIN_DOWN   0x04

#define FDC_HLT 0x08 //head load time
#define FDC_HUT 0x0f //head unload time 
#define FDC_SRT 0x0c //step rate time
#if(FDC_DMA_EANBLE==0)
    #define FDC_ND 1    //non-dma=1...no use dma
#else
    #define FDC_ND 0    //non-dma=0...use dma
#endif

#define FDC_GAP3 0x1B    



#define FDC_IC_NORMAL   0x00
#define FDC_IC_ABNORMAL 0x40
#define FDC_IC_INVALID  0x80
#define FDC_IC_ABNORMAL_POLLING 0xc0

#define FDC_SECTORSIZE_128  0x00
#define FDC_SECTORSIZE_256  0x01
#define FDC_SECTORSIZE_512  0x02
#define FDC_SECTORSIZE_1k   0x03
#define FDC_SECTORSIZE_2k   0x04
#define FDC_SECTORSIZE_4k   0x05
#define FDC_SECTORSIZE_8k   0x06
#define FDC_SECTORSIZE_16k  0x07

#define FDC_DRIVE0 0x00
#define FDC_DRIVE1 0x01
#define FDC_DRIVE2 0x02
#define FDC_DRIVE3 0x03

#define FDC_IDLE       0
#define FDC_IN_NONDATA 1
#define FDC_IN_READ    2
#define FDC_IN_WRITE   3

typedef struct{
    U32 CmosType;  
    U8  *Name;
}FDC_RECORD;

typedef struct{
    U8 State;
    U8 DorReg;
    U8 MsrReg;
    U8 HasInterrupt;
    U8 ControllerType;
    U8 Device0Type;
    U8 Device1Type;
    U32 PreviousTime;
    U32 CurrentTime;
    U32 TimeLimit;
    U16 ReTries;
    U16 BufferIndex;
    U8 FdcResultBuffer[8];
}FDC_CONTROL;

void FdcInit(void);
void FdcHandler(void);
void FdcStart(void);
bool FdcSeekProcedure(U8);
bool FdcSeek(U8 TrackNumber);
void FdcVersion(void);
bool FdcSpecify(void);
bool FdcSenseInterruptStatus(void);
bool FdcWriteFifo(U8 Data);
U8 FdcReadFifo(void);
void FdcWriteDor(U8 Data);
U8 FdcReadMsr(void);	
void FdcTimeDelay(U16 Time);

#endif
