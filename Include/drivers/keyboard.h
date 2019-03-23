#ifndef KEYBOARD_H
#define KEYBOARD_H

// KEY MAPPING TABLE
#define KEY_RELEASE 0x80
#define KEY_PRESS 0x00

#define KEY_MINUS 0x0c
#define KEY_EQUAL 0x0d
#define KEY_UL2DR_SLASH 0x2b
#define KEY_DIVIDE 0x035       
#define KEY_DOT 0x034           // .
#define KEY_UPPER_DOT 0x028     // '
#define KEY_COMMA 0x033         // ,
#define KEY_UPPER_COMMA 0x29    // `
#define KEY_SEMICOLON 0x27      // ;  colon is ':'
#define KEY_LEFT_BRACKET 0x1a   // [
#define KEY_RIGHT_BRACKET 0x1b  // ]

#define KEY_0 0x0b
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0a

#define KEY_a 0x1e
#define KEY_b 0x30
#define KEY_c 0x2e
#define KEY_d 0x20
#define KEY_e 0x12
#define KEY_f 0x21
#define KEY_g 0x22
#define KEY_h 0x23
#define KEY_i 0x17
#define KEY_j 0x24
#define KEY_k 0x25
#define KEY_l 0x26
#define KEY_m 0x32
#define KEY_n 0x31
#define KEY_o 0x18
#define KEY_p 0x19
#define KEY_q 0x10
#define KEY_r 0x13
#define KEY_s 0x1f
#define KEY_t 0x14
#define KEY_u 0x16
#define KEY_v 0x2f
#define KEY_w 0x11
#define KEY_x 0x2d
#define KEY_y 0x15
#define KEY_z 0x2c

#define KEY_F1 0x3b
#define KEY_F2 0x3c
#define KEY_F3 0x3d
#define KEY_F4 0x3e
#define KEY_F5 0x3f
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x57
#define KEY_F12 0x58

#define KEY_ESC 0x01
#define KEY_NUMLOCK 0x45
#define KEY_SCROLL_LOCK 0x46

#define KEY_SHIFT_RIGHT 0x36
#define KEY_SHIFT_LEFT  0x2a
#define KEY_ALT_LEFT    0x38
#define KEY_CAPSLOCK    0x3a
#define KEY_TAB         0x0f
#define KEY_CTRL_LEFT   0x1d
#define KEY_ENTER       0x1c
#define KEY_BACKSPACE   0x0e
#define KEY_SPACE       0x39

#define KEY_NUMPAD_0 0x52
#define KEY_NUMPAD_1 0x4f
#define KEY_NUMPAD_2 0x50
#define KEY_NUMPAD_3 0x51
#define KEY_NUMPAD_4 0x4b
#define KEY_NUMPAD_5 0x4c
#define KEY_NUMPAD_6 0x4d
#define KEY_NUMPAD_7 0x47
#define KEY_NUMPAD_8 0x48
#define KEY_NUMPAD_9 0x49
#define KEY_NUMPAD_DOT 0x53
#define KEY_NUMPAD_STAR 0x37
#define KEY_NUMPAD_MINUS 0x4a
#define KEY_NUMPAD_PLUS 0x4e

#define KEY_NUMPAD_DIVIDE 0x35 //e0 35 e0 b5
#define KEY_NUMPAD_ENTER 0x1c //e0 1c e0 9c
#define KEY_PRTSC       0x37  //e0 37 e0 b7
#define KEY_HOME        0x47  //e0 47 e0 c7
#define KEY_END         0x4f  //e0 4f e0 cf
#define KEY_PAGEUP      0x49  //e0 49 e0 c9
#define KEY_PAGEDOWN    0x51  //e0 51 e0 d1
#define KEY_ARROWUP     0x48  //e0 48 e0 c8
#define KEY_ARROWDOWN   0x50  //e0 50 e0 d0
#define KEY_ARROWLEFT   0x4b  //e0 4b e0 cb
#define KEY_ARRORRIGHT  0x4d  //e0 4d e0 cd
#define KEY_DEL         0x53  //e0 53 e0 d3
#define KEY_INS         0x52  //e0 52 e0 d2
#define KEY_ALT_RIGHT   0x38  //e0 38 e0 b8
#define KEY_CTRL_RIGHT  0x1d  //e0 1d e0 9d

#define KEY_WINDOWS_MENU 0x5d  //e0 5d e0 dd
#define KEY_WINDOWS_START 0x5b //e0 5b e0 db

#define KEY_PAUSE       0xe1 //0x1d 0x45 0xe1 0x9d 0xc5

// key definition

