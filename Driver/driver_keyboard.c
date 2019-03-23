#include <includes.h>

#define KeyboardIdleState                  0
#define KeyboardGeneralcodeState           1
#define KeyboardExtendcodeState            2
#define KeyboardExtraExtendcode1stState    3
#define KeyboardExtraExtendcode2stState    4

KEYBOARD_CONTROL *pOsDriverKeyboard;

VOID KeyboardInit(VOID)
{
	EFI_STATUS Status ;	

	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(KEYBOARD_CONTROL),&pOsDriverKeyboard);
	if(Status != EFI_SUCCESS)return;

    pOsDriverKeyboard->State=KeyboardGeneralcodeState;
    pOsDriverKeyboard->MyTimer.Timer=0;
    pOsDriverKeyboard->LedValue=0;
    pOsDriverKeyboard->LedChange=FALSE;
    pOsDriverKeyboard->Ack=FALSE;
    pOsDriverKeyboard->ScrollLock=FALSE;
    pOsDriverKeyboard->CapsLock=FALSE;
    pOsDriverKeyboard->NumLock=FALSE;
    pOsDriverKeyboard->LeftCtrl=FALSE;
    pOsDriverKeyboard->LeftShift=FALSE;
    pOsDriverKeyboard->LeftAlt=FALSE;
    pOsDriverKeyboard->RightCtrl=FALSE;
    pOsDriverKeyboard->RightShift=FALSE;
    pOsDriverKeyboard->RightAlt=FALSE;
    pOsDriverKeyboard->Put=0;
    pOsDriverKeyboard->Get=0;
	pOsDriverKeyboard->ConIn=gConIn;
	
	Status = gBS->AllocatePool(EfiBootServicesData,KEYBOARD_KEYBUFFER_SZIE*2,&(pOsDriverKeyboard->pDataBuffer));
	if(Status != EFI_SUCCESS)return;
	
    if(pOsDriverKeyboard->pDataBuffer!=(UINT16 *)NULL) pOsDriverKeyboard->BufferStatus=BUFFER_GOOD;
    else {
		pOsDriverKeyboard->BufferStatus=BUFFER_FAIL;
	}
    OsEventAdd(&pOsDriverKeyboard->KeyboardEvent,"DRIVER_KEYBOARD",OS_EVENT_KEYBOARD);
	OsTimeTimerPut(&pOsDriverKeyboard->MyTimer);
	SystemGuiStringPrint(L">>> KeyboardInit end <<<<<<<<<<\n");
}

BOOLEAN KeyboardDataScan()
{
	MY_MUTEX mutex;
	mutex = OsEnterCritical();
	if(gConIn->ReadKeyStroke(gConIn,pOsDriverKeyboard->Key) == EFI_SUCCESS )
	{
		if(pOsDriverKeyboard->Key->ScanCode==0) KeyboardKeyBufferPutIsr(pOsDriverKeyboard->Key->UnicodeChar);
		else KeyboardKeyBufferPutIsr(pOsDriverKeyboard->Key->ScanCode);
		
		OsExitCritical(mutex);
		return TRUE;
	}
	OsExitCritical(mutex);
	return FALSE;
}

VOID KeyboardEnable(VOID)
{
    //PicIrqDisable(IRQ1_KEYBOARD);
	// write CCB
	MY_MUTEX mutex;
	mutex = OsEnterCritical();
	pOsDriverKeyboard->Ack=FALSE;
	KeyboardBusyWait();
	OutByte(KB_CMD_REG,KB_CMD_WRITEMODE); // write 0x60 ram
    KeyboardAckWait();
    
	pOsDriverKeyboard->Ack=FALSE;
	KeyboardBusyWait();
	OutByte(KB_DATA_REG,KB_CCB_SETTING); // translate_code=1,keyboard_en=0,systemflag=1,mouse_int=1,keyboard_int=1
    KeyboardAckWait();
    OsExitCritical(mutex);
    //PicIrqEnable(IRQ1_KEYBOARD);
}

