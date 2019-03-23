#include <includes.h>

const UINT8 CalculatorTaskName[]="CALCULATOR";

const UINT8 CalculatorButtonName0[]="0";
const UINT8 CalculatorButtonName1[]="1";
const UINT8 CalculatorButtonName2[]="2";
const UINT8 CalculatorButtonName3[]="3";
const UINT8 CalculatorButtonName4[]="4";
const UINT8 CalculatorButtonName5[]="5";
const UINT8 CalculatorButtonName6[]="6";
const UINT8 CalculatorButtonName7[]="7";
const UINT8 CalculatorButtonName8[]="8";
const UINT8 CalculatorButtonName9[]="9";
const UINT8 CalculatorButtonNameAdd[]="+";
const UINT8 CalculatorButtonNameSub[]="-";
const UINT8 CalculatorButtonNameMul[]="*";
const UINT8 CalculatorButtonNameDiv[]="/";
const UINT8 CalculatorButtonNameDot[]=".";
const UINT8 CalculatorButtonNameEqual[]="=";
const UINT8 CalculatorButtonNameClear[]="C";

const UINT8 CalBtnWeight = 25;

VOID CalculatorInit(CALCULATOR_CONTORL *pCalculator){
    pCalculator->TaskState=CalculatorTaskIdleState; 
    pCalculator->OperationType=CALCULATOR_OPERATION_NONE;
    pCalculator->InputNumner=0;
    pCalculator->Result=0;
    pCalculator->NewArgument=TRUE;
    pCalculator->ArgumentIndex=0;
    pCalculator->ArgumentBuffer[0]=' ';
    pCalculator->ArgumentBuffer[1]=' ';
    pCalculator->ArgumentBuffer[2]=' ';
    pCalculator->ArgumentBuffer[3]=' ';
    pCalculator->ArgumentBuffer[4]=' ';
    pCalculator->ArgumentBuffer[5]=' ';
    pCalculator->ArgumentBuffer[6]=' ';
    pCalculator->ArgumentBuffer[7]=' ';
    pCalculator->ArgumentBuffer[8]=' ';
    pCalculator->ArgumentBuffer[9]=' ';
    pCalculator->ArgumentBuffer[10]='0';
    pCalculator->ArgumentBuffer[11]='.';
    pCalculator->ArgumentBuffer[12]=0;    

    pCalculator->StringBox.Type=WINDOW_STRINGBOX_GENERAL;
    pCalculator->StringBox.Dirty=FALSE;
    pCalculator->StringBox.Alignment=ALIGN_RIGHT;
    pCalculator->StringBox.pName=&pCalculator->ArgumentBuffer;
    pCalculator->StringBox.Gfx.BgColor=GFX_COLOR_WHITE;
    pCalculator->StringBox.Gfx.FgColor=GFX_COLOR_WHITE;
    pCalculator->StringBox.Gfx.FontColor=GFX_COLOR_BLACK;
    pCalculator->StringBox.Area.X=3;
    pCalculator->StringBox.Area.Y=5;
    pCalculator->StringBox.Area.W=12*STRING_SIZE+2; // 10 chars
    pCalculator->StringBox.Area.H=STRING_SIZE+2+5;
    pCalculator->WdStringBox.Type=WINDOW_DEVICE_STRINGBOX;
    pCalculator->WdStringBox.DeviceNumberLeft=CALCULATOR_WDN_STRINGBOX;
    pCalculator->WdStringBox.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdStringBox.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdStringBox.pDevice=(UINT32 *)(&pCalculator->StringBox);
    
    pCalculator->NumberButton0.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton0.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton0.Active=TRUE;
    pCalculator->NumberButton0.Dirty=TRUE;
    pCalculator->NumberButton0.Outline=TRUE;
    pCalculator->NumberButton0.pName=CalculatorButtonName0;
    pCalculator->NumberButton0.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton0.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton0.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton0.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton0.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton0.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton0.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton0.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton0.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton0.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton0.Area.X=5;
    pCalculator->NumberButton0.Area.Y=120;
    pCalculator->NumberButton0.Area.W=CalBtnWeight;
    pCalculator->NumberButton0.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton0.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton0.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON0;
    pCalculator->WdNumberButton0.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton0.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton0.pDevice=(UINT32 *)(&pCalculator->NumberButton0);
    
    pCalculator->NumberButton1.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton1.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton1.Active=TRUE;
    pCalculator->NumberButton1.Dirty=TRUE;
    pCalculator->NumberButton1.Outline=TRUE;
    pCalculator->NumberButton1.pName=CalculatorButtonName1;
    pCalculator->NumberButton1.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton1.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton1.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton1.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton1.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton1.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton1.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton1.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton1.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton1.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton1.Area.X=5;
    pCalculator->NumberButton1.Area.Y=90;
    pCalculator->NumberButton1.Area.W=CalBtnWeight;
    pCalculator->NumberButton1.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton1.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton1.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON1;
    pCalculator->WdNumberButton1.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton1.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton1.pDevice=(UINT32 *)(&pCalculator->NumberButton1);

    pCalculator->NumberButton2.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton2.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton2.Active=TRUE;
    pCalculator->NumberButton2.Dirty=TRUE;
    pCalculator->NumberButton2.Outline=TRUE;
    pCalculator->NumberButton2.pName=CalculatorButtonName2;
    pCalculator->NumberButton2.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton2.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton2.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton2.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton2.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton2.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton2.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton2.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton2.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton2.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton2.Area.X=35;
    pCalculator->NumberButton2.Area.Y=90;
    pCalculator->NumberButton2.Area.W=CalBtnWeight;
    pCalculator->NumberButton2.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton2.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton2.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON2;
    pCalculator->WdNumberButton2.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton2.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton2.pDevice=(UINT32 *)(&pCalculator->NumberButton2);
    
    pCalculator->NumberButton3.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton3.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton3.Active=TRUE;
    pCalculator->NumberButton3.Dirty=TRUE;
    pCalculator->NumberButton3.Outline=TRUE;
    pCalculator->NumberButton3.pName=CalculatorButtonName3;
    pCalculator->NumberButton3.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton3.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton3.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton3.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton3.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton3.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton3.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton3.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton3.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton3.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton3.Area.X=65;
    pCalculator->NumberButton3.Area.Y=90;
    pCalculator->NumberButton3.Area.W=CalBtnWeight;
    pCalculator->NumberButton3.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton3.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton3.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON3;
    pCalculator->WdNumberButton3.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton3.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton3.pDevice=(UINT32 *)(&pCalculator->NumberButton3);
    
    pCalculator->NumberButton4.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton4.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton4.Active=TRUE;
    pCalculator->NumberButton4.Dirty=TRUE;
    pCalculator->NumberButton4.Outline=TRUE;
    pCalculator->NumberButton4.pName=CalculatorButtonName4;
    pCalculator->NumberButton4.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton4.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton4.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton4.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton4.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton4.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton4.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton4.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton4.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton4.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton4.Area.X=5;
    pCalculator->NumberButton4.Area.Y=60;
    pCalculator->NumberButton4.Area.W=CalBtnWeight;
    pCalculator->NumberButton4.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton4.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton4.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON4;
    pCalculator->WdNumberButton4.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton4.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton4.pDevice=(UINT32 *)(&pCalculator->NumberButton4);
    
    pCalculator->NumberButton5.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton5.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton5.Active=TRUE;
    pCalculator->NumberButton5.Dirty=TRUE;
    pCalculator->NumberButton5.Outline=TRUE;
    pCalculator->NumberButton5.pName=CalculatorButtonName5;
    pCalculator->NumberButton5.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton5.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton5.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton5.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton5.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton5.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton5.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton5.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton5.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton5.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton5.Area.X=35;
    pCalculator->NumberButton5.Area.Y=60;
    pCalculator->NumberButton5.Area.W=CalBtnWeight;
    pCalculator->NumberButton5.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton5.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton5.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON5;
    pCalculator->WdNumberButton5.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton5.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton5.pDevice=(UINT32 *)(&pCalculator->NumberButton5);
    
    pCalculator->NumberButton6.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton6.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton6.Active=TRUE;
    pCalculator->NumberButton6.Dirty=TRUE;
    pCalculator->NumberButton6.Outline=TRUE;
    pCalculator->NumberButton6.pName=CalculatorButtonName6;
    pCalculator->NumberButton6.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton6.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton6.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton6.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton6.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton6.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton6.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton6.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton6.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton6.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton6.Area.X=65;
    pCalculator->NumberButton6.Area.Y=60;
    pCalculator->NumberButton6.Area.W=CalBtnWeight;
    pCalculator->NumberButton6.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton6.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton6.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON6;
    pCalculator->WdNumberButton6.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton6.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton6.pDevice=(UINT32 *)(&pCalculator->NumberButton6);
    
    pCalculator->NumberButton7.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton7.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton7.Active=TRUE;
    pCalculator->NumberButton7.Dirty=TRUE;
    pCalculator->NumberButton7.Outline=TRUE;
    pCalculator->NumberButton7.pName=CalculatorButtonName7;
    pCalculator->NumberButton7.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton7.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton7.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton7.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton7.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton7.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton7.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton7.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton7.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton7.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton7.Area.X=5;
    pCalculator->NumberButton7.Area.Y=30;
    pCalculator->NumberButton7.Area.W=CalBtnWeight;
    pCalculator->NumberButton7.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton7.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton7.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON7;
    pCalculator->WdNumberButton7.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton7.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton7.pDevice=(UINT32 *)(&pCalculator->NumberButton7);
    
    pCalculator->NumberButton8.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton8.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton8.Active=TRUE;
    pCalculator->NumberButton8.Dirty=TRUE;
    pCalculator->NumberButton8.Outline=TRUE;
    pCalculator->NumberButton8.pName=CalculatorButtonName8;
    pCalculator->NumberButton8.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton8.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton8.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton8.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton8.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton8.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton8.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton8.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton8.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton8.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton8.Area.X=35;
    pCalculator->NumberButton8.Area.Y=30;
    pCalculator->NumberButton8.Area.W=CalBtnWeight;
    pCalculator->NumberButton8.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton8.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton8.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON8;
    pCalculator->WdNumberButton8.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton8.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton8.pDevice=(UINT32 *)(&pCalculator->NumberButton8);
    
    pCalculator->NumberButton9.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->NumberButton9.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->NumberButton9.Active=TRUE;
    pCalculator->NumberButton9.Dirty=TRUE;
    pCalculator->NumberButton9.Outline=TRUE;
    pCalculator->NumberButton9.pName=CalculatorButtonName9;
    pCalculator->NumberButton9.pBitmap=(UINT8 *)NULL;
    pCalculator->NumberButton9.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton9.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->NumberButton9.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton9.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton9.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->NumberButton9.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->NumberButton9.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton9.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->NumberButton9.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->NumberButton9.Area.X=65;
    pCalculator->NumberButton9.Area.Y=30;
    pCalculator->NumberButton9.Area.W=CalBtnWeight;
    pCalculator->NumberButton9.Area.H=CalBtnWeight;
    pCalculator->WdNumberButton9.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdNumberButton9.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTON9;
    pCalculator->WdNumberButton9.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton9.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdNumberButton9.pDevice=(UINT32 *)(&pCalculator->NumberButton9);
    
    pCalculator->AddButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->AddButton.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->AddButton.Active=TRUE;
    pCalculator->AddButton.Dirty=TRUE;
    pCalculator->AddButton.Outline=TRUE;
    pCalculator->AddButton.pName=CalculatorButtonNameAdd;
    pCalculator->AddButton.pBitmap=(UINT8 *)NULL;
    pCalculator->AddButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->AddButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->AddButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->AddButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->AddButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->AddButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->AddButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->AddButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->AddButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->AddButton.Area.X=95;
    pCalculator->AddButton.Area.Y=30;
    pCalculator->AddButton.Area.W=CalBtnWeight;
    pCalculator->AddButton.Area.H=CalBtnWeight;
    pCalculator->WdAddButton.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdAddButton.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTONADD;
    pCalculator->WdAddButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdAddButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdAddButton.pDevice=(UINT32 *)(&pCalculator->AddButton);
    
    pCalculator->SubButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->SubButton.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->SubButton.Active=TRUE;
    pCalculator->SubButton.Dirty=TRUE;
    pCalculator->SubButton.Outline=TRUE;
    pCalculator->SubButton.pName=CalculatorButtonNameSub;
    pCalculator->SubButton.pBitmap=(UINT8 *)NULL;
    pCalculator->SubButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->SubButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->SubButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->SubButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->SubButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->SubButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->SubButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->SubButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->SubButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->SubButton.Area.X=95;
    pCalculator->SubButton.Area.Y=60;
    pCalculator->SubButton.Area.W=CalBtnWeight;
    pCalculator->SubButton.Area.H=CalBtnWeight;
    pCalculator->WdSubButton.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdSubButton.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTONSUB;
    pCalculator->WdSubButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdSubButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdSubButton.pDevice=(UINT32 *)(&pCalculator->SubButton);
    
    pCalculator->MulButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->MulButton.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->MulButton.Active=TRUE;
    pCalculator->MulButton.Dirty=TRUE;
    pCalculator->MulButton.Outline=TRUE;
    pCalculator->MulButton.pName=CalculatorButtonNameMul;
    pCalculator->MulButton.pBitmap=(UINT8 *)NULL;
    pCalculator->MulButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->MulButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->MulButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->MulButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->MulButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->MulButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->MulButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->MulButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->MulButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->MulButton.Area.X=95;
    pCalculator->MulButton.Area.Y=90;
    pCalculator->MulButton.Area.W=CalBtnWeight;
    pCalculator->MulButton.Area.H=CalBtnWeight;
    pCalculator->WdMulButton.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdMulButton.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTONMUL;
    pCalculator->WdMulButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdMulButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdMulButton.pDevice=(UINT32 *)(&pCalculator->MulButton);
        
    pCalculator->DivButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->DivButton.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->DivButton.Active=TRUE;
    pCalculator->DivButton.Dirty=TRUE;
    pCalculator->DivButton.Outline=TRUE;
    pCalculator->DivButton.pName=CalculatorButtonNameDiv;
    pCalculator->DivButton.pBitmap=(UINT8 *)NULL;
    pCalculator->DivButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->DivButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->DivButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->DivButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->DivButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->DivButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->DivButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->DivButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->DivButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->DivButton.Area.X=95;
    pCalculator->DivButton.Area.Y=120;
    pCalculator->DivButton.Area.W=CalBtnWeight;
    pCalculator->DivButton.Area.H=CalBtnWeight;
    pCalculator->WdDivButton.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdDivButton.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTONDIV;
    pCalculator->WdDivButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdDivButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdDivButton.pDevice=(UINT32 *)(&pCalculator->DivButton);
    
    pCalculator->DotButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->DotButton.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->DotButton.Active=TRUE;
    pCalculator->DotButton.Dirty=TRUE;
    pCalculator->DotButton.Outline=TRUE;
    pCalculator->DotButton.pName=CalculatorButtonNameDot;
    pCalculator->DotButton.pBitmap=(UINT8 *)NULL;
    pCalculator->DotButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->DotButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->DotButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->DotButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->DotButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->DotButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->DotButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->DotButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->DotButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->DotButton.Area.X=65;
    pCalculator->DotButton.Area.Y=120;
    pCalculator->DotButton.Area.W=CalBtnWeight;
    pCalculator->DotButton.Area.H=CalBtnWeight;
    pCalculator->WdDotButton.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdDotButton.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTONDOT;
    pCalculator->WdDotButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdDotButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdDotButton.pDevice=(UINT32 *)(&pCalculator->DotButton);
    
    pCalculator->EqualButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->EqualButton.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->EqualButton.Active=TRUE;
    pCalculator->EqualButton.Dirty=TRUE;
    pCalculator->EqualButton.Outline=TRUE;
    pCalculator->EqualButton.pName=CalculatorButtonNameEqual;
    pCalculator->EqualButton.pBitmap=(UINT8 *)NULL;
    pCalculator->EqualButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->EqualButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->EqualButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->EqualButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->EqualButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->EqualButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->EqualButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->EqualButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->EqualButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->EqualButton.Area.X=125;
    pCalculator->EqualButton.Area.Y=30;
    pCalculator->EqualButton.Area.W=CalBtnWeight;
    pCalculator->EqualButton.Area.H=CalBtnWeight;
    pCalculator->WdEqualButton.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdEqualButton.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTONEQUAL;
    pCalculator->WdEqualButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdEqualButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdEqualButton.pDevice=(UINT32 *)(&pCalculator->EqualButton);
    
    pCalculator->ClearButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pCalculator->ClearButton.Status=WINDOW_BUTTON_RELEASE;
    pCalculator->ClearButton.Active=TRUE;
    pCalculator->ClearButton.Dirty=TRUE;
    pCalculator->ClearButton.Outline=TRUE;
    pCalculator->ClearButton.pName=CalculatorButtonNameClear;
    pCalculator->ClearButton.pBitmap=(UINT8 *)NULL;
    pCalculator->ClearButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pCalculator->ClearButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pCalculator->ClearButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->ClearButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pCalculator->ClearButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pCalculator->ClearButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->ClearButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->ClearButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pCalculator->ClearButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pCalculator->ClearButton.Area.X=125;
    pCalculator->ClearButton.Area.Y=60;
    pCalculator->ClearButton.Area.W=CalBtnWeight;
    pCalculator->ClearButton.Area.H=CalBtnWeight;
    pCalculator->WdClearButton.Type=WINDOW_DEVICE_BUTTON;
    pCalculator->WdClearButton.DeviceNumberLeft=CALCULATOR_WDN_NUMBERBUTTONCLEAR;
    pCalculator->WdClearButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pCalculator->WdClearButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pCalculator->WdClearButton.pDevice=(UINT32 *)(&pCalculator->ClearButton);
    
    pCalculator->UserTable.Type=WINDOW_TABLE_GENERAL;
    pCalculator->UserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    pCalculator->UserTable.Gfx.BgColor=GFX_COLOR_LIGHTBLUE;
    pCalculator->UserTable.Gfx.FgColor=GFX_COLOR_LIGHTBLUE;
    pCalculator->UserTable.Gfx.FontColor=GFX_COLOR_WHITE;
    pCalculator->UserTable.Area.X=0;
    pCalculator->UserTable.Area.Y=0;
    pCalculator->UserTable.Area.W=170;
    pCalculator->UserTable.Area.H=155;
    // add device to user table
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdStringBox);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton0);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton1);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton2);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton3);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton4);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton5);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton6);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton7);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton8);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdNumberButton9);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdAddButton);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdSubButton);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdDivButton);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdMulButton);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdDotButton);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdEqualButton);
    DeskTableWindowDeviceAdd(&pCalculator->UserTable,&pCalculator->WdClearButton);
    
    //window initial
    WindowVariableInit(&pCalculator->Window,WINDOW_TYPE_APPLICATION);
    pCalculator->Window.pTitle=(UINT8 *)CalculatorTaskName;
    DeskTableUserTableAdd(&pCalculator->Window,&pCalculator->UserTable);
    WindowAreaInitial(&pCalculator->Window);
    WindowOutlineCalculate(&pCalculator->Window);
    WindowOutlineTableInitial(&pCalculator->Window);
    WindowHeaderCalculate(&pCalculator->Window);
    WindowHeaderTableInitial(&pCalculator->Window);
    
    // add window to desk
    DeskWindowWindowPut((WINDOW *)&pCalculator->Window);
    ((OS_TCB *)OsTaskCurrent)->Window=(UINT32)&pCalculator->Window;
    pCalculator->TaskState=CalculatorTaskRunState; 
}