#define ASCII_NUL 0x00
#define ASCII_SOH 0x01
#define ASCII_STX 0x02
#define ASCII_ETX 0x03
#define ASCII_EOT 0x04
#define ASCII_ENQ 0x05
#define ASCII_ACK 0x06
#define ASCII_BEL 0x07
#define ASCII_BS 0x08
#define ASCII_HT 0x09
#define ASCII_LF 0x0a
#define ASCII_VT 0x0b
#define ASCII_FF 0x0c
#define ASCII_CR 0x0d
#define ASCII_SO 0x0e
#define ASCII_SI 0x0f
#define ASCII_DLE 0x10
#define ASCII_DC1 0x11
#define ASCII_DC2 0x12
#define ASCII_DC3 0x13
#define ASCII_DC4 0x14
#define ASCII_NAK 0x15
#define ASCII_SYN 0x16 
#define ASCII_ETB 0x17
#define ASCII_CAN 0x18
#define ASCII_EM  0x19
#define ASCII_SUB 0x1a
#define ASCII_ESC 0x1b
#define ASCII_FS 0x1c
#define ASCII_GS 0x1d
#define ASCII_RS 0x1e
#define ASCII_US 0x1f
#define ASCII_SP 0x20
#define ASCII_DEL 0x7f

#define KB_SPECIAL_F1_KEY               0x80
#define KB_SPECIAL_F2_KEY               0x81
#define KB_SPECIAL_F3_KEY               0x82
#define KB_SPECIAL_F4_KEY               0x83
#define KB_SPECIAL_F5_KEY               0x84
#define KB_SPECIAL_F6_KEY               0x85
#define KB_SPECIAL_F7_KEY               0x86
#define KB_SPECIAL_F8_KEY               0x87
#define KB_SPECIAL_F9_KEY               0x88
#define KB_SPECIAL_F10_KEY              0x89
#define KB_SPECIAL_F11_KEY              0x8a
#define KB_SPECIAL_F12_KEY              0x8b
#define KB_SPECIAL_PRTSCR_KEY           0x8c
#define KB_SPECIAL_SCROLL_LOCK_KEY      0x8d
#define KB_SPECIAL_PAUSE_BREAK_KEY      0x8e
#define KB_SPECIAL_TAB_KEY              0x8f
#define KB_SPECIAL_SHIFT_AT_LEFT_KEY    0x90
#define KB_SPECIAL_SHIFT_AT_RIGHT_KEY   0x91
#define KB_SPECIAL_CTRL_AT_LEFT_KEY     0x92
#define KB_SPECIAL_CTRL_AT_RIGHT_KEY    0x93
#define KB_SPECIAL_WINDOW_AT_LEFT_KEY   0x94
#define KB_SPECIAL_WINDOW_AT_RIGHT_KEY  0x95
#define KB_SPECIAL_ATL_AT_LEFT_KEY      0x96
#define KB_SPECIAL_ATL_AT_RIGHT_KEY     0x97
#define KB_SPECIAL_MENUS_KEY            0x98
#define KB_SPECIAL_INSERT_KEY           0x99
#define KB_SPECIAL_HOME_KEY             0x9a
#define KB_SPECIAL_PAGE_DOWN_KEY        0x9b
#define KB_SPECIAL_END_KEY              0x9c
#define KB_SPECIAL_PAGE_UP_KEY          0x9d
#define KB_SPECIAL_CAP_LOCK_KEY         0x9e
#define KB_SPECIAL_UP_ARROW_KEY         0x9f
#define KB_SPECIAL_LEFT_ARROW_KEY       0xa0
#define KB_SPECIAL_DOWN_ARROW_KEY       0xa1
#define KB_SPECIAL_RIGHT_ARROW_KEY      0xa2
#define KB_SPECIAL_NUM_LOCK_KEY         0xa3
#define KB_SPECIAL_INS                  0xa4

// keyboard controlLer 8042 port definitions
#define KB_DATA_REG 0x60
#define KB_CMD_REG 0x64
#define KB_STATUS_REG 0x64

// keyboard command definitions
#define KB_CMD_READMODE 0x20
#define KB_CMD_WRITEMODE 0x60
#define KB_CMD_SELFTEST 0xaa
#define KB_CMD_INTERFACETEST 0xab
#define KB_CMD_DISABLEKB 0xad
#define KB_CMD_ENABLEKB 0xae
#define KB_CMD_READ_INPORT 0xc0
#define KB_CMD_READ_OUTPORT 0xd0
#define KB_CMD_WRITE_OUTPORT 0xd1
#define KB_CMD_READ_TESTINPUTS 0xe0
#define KB_CMD_READ_SYSTEM_RESET 0xfe

#define KB_CMD_DISABLE_MOUSE 0xa7
#define KB_CMD_ENABLE_MOUSE 0xa8
#define KB_CMD_TEST_MOUSE 0xa9
#define KB_CMD_WRITE_MOUSE 0xd4