VOID KeyboardHandler(VOID)
{
    UINT8 ScanCode;
    UINT8 KeyCode;
    UINT8 KeyStatus;
    
    ScanCode=InByte(KB_DATA_REG);
    if(ScanCode==KB_ACK){
    	pOsDriverKeyboard->Ack=TRUE;
    	return;
    }
    switch(pOsDriverKeyboard->State){
    	case KeyboardIdleState:
    	    //do nothing because keyboard buffer is not ready
    	    break;
    	case KeyboardGeneralcodeState:
    	    if(ScanCode==0xe0){
    	    	 pOsDriverKeyboard->State=KeyboardExtendcodeState;
    	    	 break;
    	    }
    	    else if(ScanCode==0xe1){
    	    	 pOsDriverKeyboard->State=KeyboardExtraExtendcode1stState;
    	    	 break;
    	    }
            KeyStatus=ScanCode&0x80;
            ScanCode=ScanCode&0x7f;
    	    switch(ScanCode){
    	        case KEY_0:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode=')';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode=')';
    	            else  KeyCode='0'; 
    	            break;
    	        case KEY_1:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='!';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='!';
    	            else  KeyCode='1';
    	            break; 
    	        case KEY_2:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='@';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='@';
    	            else  KeyCode='2';
    	            break; 
    	        case KEY_3:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='#';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='#';
    	            else  KeyCode='3';
    	            break; 
    	        case KEY_4:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='$';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='$';
    	            else  KeyCode='4';
    	            break; 
    	        case KEY_5:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='%';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='%';
    	            else  KeyCode='5';
    	            break; 
    	        case KEY_6:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='^';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='^';
    	            else  KeyCode='6';
    	            break; 
    	        case KEY_7:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='&';          //'&';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='&';    //'&';
    	            else  KeyCode='7';
    	            break; 
    	        case KEY_8:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='*';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='*';
    	            else  KeyCode='8';
    	            break; 
    	        case KEY_9:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='(';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='(';
    	            else  KeyCode='9';
    	            break; 
    	        case KEY_a: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='A';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='A';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='A';
    	            else  KeyCode='a';
    	            break;
    	        case KEY_b: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='B';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='B';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='B';
    	            else  KeyCode='b';
    	            break;
    	        case KEY_c: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='C';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='C';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='C';
    	            else  KeyCode='c';
    	            break;
    	        case KEY_d: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='D';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='D';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='D';
    	            else  KeyCode='d';
    	            break;
    	        case KEY_e: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='E';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='E';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='E';
    	            else  KeyCode='e';
    	            break;
    	        case KEY_f: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='F';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='F';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='F';
    	            else  KeyCode='f';
    	            break;
    	        case KEY_g: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='G';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='G';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='G';
    	            else  KeyCode='g';
    	            break;
    	        case KEY_h: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='H';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='H';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='H';
    	            else  KeyCode='h';
    	            break;
    	        case KEY_i: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='I';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='I';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='I';
    	            else  KeyCode='i';
    	            break;
    	        case KEY_j: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='J';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='J';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='J';
    	            else  KeyCode='j';
    	            break;
    	        case KEY_k: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='K';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='K';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='K';
    	            else  KeyCode='k';
    	            break;
    	        case KEY_l: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='L';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='L';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='L';
    	            else  KeyCode='l';
    	            break;
    	        case KEY_m: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='M';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='M';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='M';
    	            else  KeyCode='m';
    	            break;
    	        case KEY_n: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='N';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='N';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='N';
    	            else  KeyCode='n';
    	            break;
    	        case KEY_o: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='O';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='O';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='O';
    	            else  KeyCode='o';
    	            break;
    	        case KEY_p: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='P';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='P';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='P';
    	            else  KeyCode='p';
    	            break;
    	        case KEY_q: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='Q';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='Q';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='Q';
    	            else  KeyCode='q';
    	            break;
    	        case KEY_r: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='R';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='R';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='R';
    	            else  KeyCode='r';
    	            break;
    	        case KEY_s: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='S';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='S';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='S';
    	            else  KeyCode='s';
    	            break;
    	        case KEY_t: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='T';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='T';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='T';
    	            else  KeyCode='t';
    	            break;
    	        case KEY_u: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='U';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='U';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='U';
    	            else  KeyCode='u';
    	            break;
    	        case KEY_v: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='V';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='V';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='V';
    	            else  KeyCode='v';
    	            break;
    	        case KEY_w: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='W';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='W';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='W';
    	            else  KeyCode='w';
    	            break;
    	        case KEY_x: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='X';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='X';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='X';
    	            else  KeyCode='x';
    	            break;
    	        case KEY_y: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='Y';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='Y';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='Y';
    	            else  KeyCode='y';
    	            break;
    	        case KEY_z: 
    	            if(pOsDriverKeyboard->CapsLock==TRUE) KeyCode='Z';
    	            else if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='Z';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='Z';
    	            else  KeyCode='z';
    	            break;
    	        case KEY_MINUS:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='_';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='_';
    	            else  KeyCode='-'; 
    	            break;
    	        case KEY_EQUAL:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='+';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='+';
    	            else  KeyCode='='; 
    	            break;
    	        case KEY_UL2DR_SLASH:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='|';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='|';
    	            else  KeyCode='\\'; 
    	            break;
    	        case KEY_DIVIDE:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='?';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='?';
    	            else  KeyCode='/'; 
    	            break;
    	        case KEY_DOT:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='>';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='>';
    	            else  KeyCode='.'; 
    	            break;
    	        case KEY_UPPER_DOT:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='"';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='"';
    	            else  KeyCode='\''; 
    	            break;
    	        case KEY_COMMA:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='<';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='<';
    	            else  KeyCode=','; 
    	            break;
    	        case KEY_UPPER_COMMA:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='~';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='~';
    	            else  KeyCode='`'; 
    	            break;
    	        case KEY_SEMICOLON:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode=':';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode=':';
    	            else  KeyCode=';'; 
    	            break;
    	        case KEY_LEFT_BRACKET:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='{';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='{';
    	            else  KeyCode='['; 
    	            break;
    	        case KEY_RIGHT_BRACKET:
    	            if(pOsDriverKeyboard->LeftShift==TRUE) KeyCode='}';
    	            else if(pOsDriverKeyboard->RightShift==TRUE) KeyCode='}';
    	            else  KeyCode=']'; 
    	            break;
    	        case KEY_F1:  KeyCode=0x80; break;
    	        case KEY_F2:  KeyCode=0x81; break;
    	        case KEY_F3:  KeyCode=0x82; break;
    	        case KEY_F4:  KeyCode=0x83; break;
    	        case KEY_F5:  KeyCode=0x84; break;
    	        case KEY_F6:  KeyCode=0x85; break;
    	        case KEY_F7:  KeyCode=0x86; break;
    	        case KEY_F8:  KeyCode=0x87; break;
    	        case KEY_F9:  KeyCode=0x88; break;
    	        case KEY_F10: KeyCode=0x89; break;
    	        case KEY_F11: KeyCode=0x8a; break;
    	        case KEY_F12: KeyCode=0x8b; break;
    	        case KEY_ESC: KeyCode=0x1b; break;
    	        case KEY_NUMLOCK:
    	            if(KeyStatus==KEY_PRESS){
    	                if(pOsDriverKeyboard->NumLock==TRUE) pOsDriverKeyboard->NumLock=FALSE;
    	                else pOsDriverKeyboard->NumLock=TRUE;
    	                pOsDriverKeyboard->LedChange=TRUE;
    	            }   
    	            KeyCode=0xa3; 
    	            break;
    	        case KEY_SCROLL_LOCK:
    	            if(KeyStatus==KEY_PRESS){
    	                if(pOsDriverKeyboard->ScrollLock==TRUE) pOsDriverKeyboard->ScrollLock=FALSE;
    	                else pOsDriverKeyboard->ScrollLock=TRUE;
    	                pOsDriverKeyboard->LedChange=TRUE;
    	            }   
    	            KeyCode=0x8d; 
    	            break;
    	        case KEY_SHIFT_RIGHT:
    	            if(KeyStatus==KEY_RELEASE) pOsDriverKeyboard->RightShift=FALSE;
    	            else pOsDriverKeyboard->RightShift=TRUE;
    	            KeyCode=0x91; 
    	            break;
    	        case KEY_SHIFT_LEFT:
    	            if(KeyStatus==KEY_RELEASE) pOsDriverKeyboard->LeftShift=FALSE;
    	            else pOsDriverKeyboard->LeftShift=TRUE;
    	            KeyCode=0x90; 
    	            break;
    	        case KEY_ALT_LEFT:
    	            if(KeyStatus==KEY_RELEASE) pOsDriverKeyboard->LeftAlt=FALSE;
    	            else pOsDriverKeyboard->LeftAlt=TRUE;
    	            KeyCode=0x96;
    	            break;
    	        case KEY_CAPSLOCK:
    	            if(KeyStatus==KEY_PRESS){
    	            	if(pOsDriverKeyboard->CapsLock==TRUE) pOsDriverKeyboard->CapsLock=FALSE;
    	                else pOsDriverKeyboard->CapsLock=TRUE;
    	                pOsDriverKeyboard->LedChange=TRUE;
    	            }   
    	            KeyCode=0x9e; 
    	            break;
    	        case KEY_TAB:
    	            KeyCode=0x8f; 
    	            break;
    	        case KEY_CTRL_LEFT:
    	            if(KeyStatus==KEY_RELEASE) pOsDriverKeyboard->LeftCtrl=FALSE;
    	            else pOsDriverKeyboard->LeftCtrl=TRUE;
    	            KeyCode=0x92; 
    	            break;
    	        case KEY_ENTER:      KeyCode=0x0d; break;
    	        case KEY_BACKSPACE:  KeyCode=0x08; break;
    	        case KEY_SPACE:      KeyCode=0x20; break;       
    	        case KEY_NUMPAD_0: 
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='0';
    	            else KeyCode=KB_SPECIAL_INS;
    	            break;
    	        case KEY_NUMPAD_1:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='1';
    	            else KeyCode=KB_SPECIAL_END_KEY;
    	            break;
    	        case KEY_NUMPAD_2:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='2';
    	            else KeyCode=KB_SPECIAL_DOWN_ARROW_KEY;
    	            break;
    	        case KEY_NUMPAD_3:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='3';
    	            else KeyCode=KB_SPECIAL_PAGE_DOWN_KEY;
    	            break;
    	        case KEY_NUMPAD_4:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='4';
    	            else KeyCode=KB_SPECIAL_LEFT_ARROW_KEY;
    	            break;
    	        case KEY_NUMPAD_5:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='5';
    	            else KeyCode='5';
    	            break;
    	        case KEY_NUMPAD_6:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='6';
    	            else KeyCode=KB_SPECIAL_RIGHT_ARROW_KEY;
    	            break;
    	        case KEY_NUMPAD_7:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='7';
    	            else KeyCode=KB_SPECIAL_HOME_KEY ;
    	            break;
    	        case KEY_NUMPAD_8:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='8';
    	            else KeyCode=KB_SPECIAL_UP_ARROW_KEY;
    	            break;
    	        case KEY_NUMPAD_9:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='9';
    	            else KeyCode=KB_SPECIAL_PAGE_UP_KEY;
    	            break;
    	        case KEY_NUMPAD_DOT:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='.';
    	            else KeyCode=ASCII_DEL;
    	            break;
    	        case KEY_NUMPAD_STAR:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='*';
    	            else KeyCode='*';
    	            break;
    	        case KEY_NUMPAD_MINUS:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='-';
    	            else KeyCode='-';
    	            break;
    	        case KEY_NUMPAD_PLUS:
    	            if(pOsDriverKeyboard->NumLock==TRUE) KeyCode='+';
    	            else KeyCode='+';
    	            break;
                default:             
                    KeyCode=0x00; 
                    break; //null key
    	    }
    	    if(KeyStatus==KEY_RELEASE) KeyCode=0x00;
            if(KeyboardKeyBufferCheckIsr()!=BUFFER_FULL){
                if(KeyCode!=0x00) KeyboardKeyBufferPutIsr(KeyCode);
            }
    	    break;
    	case KeyboardExtendcodeState:
            KeyStatus=ScanCode&0x80;
            ScanCode=ScanCode&0x7f;
    	    switch(ScanCode){
    	        case KEY_PRTSC:     KeyCode=0x8c; break;
    	        case KEY_HOME:      KeyCode=0x9a; break;
    	        case KEY_END:       KeyCode=0x9c; break;
    	        case KEY_PAGEUP:    KeyCode=0x9d; break;
    	        case KEY_PAGEDOWN:  KeyCode=0x9b; break;
    	        case KEY_ARROWUP:   KeyCode=0x9f; break;
    	        case KEY_ARROWDOWN: KeyCode=0xa1; break;
    	        case KEY_ARROWLEFT: KeyCode=0xa0; break;
    	        case KEY_ARRORRIGHT:KeyCode=0xa2; break;
    	        case KEY_DEL:       KeyCode=0x7f; break;
    	        case KEY_INS:       KeyCode=0xa5; break;
    	        case KEY_ALT_RIGHT:
    	            if(KeyStatus==KEY_RELEASE) pOsDriverKeyboard->RightAlt=FALSE;
    	            else pOsDriverKeyboard->RightAlt=TRUE;
    	            KeyCode=0x97; 
    	            break;
    	        case KEY_CTRL_RIGHT:
    	            if(KeyStatus==KEY_RELEASE) pOsDriverKeyboard->RightCtrl=FALSE;
    	            else pOsDriverKeyboard->RightCtrl=TRUE;
    	            KeyCode=0x93; 
    	            break;
    	        case KEY_WINDOWS_MENU: KeyCode=0x98; break;
    	        case KEY_WINDOWS_START:KeyCode=0x94; break;
    	        case KEY_NUMPAD_DIVIDE:KeyCode='/'; break;
    	        case KEY_NUMPAD_ENTER: KeyCode=0x0d; break;
    	        default: KeyCode=0x00; break; //for skip key
    	    }
    	    if(KeyStatus==KEY_RELEASE) KeyCode=0x00;
            if(KeyboardKeyBufferCheckIsr()!=BUFFER_FULL)
                if(KeyCode!=0x00) KeyboardKeyBufferPutIsr(KeyCode);
    	    pOsDriverKeyboard->State=KeyboardGeneralcodeState;
    	    break;
    	case KeyboardExtraExtendcode1stState:
    	    pOsDriverKeyboard->ExtendKeyCode=(UINT16)ScanCode;
    	    pOsDriverKeyboard->ExtendKeyCode=pOsDriverKeyboard->ExtendKeyCode<<8;
    	    pOsDriverKeyboard->State=KeyboardExtraExtendcode2stState;
    	    break;
    	case KeyboardExtraExtendcode2stState:
    	    pOsDriverKeyboard->ExtendKeyCode=pOsDriverKeyboard->ExtendKeyCode+ScanCode;
    	    if(pOsDriverKeyboard->ExtendKeyCode==0x1d45) KeyCode=0x8e;
    	    else if(pOsDriverKeyboard->ExtendKeyCode==0x9dc5)  KeyCode=0x00; //release value of pause key
    	    else KeyCode=0x00;
            if(KeyboardKeyBufferCheckIsr()!=BUFFER_FULL)
                if(KeyCode!=0x00) KeyboardKeyBufferPutIsr(KeyCode);
    	    pOsDriverKeyboard->State=KeyboardGeneralcodeState;
    	    break;
    }
}

