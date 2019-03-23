#ifndef OS_DEFINE_H
#define OS_DEFINE_H

/*********************************************
*prototype definition used in operation system
*********************************************/
typedef UINT32 OS_STACK; 
typedef UINT32 OS_ERROR;
typedef VOID (*Task_Func)(VOID *);

#define GDP Print

#define OS_BOOL UINT8
#define	OS_TRUE	 1
#define	OS_FALSE 0
#define OS_NULL 0

/*********************************************
* os error definition
*********************************************/
#define OS_NO_ERROR             0
#define OS_IS_ERROR             1
#define OS_ERROR_TIMEOUT        2
#define OS_ERROR_NULL_POINTER   3
#define OS_ERROR_EVENT_TYPE     4

#define OS_PENDING_NONE      0
#define OS_PENDING_TIME      1
#define OS_PENDING_RESOURCE  2
#define OS_PENDING_EVENT     3

#define OS_NAME_STRING_MAX 16

/*********************************************
* task switch setting
*********************************************/
#define OS_INT_LEVEL_CSW_ENABLE  1     // enable time scheduler
#define OS_TASK_SWITCH_TIME      1     // ticks
#define OS_TIME_EVENT_ENABLE     1     // default support...no disable it

/*********************************************
* os memory control structure definition
**********************************************/
#define OS_MEMORY_STATUS_FREE 0
#define OS_MEMORY_STATUS_USED 1

#define OS_MEMORY_ENTRY_SIZE 36  // size of OS_MEMORY

typedef struct os_memory{        // 28 bytes
    UINT8 Sinature[4];
    UINT8 Status;
    UINT8 Reserve[3];
    UINT8* pMemory;                 // memory address
    UINT32 Length;                  // memory lenth
    UINT32 *pUser;                  // task that use this memory
    struct os_memory *Prev;      // memory link list
    struct os_memory *Next;      // memory link list
    struct os_memory *TmPrev;  // task memory link list
    struct os_memory *TmNext;  // task memory link list
}OS_MEMORY;

/*********************************************
* os event control structure definition
**********************************************/
#define OS_EVENT_TIME     0
#define OS_EVENT_KEYBOARD 1
#define OS_EVENT_MOUSE    2
#define OS_EVENT_UART1    3
#define OS_EVENT_UART2    4
#define OS_EVENT_RTC      5 

typedef struct os_event{
    UINT32 Type;
    UINT8 *pName;                     //event name
    UINT32 *ListHead;                 //task pending for this event or resource
    UINT32 *ListTail;                 //task pending for this event or resource
    struct os_event *Prev;         //event link list
    struct os_event *Next;         //event link list
}OS_EVENT;

/*********************************************
* os resource control structure definition
**********************************************/
#define OS_RESOURCE_GUI 1

typedef struct os_resource{
    UINT8  InUse;                     //in use or not
    UINT8 *pName;                     //resource name
    UINT32 *pUser;                    //pointer to user task that use this resource
    UINT32 Type;                      //resource type
    UINT32 *ListHead;                 //task pending for this event or resource
    UINT32 *ListTail;                 //task pending for this event or resource
    struct os_resource *Prev;      // event link list
    struct os_resource *Next;      // event link list
    struct os_resource *TmPrev;
    struct os_resource *TmNext;
}OS_RESOURCE;

/*********************************************
* os timer
**********************************************/
typedef struct os_timer{
    UINT32 Timer;
    struct os_timer *Prev;
    struct os_timer *Next;
    struct os_timer *TmPrev;
    struct os_timer *TmNext;
}OS_TIMER;

/*********************************************
* os task control structure definition
**********************************************/
#define OS_TASK_FREE      0   //task status
#define OS_TASK_READY     1
#define OS_TASK_PENDING   2
#define OS_TASK_SUSPEND   3
#define OS_TASK_EXECUTION 4
#define STACK_SIZE (64*1024)

typedef struct{
	UINTN MultiThread_BX;
	UINTN MultiThread_SP;
	UINTN MultiThread_BP;
	UINTN MultiThread_DI;
	UINTN MultiThread_SI;
	UINTN MultiThread_10;
	UINTN MultiThread_11;
	UINTN MultiThread_12;
	UINTN MultiThread_13;
	UINTN MultiThread_14;
	UINTN MultiThread_15;
	UINTN MultiThread_IP;
}TASK_REG;//MultiThread_REG

typedef struct os_tcb{
	CHAR8 Signature[4];
	BOOLEAN MainThread;
	BOOLEAN FirstTime;
	UINT8 Status; 
	UINT8 Priority;
	UINT8 WeightedPriority;  
	UINT8 PendingType;            //event or resource
	UINT32 TimeDelay;             //65535*1ms=65.535sec...long enough
	UINT32 Id;              
	UINT32 Window;                //window control structure
	UINT8 *pName;                 //task name
	UINT32 PendingWhere;          //pending on event or resource
	OS_RESOURCE *ResourceList;
	OS_MEMORY *MemoryList;     //memory used in task
	OS_TIMER *TimerList;       //timer used in task
	EFI_TPL ThreadTPL;
	struct os_tcb *Next;
	struct os_tcb *Prev;
	struct os_tcb *TmNext;
	struct os_tcb *TmPrev;
	Task_Func function_p;
	VOID *arg;
	EFI_PHYSICAL_ADDRESS Stack;
	TASK_REG Regs;
}OS_TCB;

/*********************************************
* os time
**********************************************/

typedef struct os_time{
    UINT8 Second;
    UINT8 Minute;
    UINT8 Hour;
    UINT8 Day;
    UINT8 Date;
    UINT8 Month;
    UINT8 Year;
}OS_TIME;

#endif