VOID CalculatorSvc(CALCULATOR_CONTORL *pCalculator){
    if(WindowEventBufferCheck(&pCalculator->Window)!=BUFFER_EMPTY){
        pCalculator->WindowEvent=WindowEventBufferGet(&pCalculator->Window);
        if(pCalculator->WindowEvent!=0){
            CaptionStringPrint(&DeskDebugCtrl.Caption,"\nevent ");
            CaptionUINT8Print(&DeskDebugCtrl.Caption,(UINT8)pCalculator->WindowEvent);
        }
        CalculatorEventHandler(pCalculator);
    }
    if(WindowKeyBufferCheck(&pCalculator->Window)!=BUFFER_EMPTY){
        pCalculator->WindowKey=WindowKeyBufferGet(&pCalculator->Window);
        if(pCalculator->WindowKey!=0){
            CaptionStringPrint(&DeskDebugCtrl.Caption,"\nkey ");
            CaptionUINT8Print(&DeskDebugCtrl.Caption,(UINT8)pCalculator->WindowKey);
        }
        CalculatorKeyHandler(pCalculator);
    }
}

VOID CalculatorEventHandler(CALCULATOR_CONTORL *pCalculator){
    CaptionStringPrint(&DeskDebugCtrl.Caption,"\nevent");
    switch((UINT8)pCalculator->WindowEvent){
        case CALCULATOR_WDN_NUMBERBUTTON0:
            CalculatorArgumentAdd(pCalculator,'0');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON1:
            CalculatorArgumentAdd(pCalculator,'1');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON2:
            CalculatorArgumentAdd(pCalculator,'2');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON3:
            CalculatorArgumentAdd(pCalculator,'3');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON4:
            CalculatorArgumentAdd(pCalculator,'4');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON5:
            CalculatorArgumentAdd(pCalculator,'5');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON6:
            CalculatorArgumentAdd(pCalculator,'6');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON7:
            CalculatorArgumentAdd(pCalculator,'7');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON8:
            CalculatorArgumentAdd(pCalculator,'8');
            break;
        case CALCULATOR_WDN_NUMBERBUTTON9:
            CalculatorArgumentAdd(pCalculator,'9');
            break;
        case CALCULATOR_WDN_NUMBERBUTTONDOT:
            CalculatorArgumentAdd(pCalculator,'.');
            break;
        case CALCULATOR_WDN_NUMBERBUTTONADD:
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_ADD;
            break;
        case CALCULATOR_WDN_NUMBERBUTTONSUB:
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_SUB;
            break;
        case CALCULATOR_WDN_NUMBERBUTTONDIV:
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_DIV;
            break;
        case CALCULATOR_WDN_NUMBERBUTTONMUL:
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_MUL;
            break;
        case CALCULATOR_WDN_NUMBERBUTTONEQUAL:
            if(pCalculator->OperationType==CALCULATOR_OPERATION_ADD)
                pCalculator->Result=pCalculator->InputNumner+CalculatorNumberGet(pCalculator);
            else if(pCalculator->OperationType==CALCULATOR_OPERATION_SUB)
                pCalculator->Result=pCalculator->InputNumner-CalculatorNumberGet(pCalculator);
            else if(pCalculator->OperationType==CALCULATOR_OPERATION_DIV)
                pCalculator->Result=pCalculator->InputNumner/CalculatorNumberGet(pCalculator);
            else if(pCalculator->OperationType==CALCULATOR_OPERATION_MUL)
                pCalculator->Result=pCalculator->InputNumner*CalculatorNumberGet(pCalculator);
            else pCalculator->Result=CalculatorNumberGet(pCalculator);
            CalculatorResult2StringConvert(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_NONE;
            break;
        case CALCULATOR_WDN_NUMBERBUTTONCLEAR:
            CalculatorArgumentReset(pCalculator);
            pCalculator->OperationType=CALCULATOR_OPERATION_NONE;
            pCalculator->InputNumner=0;
            pCalculator->Result=0;
            break;
        default:
            CaptionStringPrint(&DeskDebugCtrl.Caption,"unknow");
            break;
    }
    CalculatorUpdate(pCalculator);
}

VOID CalculatorKeyHandler(CALCULATOR_CONTORL *pCalculator){
    switch(pCalculator->WindowKey){
        case '0':
            CalculatorArgumentAdd(pCalculator,'0');
            break;
        case '1':
            CalculatorArgumentAdd(pCalculator,'1');
            break;
        case '2':
            CalculatorArgumentAdd(pCalculator,'2');
            break;
        case '3':
            CalculatorArgumentAdd(pCalculator,'3');
            break;
        case '4':
            CalculatorArgumentAdd(pCalculator,'4');
            break;
        case '5':
            CalculatorArgumentAdd(pCalculator,'5');
            break;
        case '6':
            CalculatorArgumentAdd(pCalculator,'6');
            break;
        case '7':
            CalculatorArgumentAdd(pCalculator,'7');
            break;
        case '8':
            CalculatorArgumentAdd(pCalculator,'8');
            break;
        case '9':
            CalculatorArgumentAdd(pCalculator,'9');
            break;
        case '.':
            CalculatorArgumentAdd(pCalculator,'.');
            break;
        case '+':
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_ADD;
            break;
        case '-':
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_SUB;
            break;
        case '*':
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_MUL;
            break;
        case '/':
            pCalculator->InputNumner=CalculatorNumberGet(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_DIV;
            break;
        case '=':
        case 0x0d: //enter
            if(pCalculator->OperationType==CALCULATOR_OPERATION_ADD)
                pCalculator->Result=pCalculator->InputNumner+CalculatorNumberGet(pCalculator);
            else if(pCalculator->OperationType==CALCULATOR_OPERATION_SUB)
                pCalculator->Result=pCalculator->InputNumner-CalculatorNumberGet(pCalculator);
            else if(pCalculator->OperationType==CALCULATOR_OPERATION_DIV)
                pCalculator->Result=pCalculator->InputNumner/CalculatorNumberGet(pCalculator);
            else if(pCalculator->OperationType==CALCULATOR_OPERATION_MUL)
                pCalculator->Result=pCalculator->InputNumner*CalculatorNumberGet(pCalculator);
            else pCalculator->Result=CalculatorNumberGet(pCalculator);
            CalculatorResult2StringConvert(pCalculator);
            pCalculator->NewArgument=TRUE;
            pCalculator->OperationType=CALCULATOR_OPERATION_NONE;
            break;
        default:
            break;
    }
    CalculatorUpdate(pCalculator);
}

VOID CalculatorArgumentReset(CALCULATOR_CONTORL *pCalculator){
    pCalculator->ArgumentIndex=0;
    pCalculator->ArgumentBuffer[0]=' ';
    pCalculator->ArgumentBuffer[1]=' ';
    pCalculator->ArgumentBuffer[2]=' ';
    pCalculator->ArgumentBuffer[3]=' ';
    pCalculator->ArgumentBuffer[4]=' ';
    pCalculator->ArgumentBuffer[5]=' ';
    pCalculator->ArgumentBuffer[6]=' ';
    pCalculator->ArgumentBuffer[7]=' ';
    pCalculator->ArgumentBuffer[8]=' ';
    pCalculator->ArgumentBuffer[9]=' ';
    pCalculator->ArgumentBuffer[10]='0';
    pCalculator->ArgumentBuffer[11]='.';
    pCalculator->ArgumentBuffer[12]=0;    
}

VOID CalculatorArgumentAdd(CALCULATOR_CONTORL *pCalculator,UINT8 Data){
    if(pCalculator->NewArgument==TRUE){
        pCalculator->NewArgument=FALSE;
        CalculatorArgumentReset(pCalculator);
    }
    if(pCalculator->ArgumentIndex>=10) return;
    if(pCalculator->ArgumentIndex==0){
        if(Data!='0'){
            pCalculator->ArgumentBuffer[10]=Data;
            pCalculator->ArgumentIndex++;
        }
    }
    else{
        pCalculator->ArgumentBuffer[0]=pCalculator->ArgumentBuffer[1];
        pCalculator->ArgumentBuffer[1]=pCalculator->ArgumentBuffer[2];
        pCalculator->ArgumentBuffer[2]=pCalculator->ArgumentBuffer[3];
        pCalculator->ArgumentBuffer[3]=pCalculator->ArgumentBuffer[4];
        pCalculator->ArgumentBuffer[4]=pCalculator->ArgumentBuffer[5];
        pCalculator->ArgumentBuffer[5]=pCalculator->ArgumentBuffer[6];
        pCalculator->ArgumentBuffer[6]=pCalculator->ArgumentBuffer[7];
        pCalculator->ArgumentBuffer[7]=pCalculator->ArgumentBuffer[8];
        pCalculator->ArgumentBuffer[8]=pCalculator->ArgumentBuffer[9];
        pCalculator->ArgumentBuffer[9]=pCalculator->ArgumentBuffer[10];
        pCalculator->ArgumentBuffer[10]=Data;
        pCalculator->ArgumentBuffer[11]='.';
        pCalculator->ArgumentBuffer[12]=0;    
        pCalculator->ArgumentIndex++;
    }
}

UINT32 CalculatorNumberGet(CALCULATOR_CONTORL *pCalculator){
    UINT8 i,j;
    UINT32 InputNumber,TensOrderNumber;
    
    j=0;
    InputNumber=0;
    TensOrderNumber=1;
    while(j<11){
	    i=pCalculator->ArgumentBuffer[10-j];
	    if(i==' ') return InputNumber;
	    else{
	        i=CalculatorAscii2HexGet(i);
	        InputNumber+=((UINT32)i)*TensOrderNumber;
	    }
	    j++;
	    TensOrderNumber=TensOrderNumber*10;
    }
}

VOID CalculatorOperationDo(CALCULATOR_CONTORL *pCalculator){
    
}

VOID CalculatorUpdate(CALCULATOR_CONTORL *pCalculator){
    pCalculator->StringBox.Dirty=TRUE;
}

UINT8 CalculatorAscii2HexGet(UINT8 CharCode){
    if((CharCode>='0')&&(CharCode<='9')) return (CharCode-'0');
    else if((CharCode>='A')&&(CharCode<='F'))  return (CharCode-'A');
    else if((CharCode>='a')&&(CharCode<='f'))  return (CharCode-'a');
    else return 0;
}

VOID CalculatorResult2StringConvert(CALCULATOR_CONTORL *pCalculator){
    UINT32 i,j;
    UINT8 k;
    
    pCalculator->ArgumentBuffer[0]=' ';
    pCalculator->ArgumentBuffer[1]=' ';
    pCalculator->ArgumentBuffer[2]=' ';
    pCalculator->ArgumentBuffer[3]=' ';
    pCalculator->ArgumentBuffer[4]=' ';
    pCalculator->ArgumentBuffer[5]=' ';
    pCalculator->ArgumentBuffer[6]=' ';
    pCalculator->ArgumentBuffer[7]=' ';
    pCalculator->ArgumentBuffer[8]=' ';
    pCalculator->ArgumentBuffer[9]=' ';
    pCalculator->ArgumentBuffer[10]='0';
    pCalculator->ArgumentBuffer[11]='.';
    pCalculator->ArgumentBuffer[12]=0;

    i=pCalculator->Result;
    
    if(i==0) return;
    
    k=0;
    while(k<11){
        j=i%10;
        if(j<10) pCalculator->ArgumentBuffer[10-k]=j+'0';
        i=i-j;
        if(i==0) return;
    	i=i/10;
        k++;
    }
}