UINT8 KeyboardKeyBufferCheckIsr(VOID)
{
    if(pOsDriverKeyboard->Put!=pOsDriverKeyboard->Get){
        if(pOsDriverKeyboard->Put==(KEYBOARD_KEYBUFFER_SZIE-1)){
            if(pOsDriverKeyboard->Get==0) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
        else{
            if((pOsDriverKeyboard->Put+1)==pOsDriverKeyboard->Get) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
    }
    else return BUFFER_EMPTY;
}

UINT8 KeyboardKeyBufferCheck(VOID)
{
    if(pOsDriverKeyboard->Put!=pOsDriverKeyboard->Get){
        if(pOsDriverKeyboard->Put==(KEYBOARD_KEYBUFFER_SZIE-1)){
            if(pOsDriverKeyboard->Get==0) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
        else{
            if((pOsDriverKeyboard->Put+1)==pOsDriverKeyboard->Get) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
    }
    else return BUFFER_EMPTY;
}

VOID KeyboardKeyBufferPutIsr(UINT16 Data)
{
	if(pOsDriverKeyboard->BufferStatus==BUFFER_FAIL) return;
    if(KeyboardKeyBufferCheckIsr()==BUFFER_FULL) return;
    if(pOsDriverKeyboard->Put==(KEYBOARD_KEYBUFFER_SZIE-1)){
        pOsDriverKeyboard->pDataBuffer[pOsDriverKeyboard->Put]=Data;
        pOsDriverKeyboard->Put=0;
    }
    else{
        pOsDriverKeyboard->pDataBuffer[pOsDriverKeyboard->Put]=Data;
        pOsDriverKeyboard->Put++;
    }
}

UINT16 KeyboardKeyBufferGet(VOID)
{
    UINT16 Data;

	if(pOsDriverKeyboard->BufferStatus==BUFFER_FAIL) return 0;
    if(KeyboardKeyBufferCheck()==BUFFER_EMPTY) return 0;
    if(pOsDriverKeyboard->Get==(KEYBOARD_KEYBUFFER_SZIE-1)){
        Data=pOsDriverKeyboard->pDataBuffer[pOsDriverKeyboard->Get];
        pOsDriverKeyboard->Get=0;
    }
    else{
        Data=pOsDriverKeyboard->pDataBuffer[pOsDriverKeyboard->Get];
        pOsDriverKeyboard->Get++;
    }
    return Data;
}

/**************************
*Function:KeyboardBusyWait
*Description: wait keyboard(8042) ready
*
***************************/
VOID KeyboardBusyWait(VOID)
{
    //UINT8 i;
    
    pOsDriverKeyboard->MyTimer.Timer=10000;
    while(InByte(KB_STATUS_REG)&0x02){
        if(pOsDriverKeyboard->MyTimer.Timer==0) return;
    }
}

/**************************
*Function:KeyboardAckWait
*Description: wait keyboard(8042) ack signal
*
***************************/
VOID KeyboardAckWait(VOID)
{
	pOsDriverKeyboard->MyTimer.Timer=100;
    while(pOsDriverKeyboard->Ack==FALSE){
        if(pOsDriverKeyboard->MyTimer.Timer==0) return; 
    }
}

/**************************
*Function:KeyboardSetLed
*Description: wait keyboard(8042) ack signal
*
***************************/
VOID KeyboardSetLed(VOID)
{
	pOsDriverKeyboard->LedValue=0;
	if(pOsDriverKeyboard->NumLock==TRUE) pOsDriverKeyboard->LedValue|=KB_NUMBERLOCK_LED;
	if(pOsDriverKeyboard->CapsLock==TRUE)pOsDriverKeyboard->LedValue|=KB_CAPSLOCK_LED;
	if(pOsDriverKeyboard->ScrollLock==TRUE)pOsDriverKeyboard->LedValue|=KB_SCROLLLOCK_LED;
	pOsDriverKeyboard->Ack=FALSE;
	KeyboardBusyWait();
	OutByte(KB_DATA_REG,LED_CODE);
    KeyboardAckWait();
	pOsDriverKeyboard->Ack=FALSE;
	KeyboardBusyWait();
	OutByte(KB_DATA_REG,pOsDriverKeyboard->LedValue);
    KeyboardAckWait();
}