#define KB_CMD_READ_COPYRIGHT  0xa0
#define KB_CMD_READ_FWVERSION  0xa1
#define KB_CMD_SWITCH_SPEED    0xa2
#define KB_CMD_SWITCH_SPEED2   0xa3
#define KB_CMD_CHECK_PWD_INSTALL 0xa4
#define KB_CMD_LOAD_PASSWORD   0xa5
#define KB_CMD_CHECK_PASSWORD  0xa6
#define KB_CMD_DIAGNOSTIC_DUMP 0xac
#define KB_CMD_READ_KBVERSION  0xaf
#define KB_CMD_INPORT_POLLLOW  0xc1
#define KB_CMD_INPORT_POLLHIGH 0xc2
#define KB_CMD_UNBLOCK_P22P23  0xc8
#define KB_CMD_BLOCK_P22P23    0xc9
#define KB_CMD_READ_KBMODE     0xca
#define KB_CMD_WRITE_KBMODE    0xcb
#define KB_CMD_WRITE_KB_OUTPUT_BUFFER    0xd2
#define KB_CMD_WRITE_MOUSE_OUTPUT_BUFFER    0xd3
#define KB_CMD_DISABLE_A20     0xdd
#define KB_CMD_ENABLE_A20      0xdf

//status bit definition
#define KB_STATUS_PARITY_ERROR 0x80
#define KB_STATUS_TIMEOUT      0x40
#define KB_STATUS_AUXOUTBUFULL 0x20         // auxiliary output buffer full
#define KB_STATUS_LOCK 0x10                 // 0:lock,1:unlock
#define KB_STATUS_CMD_DATA 0x08             // 0:last write is data,1:last
#define KB_STATUS_SYSTEM_FLAG 0x04          // 0: after POR,1:selt test successful
#define KB_STATUS_INPUT_BUFFER_STATUS 0x02  // 0:empty,1 full
#define KB_STATUS_OUTPUT_BUFFER_STATUS 0x01 // 0:empty,1 full

//CCB bit definition...CCB is brief of controller command byte
#define KB_CCB_TRANSLATE     0x40
#define KB_CCB_MOUSE_ENABLE  0x20
#define KB_CCB_KB_ENABLE     0x10
#define KB_CCB_IGNORE_KBLOCK 0x08
#define KB_CCB_SYSTEMFLAG    0x04
#define KB_CCB_MOUSE_INT_ENABLE 0x02
#define KB_CCB_KB_INT_ENABLE 0x01

#define KB_CCB_SETTING (KB_CCB_TRANSLATE|KB_CCB_SYSTEMFLAG|KB_CCB_MOUSE_INT_ENABLE|KB_CCB_KB_INT_ENABLE )

#define LED_CODE 0xed
#define KB_ACK 0xfa

#define KB_SCROLLLOCK_LED 0x01
#define KB_NUMBERLOCK_LED 0x02
#define KB_CAPSLOCK_LED 0x04

#define KEYBOARD_KEYBUFFER_SZIE 50

//GDB : EFI KEY DEFINE >>>
#define EFI_KEY_UP 		0x01
#define EFI_KEY_DOWN 	0x02
#define EFI_KEY_RIGHT 	0x03
#define EFI_KEY_LEFT 	0x04
//GDB : EFI KEY DEFINE <<<

typedef struct{
    UINT8 State;
    UINT8 LedValue;
    UINT16 ExtendKeyCode;
    //UINT16 Timer; // for scan code time out use 
    BOOLEAN LedChange;
    BOOLEAN Ack;
    BOOLEAN ScrollLock;
    BOOLEAN CapsLock;
    BOOLEAN NumLock;
    BOOLEAN LeftCtrl;
    BOOLEAN LeftShift;
    BOOLEAN LeftAlt;
    BOOLEAN RightCtrl;
    BOOLEAN RightShift;
    BOOLEAN RightAlt;
    UINT8 BufferStatus;
    UINT16 Put;
    UINT16 Get;
    UINT16 *pDataBuffer;
    OS_EVENT KeyboardEvent;
    OS_TIMER MyTimer;
	SIMPLE_INPUT_INTERFACE *ConIn;
	EFI_INPUT_KEY *Key;
}KEYBOARD_CONTROL;

extern KEYBOARD_CONTROL *pOsDriverKeyboard;

VOID KeyboardInit(VOID);
VOID KeyboardStop(VOID);
VOID KeyboardHandler(VOID);
VOID KeyboardEnable(VOID);
VOID KeyboardBusyWait(VOID);
VOID KeyboardAckWait(VOID);
VOID KeyboardSetLed(VOID);

BOOLEAN KeyboardDataScan();

UINT8 KeyboardKeyBufferCheck(VOID);
UINT8 KeyboardKeyBufferCheckIsr(VOID);
VOID KeyboardKeyBufferPutIsr(UINT16 Data);
UINT16 KeyboardKeyBufferGet(VOID);

#endif
