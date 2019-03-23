;BIN: PEGA_Debug_util_x64.asm is created by BIN.
;BIN: This file contains funcrions used by PEGA DXE Debugger
;BIN: for X64 support.
;include token.equ

EXTERN IntDummyCallback:NEAR
EXTERN ExtHandler_Debugger:NEAR

.code

align 16
;VOID IntDummyHandler();
IntDummyHandler PROC PUBLIC
	push rax
	push rcx
	push rdx
	push rbx
	push rsp
	push rbp
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	call IntDummyCallback
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rbp
;	pop rsp
	pop rax				;rsp - not used
	pop rbx
	pop rdx
	pop rcx
	pop rax
	iretq
IntDummyHandler ENDP

align 16
Exp_00_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 00h		;rax := vector 0 (Divide Error Exception, no error code)
	jmp	Pre_ExpHandler
Exp_00_Handler ENDP

align 16
Exp_01_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 01h		;rax := vector 1 (Debug Exception, no error code)
	jmp	Pre_ExpHandler
Exp_01_Handler ENDP

align 16
Exp_02_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 02h		;rax := vector 2 (NMI Interrupt, no error code)
	jmp	Pre_ExpHandler
Exp_02_Handler ENDP

align 16
Exp_03_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 03h		;rax := vector 3 (Breakpoint Exception, no error code)
	jmp	Pre_ExpHandler
Exp_03_Handler ENDP

align 16
Exp_04_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 04h		;rax := vector 4 (Overflow Exception, no error code)
	jmp	Pre_ExpHandler
Exp_04_Handler ENDP

align 16
Exp_05_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 05h		;rax := vector 5 (BOUND Range Exceeded Exception, no error code)
	jmp	Pre_ExpHandler
Exp_05_Handler ENDP

align 16
Exp_06_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 06h		;rax := vector 6 (Invalid Opcode Exception, no error code)
	jmp	Pre_ExpHandler
Exp_06_Handler ENDP

align 16
Exp_07_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 07h		;rax := vector 7 (Device Not Available Exception, no error code)
	jmp	Pre_ExpHandler
Exp_07_Handler ENDP

align 16
Exp_08_Handler PROC PUBLIC
	xchg	qword ptr [rsp], rax	;error_code, rip, cs, rflag
	mov	rax, 08h		;rax := vector 8 (Double Fault Exception, has error code = 0)
	jmp	Pre_ExpHandler
Exp_08_Handler ENDP

align 16
Exp_09_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 09h		;rax := vector 9 (Double Fault Exception, no error code)
	jmp	Pre_ExpHandler
Exp_09_Handler ENDP

align 16
Exp_0A_Handler PROC PUBLIC
	xchg	qword ptr [rsp], rax	;error_code, rip, cs, rflag
	mov	rax, 0Ah		;rax := vector 10 (Invalid TSS Exception, has error code - segment selector index)
	jmp	Pre_ExpHandler
Exp_0A_Handler ENDP

align 16
Exp_0B_Handler PROC PUBLIC
	xchg	qword ptr [rsp], rax	;error_code, rip, cs, rflag
	mov	rax, 0Bh		;rax := vector 11 (Segment Not Present, has error code - segment selector index)
	jmp	Pre_ExpHandler
Exp_0B_Handler ENDP

align 16
Exp_0C_Handler PROC PUBLIC
	xchg	qword ptr [rsp], rax	;error_code, rip, cs, rflag
	mov	rax, 0Ch		;rax := vector 12 (Stack Fault Exception, has error code - segment selector index)
	jmp	Pre_ExpHandler
Exp_0C_Handler ENDP

align 16
Exp_0D_Handler PROC PUBLIC
	xchg	qword ptr [rsp], rax	;error_code, rip, cs, rflag
	mov	rax, 0Dh		;rax := vector 13 (Stack Fault Exception, has error code - segment selector index or IDT vector number)
	jmp	Pre_ExpHandler
Exp_0D_Handler ENDP

align 16
Exp_0E_Handler PROC PUBLIC
	xchg	qword ptr [rsp], rax	;error_code, rip, cs, rflag
	mov	rax, 0Eh		;rax := vector 14 (Page-Fault Exception, has error code, page-fault information)
	jmp	Pre_ExpHandler
Exp_0E_Handler ENDP

align 16
Exp_0F_Handler PROC PUBLIC
	push	rax			;rax, rip, cs, rflag
	mov	rax, 0Fh		;rax := vector 15 (no such exception on IA32-SPEC.)
	jmp	Pre_ExpHandler
Exp_0F_Handler ENDP

align 16
Pre_ExpHandler PROC
;	push rax			;rax contains vector (ex. 00h, 0Dh, 0Eh, ...)
	push rcx
	push rdx
	push rbx
	mov rbx, rsp
	add  rbx, 8 * 7			;rbx, rdx, rcx, rax, rip, cs, rflag
	mov  rbx, [rbx]			;rbx := rsp
	push rbx
	push rbp
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	mov rdx, rax			;rdx (Arg1 in RDX, vector)
	mov rbx, rsp
	mov rax, dr7
	push rax			;dr7
	mov rax, dr6
	push rax			;dr6
;	mov rax, dr5
	push rax			;dr5
;	mov rax, dr4
	push rax			;dr4
	mov rax, dr3
	push rax			;dr3
	mov rax, dr2
	push rax			;dr2
	mov rax, dr1
	push rax			;dr1
	mov rax, dr0
	push rax			;dr0
	mov rax, cr8
	push rax			;cr8
	mov rax, cr4
	push rax			;cr4
	mov rax, cr3
	push rax			;cr3
	mov rax, cr2
	push rax			;cr2
;	mov rax, cr1
	push rax			;cr1
	mov rax, cr0
	push rax			;cr0
	mov rax, 0
	mov ax, gs
	push rax			;gs
	mov ax, fs
	push rax			;fs
	mov ax, es
	push rax			;es
	mov ax, ss
	push rax			;ss
	mov ax, ds
	push rax			;ds
	mov rax, [rbx+17*8]
	push rax			;cs
	mov rax, [rbx+18*8]
	push rax			;rflags
	mov rax, [rbx+16*8]
	push rax			;rip
	mov rax, rsp
	push rbx			;Save rbx, in case debugger destroy it

	mov rcx, rax			;PegaRegisterSet *Regs (Arg0 in RCX)
	push rdx
	push rcx
	call ExtHandler_Debugger
	pop  rcx
	pop rdx
	mov rax, rcx			;PegaRegisterSet *Regs (Arg0 in RCX)

	pop rbx				;Restore rbx
	pop rax				;rip
	mov [rbx+16*8], rax
	pop rax				;rflags
	mov [rbx+18*8], rax
	pop rax				;cs
	mov [rbx+17*8], rax
	pop rax				;ds
	mov ds, ax
	pop rax				;ss
	mov ss, ax
	pop rax				;es
	mov es, ax
	pop rax				;fs
	mov fs, ax
	pop rax				;gs
	mov gs, ax
	pop rax				;cr0
	mov cr0, rax
	pop rax				;cr1
;	mov cr1, rax
	pop rax				;cr2
;	mov cr2, rax
	pop rax				;cr3
;	mov cr3, rax
	pop rax				;cr4
	mov cr4, rax
	pop rax				;cr8
	mov cr8, rax
	pop rax				;dr0
	mov dr0, rax
	pop rax				;dr1
	mov dr1, rax
	pop rax				;dr2
	mov dr2, rax
	pop rax				;dr3
	mov dr3, rax
	pop rax				;dr4
;	mov dr4, rax
	pop rax				;dr5
;	mov dr5, rax
	pop rax				;dr6
	mov dr6, rax
	pop rax				;dr7
	mov dr7, rax
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rbp
	pop rax				;rsp - not used
;	mov rsp, rax
	pop rbx
	pop rdx
	pop rcx
	pop rax
	iretq
Pre_ExpHandler ENDP

PUBLIC RealModeIntHandlerStart
PUBLIC RealModeIntHandlerEnd
PUBLIC RealModeInt1HandlerStart
PUBLIC RealModeInt3HandlerStart
PUBLIC RealModeInt1DebuggerEntry
PUBLIC RealModeInt3DebuggerEntry
PUBLIC RealModeIntStack
PUBLIC RealModeSaveCR3
PUBLIC DBGR_GDT_PTR
PUBLIC PM16_PATCH1
PUBLIC PM16_PATCH2
PUBLIC PM32_PATCH1
PUBLIC PM32_PATCH2
PUBLIC PM32_PATCH3
PUBLIC PM64_PATCH1
PUBLIC PM64_PATCH2
PUBLIC PM64_PATCH3
PUBLIC PM64_PATCH4
PUBLIC PM64_PATCH5

RealModeIntHandlerStart DQ RealModeIntHandlerStartAddr
RealModeIntHandlerEnd DQ RealModeIntHandlerEndAddr
RealModeInt1HandlerStart DQ RealModeInt1Handler
RealModeInt3HandlerStart DQ RealModeInt3Handler
PM16_PATCH1 DQ PM16_PATCH1_ADDR
PM16_PATCH2 DQ PM16_PATCH2_ADDR
PM32_PATCH1 DQ PM32_PATCH1_ADDR
PM32_PATCH2 DQ PM32_PATCH2_ADDR
PM32_PATCH3 DQ PM32_PATCH3_ADDR
PM64_PATCH1 DQ PM64_PATCH1_ADDR
PM64_PATCH2 DQ PM64_PATCH2_ADDR
PM64_PATCH3 DQ PM64_PATCH3_ADDR
PM64_PATCH4 DQ PM64_PATCH4_ADDR
PM64_PATCH5 DQ PM64_PATCH5_ADDR

RealModeIntHandlerStartAddr EQU $
RealModeIntStack DQ 0
RealModeInt1DebuggerEntry DQ offset DummyRealModeIntEntry
RealModeInt3DebuggerEntry DQ offset DummyRealModeIntEntry
RealModeSaveCR3	DQ 0

;VOID RealModeInt1Handler();
RealModeInt1Handler PROC PUBLIC
	db 0FAh				;cli

	db 66h, 50h			;push eax
	db 66h, 51h			;push ecx
	db 66h, 52h			;push edx
	db 66h, 53h			;push ebx
	db 66h, 89h, 0E0h		;mov eax, esp		;ebx, edx, ecx, eax, eip, cs, eflag
	db 66h, 83h, 0C0h, (4*7)	;add eax, 4*7
	db 66h, 50h			;push eax
	db 66h, 55h			;push ebp
	db 66h, 56h			;push esi
	db 66h, 57h			;push edi

	db 66h, 89h, 0E3h		;mov ebx, esp
	db 0Fh, 21h, 0F8h		;mov eax, dr7
	db 66h, 50h			;push eax		;dr7
	db 0Fh, 21h, 0F0h		;mov eax, dr6
	db 66h, 50h			;push eax		;dr6
;	mov eax, dr5
	db 66h, 50h			;push eax		;dr5
;	mov eax, dr4
	db 66h, 50h			;push eax		;dr4
	db 0Fh, 21h, 0D8h		;mov eax, dr3
	db 66h, 50h			;push eax		;dr3
	db 0Fh, 21h, 0D0h		;mov eax, dr2
	db 66h, 50h			;push eax		;dr2
	db 0Fh, 21h, 0C8h		;mov eax, dr1
	db 66h, 50h			;push eax		;dr1
	db 0Fh, 21h, 0C0h		;mov eax, dr0
	db 66h, 50h			;push eax		;dr0
	db 0Fh, 20h, 0E0h		;mov eax, cr4
	db 66h, 50h			;push eax		;cr4
	db 0Fh, 20h, 0D8h		;mov eax, cr3
	db 66h, 50h			;push eax		;cr3
	db 0Fh, 20h, 0D0h		;mov eax, cr2
	db 66h, 50h			;push eax		;cr2
;	mov eax, cr1
	db 66h, 50h			;push eax		;cr1	Reserved
	db 0Fh, 20h, 0C0h		;mov eax, cr0
	db 66h, 50h			;push eax		;cr0
	db 66h, 0B8h,00h, 00h, 00h, 00h	;mov eax, 0
	db 8Ch, 0E8h			;mov ax, gs
	db 66h, 50h			;push eax		;gs
	db 8Ch, 0E0h			;mov ax, fs
	db 66h, 50h			;push eax		;fs
	db 8Ch, 0C0h			;mov ax, es
	db 66h, 50h			;push eax		;es
	db 8Ch, 0D0h			;mov ax, ss
	db 66h, 50h			;push eax		;ss
	db 8Ch, 0D8h			;mov ax, ds
	db 66h, 50h			;push eax		;ds
	db 36h, 8Bh, 87h
	dw (8*4)+(1*2)			;mov ax, ss:[bx+8*4+1*2]
	db 66h, 50h			;push eax		;cs
	db 36h, 8Bh, 87h
	dw (8*4)+(2*2)			;mov ax, ss:[bx+8*4+2*2]
	db 66h, 50h			;push eax		;eflag
	db 36h, 8Bh, 87h
	dw (8*4)			;mov ax, ss:[bx+8*4]
	db 66h, 50h			;push eax		;eip
	db 66h, 53h			;push ebx		;ebx maybe destroyed,Save on Stack
	db 0BEh, 01h, 00h		;mov si, 1

	db 0E8h				;call Call64ModeDBGR
	dw offset Call64ModeDBGR-($+2)

	db 66h, 5Bh			;pop ebx		;Restore ebx from Stack
	db 66h, 58h			;pop eax		;eip
	db 36h, 89h, 87h		;mov ss:[bx+8*4], ax
	dw (8*4)
	db 66h, 58h			;pop eax		;eflag
	db 36h, 89h, 87h		;mov ss:[bx+8*4+2*2], ax
	dw (8*4)+(2*2)
	db 66h, 58h			;pop eax		;cs
	db 36h, 89h, 87h		;mov ss:[ebx+8*4+1*2], ax
	dw (8*4)+(1*2)
	db 66h, 58h			;pop eax		;ds
	db 8Eh, 0D8h			;mov ds, ax
	db 66h, 58h			;pop eax		;ss
	db 8Eh, 0D0h			;mov ss, ax
	db 66h, 58h			;pop eax		;es
	db 8Eh, 0C0h			;mov es, ax
	db 66h, 58h			;pop eax		;fs
	db 8Eh, 0E0h			;mov fs, ax
	db 66h, 58h			;pop eax		;gs
	db 8Eh, 0E8h			;mov gs, ax
	db 66h, 58h			;pop eax		;cr0
	db 0Fh, 22h, 0C0h		;mov cr0, eax
	db 66h, 58h			;pop eax		;cr1	Reserved
;	mov cr1, eax
	db 66h, 58h			;pop eax		;cr2
;	mov cr2, eax
	db 66h, 58h			;pop eax		;cr3
	db 0Fh, 22h, 0D8h		;mov cr3, eax
	db 66h, 58h			;pop eax		;cr4
	db 0Fh, 22h, 0E0h		;mov cr4, eax
	db 66h, 58h			;pop eax		;dr0
	db 0Fh, 23h, 0C0h		;mov dr0, eax
	db 66h, 58h			;pop eax		;dr1
	db 0Fh, 23h, 0C8h		;mov dr1, eax
	db 66h, 58h			;pop eax		;dr2
	db 0Fh, 23h, 0D0h		;mov dr2, eax
	db 66h, 58h			;pop eax		;dr3
	db 0Fh,23h, 0D8h		;mov dr3, eax
	db 66h, 58h			;pop eax		;dr4
;	mov dr4, eax
	db 66h, 58h			;pop eax		;dr5
;	mov dr5, eax
	db 66h, 58h			;pop eax		;dr6
	db 0Fh, 23h, 0F0h		;mov dr6, eax
	db 66h, 58h			;pop eax		;dr7
	db 0Fh, 23h, 0F8h		;mov dr7, eax

	db 66h, 5Fh			;pop edi
	db 66h, 5Eh			;pop esi
	db 66h, 5Dh			;pop ebp
	db 66h, 58h			;pop eax
;	db 66h, 89h, 0C4h		;mov esp, eax
	db 66h, 5Bh			;pop ebx
	db 66h, 5Ah			;pop edx
	db 66h, 59h			;pop ecx
	db 66h, 58h			;pop eax

	db 0CFh				;iret
RealModeInt1Handler ENDP

RealModeInt3Handler PROC PUBLIC
	db 0FAh				;cli

	db 66h, 50h			;push eax
	db 66h, 51h			;push ecx
	db 66h, 52h			;push edx
	db 66h, 53h			;push ebx
	db 66h, 89h, 0E0h		;mov eax, esp		;ebx, edx, ecx, eax, eip, cs, eflag
	db 66h, 83h, 0C0h, (4*7)	;add eax, 4*7
	db 66h, 50h			;push eax
	db 66h, 55h			;push ebp
	db 66h, 56h			;push esi
	db 66h, 57h			;push edi

	db 66h, 89h, 0E3h		;mov ebx, esp

	db 0Fh, 21h, 0F8h		;mov eax, dr7
	db 66h, 50h			;push eax		;dr7
	db 0Fh, 21h, 0F0h		;mov eax, dr6
	db 66h, 50h			;push eax		;dr6
;	mov eax, dr5
	db 66h, 50h			;push eax		;dr5
;	mov eax, dr4
	db 66h, 50h			;push eax		;dr4
	db 0Fh, 21h, 0D8h		;mov eax, dr3
	db 66h, 50h			;push eax		;dr3
	db 0Fh, 21h, 0D0h		;mov eax, dr2
	db 66h, 50h			;push eax		;dr2
	db 0Fh, 21h, 0C8h		;mov eax, dr1
	db 66h, 50h			;push eax		;dr1
	db 0Fh, 21h, 0C0h		;mov eax, dr0
	db 66h, 50h			;push eax		;dr0
	db 0Fh, 20h, 0E0h		;mov eax, cr4
	db 66h, 50h			;push eax		;cr4
	db 0Fh, 20h, 0D8h		;mov eax, cr3
	db 66h, 50h			;push eax		;cr3
	db 0Fh, 20h, 0D0h		;mov eax, cr2
	db 66h, 50h			;push eax		;cr2
;	mov eax, cr1
	db 66h, 50h			;push eax		;cr1	Reserved
	db 0Fh, 20h, 0C0h		;mov eax, cr0
	db 66h, 50h			;push eax		;cr0
	db 66h, 0B8h,00h, 00h, 00h, 00h	;mov eax, 0
	db 8Ch, 0E8h			;mov ax, gs
	db 66h, 50h			;push eax		;gs
	db 8Ch, 0E0h			;mov ax, fs
	db 66h, 50h			;push eax		;fs
	db 8Ch, 0C0h			;mov ax, es
	db 66h, 50h			;push eax		;es
	db 8Ch, 0D0h			;mov ax, ss
	db 66h, 50h			;push eax		;ss
	db 8Ch, 0D8h			;mov ax, ds
	db 66h, 50h			;push eax		;ds
	db 36h, 8Bh, 87h
	dw (8*4)+(1*2)			;mov ax, ss:[bx+8*4+1*2]
	db 66h, 50h			;push eax		;cs
	db 36h, 8Bh, 87h
	dw (8*4)+(2*2)			;mov ax, ss:[bx+8*4+2*2]
	db 66h, 50h			;push eax		;eflag
	db 36h, 8Bh, 87h
	dw (8*4)			;mov ax, ss:[bx+8*4]
	db 66h, 50h			;push eax		;eip
	db 66h, 53h			;push ebx		;ebx maybe destroyed,Save on Stack
	db 0BEh, 03h, 00h		;mov si, 3

	db 0E8h				;call Call64ModeDBGR
	dw offset Call64ModeDBGR-($+2)

	db 66h, 5Bh			;pop ebx		;Restore ebx from Stack
	db 66h, 58h			;pop eax		;eip
	db 36h, 89h, 87h		;mov ss:[bx+8*4], ax
	dw (8*4)
	db 66h, 58h			;pop eax		;eflag
	db 36h, 89h, 87h		;mov ss:[bx+8*4+2*2], ax
	dw (8*4)+(2*2)
	db 66h, 58h			;pop eax		;cs
	db 36h, 89h, 87h		;mov ss:[ebx+8*4+1*2], ax
	dw (8*4)+(1*2)
	db 66h, 58h			;pop eax		;ds
	db 8Eh, 0D8h			;mov ds, ax
	db 66h, 58h			;pop eax		;ss
	db 8Eh, 0D0h			;mov ss, ax
	db 66h, 58h			;pop eax		;es
	db 8Eh, 0C0h			;mov es, ax
	db 66h, 58h			;pop eax		;fs
	db 8Eh, 0E0h			;mov fs, ax
	db 66h, 58h			;pop eax		;gs
	db 8Eh, 0E8h			;mov gs, ax
	db 66h, 58h			;pop eax		;cr0
	db 0Fh, 22h, 0C0h		;mov cr0, eax
	db 66h, 58h			;pop eax		;cr1	Reserved
;	mov cr1, eax
	db 66h, 58h			;pop eax		;cr2
;	mov cr2, eax
	db 66h, 58h			;pop eax		;cr3
	db 0Fh, 22h, 0D8h		;mov cr3, eax
	db 66h, 58h			;pop eax		;cr4
	db 0Fh, 22h, 0E0h		;mov cr4, eax
	db 66h, 58h			;pop eax		;dr0
	db 0Fh, 23h, 0C0h		;mov dr0, eax
	db 66h, 58h			;pop eax		;dr1
	db 0Fh, 23h, 0C8h		;mov dr1, eax
	db 66h, 58h			;pop eax		;dr2
	db 0Fh, 23h, 0D0h		;mov dr2, eax
	db 66h, 58h			;pop eax		;dr3
	db 0Fh,23h, 0D8h		;mov dr3, eax
	db 66h, 58h			;pop eax		;dr4
;	mov dr4, eax
	db 66h, 58h			;pop eax		;dr5
;	mov dr5, eax
	db 66h, 58h			;pop eax		;dr6
	db 0Fh, 23h, 0F0h		;mov dr6, eax
	db 66h, 58h			;pop eax		;dr7
	db 0Fh, 23h, 0F8h		;mov dr7, eax

	db 66h, 5Fh			;pop edi
	db 66h, 5Eh			;pop esi
	db 66h, 5Dh			;pop ebp
	db 66h, 58h			;pop eax
;	db 66h, 89h, 0C4h		;mov esp, eax
	db 66h, 5Bh			;pop ebx
	db 66h, 5Ah			;pop edx
	db 66h, 59h			;pop ecx
	db 66h, 58h			;pop eax

	db 0CFh				;iret
RealModeInt3Handler ENDP

;VOID Call64ModeDBGR(UINT16 Int1OrInt3(in si));
Call64ModeDBGR PROC
	db 66h, 0Fh, 0B7h, 0FCh		;movzx edi, sp		;Save in edi
	db 83h, 0C7h			;add di, (4+2)		;Add 4 to skip ebx on stack, 2 to skip ret_addr on stack
	db (4 + 2)
	db 8Ch, 0D0h			;mov ax, ss
	db 66h, 0Fh, 0B7h, 0C0h		;movzx eax, ax
	db 66h, 0C1h, 0E0h, 04h		;shl eax, 4
	db 66h, 01h, 0C7h		;add edi, eax		;edi = absolute addr of RegSet

;Chipset Dependent>>>
	db 0E4h, 92h			;in al, 92h
	db 50h				;push ax
	db 0Ch, 02h			;or al, 1 SHL 1
	db 0E6h, 92h			;out 92h, al
;Chipset Dependent<<<

	db 8Ch, 0D3h			;mov bx, ss		;Save ss in bx
	db 89h, 0E5h			;mov bp, sp		;Save sp in bp
	db 2Eh, 0Fh, 01h, 16h		;lgdt fword ptr cs:DBGR_GDT_LIMIT
PM16_PATCH1_ADDR EQU $
	dw offset DBGR_GDT_LIMIT - RealModeIntHandlerStartAddr
	db 0Fh, 20h, 0C0h		;mov eax, cr0
	db 0Ch, 01h			;or al, 1
	db 0Fh, 22h, 0C0h		;mov cr0, eax
	db 0EBh, 00h			;jmp $+2
	db 0B8h				;mov ax, SYS_DATA32_SEL
	dw SYS_DATA32_SEL
	db 8Eh, 0D8h			;mov ds, ax
	db 8Eh, 0C0h			;mov es, ax
	db 8Eh, 0E0h			;mov fs, ax
	db 8Eh, 0E8h			;mov gs, ax
	db 8Eh, 0D0h			;mov ss, ax
	db 66h, 0EAh			;jmp SYS_CODE32_SEL:PM32_MODE
PM32_PATCH1_ADDR EQU $
	dd offset PM32_MODE - RealModeIntHandlerStartAddr
	dw SYS_CODE32_SEL
PM32_MODE:
	db 0EBh, 00h			;jmp $+2
	db 0A1h				;mov eax, dword ptr ds:RealModeSaveCR3
PM32_PATCH2_ADDR EQU $
	dd offset RealModeSaveCR3 - RealModeIntHandlerStartAddr
	db 0Fh, 22h, 0D8h		;mov cr3, eax
	db 0Fh, 20h, 0E0h		;mov eax, cr4
	db 0Dh				;or eax, 0620h
	dd 0620h
	db 0Fh, 22h, 0E0h		;mov cr4, eax
	db 0B9h				;mov ecx, 0C0000080h
	dd 0C0000080h
	db 0Fh, 32h			;rdmsr
	db 0Fh, 0BAh,0E8h,08h		;bts eax, 8
	db 0Fh, 30h			;wrmsr
	db 0Fh, 20h, 0C0h		;mov eax, cr0
	db 0Fh, 0BAh,0E8h, 1Fh		;bts eax, 31	;Enable Paging
	db 0Fh, 0BAh, 0F0h, 10h		;btr eax, 16
	db 0Fh, 22h, 0C0h		;mov cr0, eax
	db 0EBh, 00h			;jmp $+2
	db 0eah				;jmp SYS_CODE64_SEL: PM64_MODE
PM64_PATCH1_ADDR EQU $
	dd	offset PM64_MODE - RealModeIntHandlerStartAddr
	dw	SYS_CODE64_SEL
PM64_MODE:
	db 66h, 0B8h			;mov ax, SYS_DATA64_SEL
	dw SYS_DATA64_SEL
	db 66h, 8Eh, 0D8h		;mov ds, ax
	db 66h, 8Eh, 0C0h		;mov es, ax
	db 66h, 8Eh, 0E0h		;mov fs, ax
	db 66h, 8Eh, 0E8h		;mov gs, ax
	db 66h, 8Eh, 0D0h		;mov ss, ax
	db 48h, 0C7h, 0C0h		;mov rax, abs_addr &RealModeIntStack
PM64_PATCH2_ADDR EQU $
	dd offset RealModeIntStack - RealModeIntHandlerStartAddr
	db 48h, 8bh, 20h		;mov rsp, [rax]
	db 81h, 0E4h			;and esp, 0fffffff8h	;in the 8-bytes boundary
	dd 0fffffff8h
	db 55h				;push rbp
	db 53h				;push rbx
	db 48h, 0C7h, 0C0h		;mov rax, abs_addr RealModeInt1DebuggerEntry
PM64_PATCH3_ADDR EQU $
	dd offset RealModeInt1DebuggerEntry - RealModeIntHandlerStartAddr
	db 66h, 81h, 0FEh, 01h, 00h	;cmp si, 0001h
	jz CALL_DBGR_ENTRY
	db 48h, 0C7h, 0C0h		;mov rax, abs_addr RealModeInt3DebuggerEntry
PM64_PATCH4_ADDR EQU $
	dd offset RealModeInt3DebuggerEntry - RealModeIntHandlerStartAddr
CALL_DBGR_ENTRY:
	db 48h,0C7h, 0C1h		;mov rcx, 0
	dd 00h
	db 89h, 0F9h			;mov ecx, edi
	db 51h				;push rcx
	db 0FFh, 10h			;call qword ptr [rax]	;DBGR (RegsSet *(in rcx))
	db 59h				;pop rcx
	db 5Bh				;pop rbx
	db 5Dh				;pop rbp
	db 0ffh,2dh, 00h, 00h, 00h, 00h	;jmp far ptr [rip+00000000h]
PM64_PATCH5_ADDR EQU $
	dd offset PM32_MODE_EXIT - RealModeIntHandlerStartAddr
	dw SYS_CODE32_SEL
PM32_MODE_EXIT:
	db 0Fh, 20h, 0C0h		;mov eax, cr0
	db 0Fh, 0BAh, 0F0h, 1Fh		;btr eax, 31
	db 0Fh, 22h, 0C0h		;mov cr0, eax
	db 0EBh, 00h			;jmp $+2
	db 0b9h				;mov ecx, 0C0000080h
	dd 0C0000080h
	db 0Fh, 32h			;rdmsr
	db 0Fh, 0BAh, 0F0h, 08h		;btr eax, 8
	db 0Fh, 30h			;wrmsr
	db 66h, 0B8h			;mov ax, SYS_DATA16_SEL
	dw SYS_DATA16_SEL
	db 66h, 8Eh, 0D8h		;mov ds, ax
	db 66h, 8Eh, 0C0h		;mov es, ax
	db 66h, 8Eh, 0E0h		;mov fs, ax
	db 66h, 8Eh, 0E8h		;mov gs, ax
	db 66h, 8Eh, 0D0h		;mov ss, ax
	db 0eah				;jmp SYS_CODE16_SEL:PM16_MODE_EXIT
PM32_PATCH3_ADDR EQU $
	dd offset PM16_MODE_EXIT - RealModeIntHandlerStartAddr
	dw SYS_CODE16_SEL
PM16_MODE_EXIT:
	db 0Fh, 20h, 0C0h		;mov eax, cr0
	db 24h, 0FEh			;and al, 0feh
	db 0Fh, 22h, 0C0h		;mov cr0, eax
	db 0eah				;jmp E000: RM16_EXIT
PM16_PATCH2_ADDR EQU $
	dw offset RM16_EXIT - RealModeIntHandlerStartAddr
	dw 0E000h
RM16_EXIT:
	db 89h, 0ECh			;mov sp, bp
	db 8Eh, 0D3h			;mov ss, bx

;Chipset Dependent>>>
	db 58h				;pop ax
	db 0E6h, 92h			;out 92h, al
;Chipset Dependent<<<

	ret
Call64ModeDBGR ENDP

align 16
DBGR_GDT_BASE:
NULL_SEL	equ	$-DBGR_GDT_BASE	;NULL Selector 0
	dd 00000000h
	dd 00000000h
DATA_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x08], Data 0-ffffffff 32 bit
	dd 0000ffffh
	dd 00cf9300h
CODE_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x10], CODE 0-ffffffff 32 bit
	dd 0000ffffh
	dd 00cf9b00h
SYS_DATA32_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x18], DATA 32-bit Limit: 0 ~ 0xffffffff
	dd 0000FFFFh
	dd 00cf9300h
SYS_CODE32_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x20], CODE 32-bit Limit: 0 ~ 0xffffffff
	dd 0000FFFFh
	dd 00cf9b00h
UNUSED_ENTRY1	equ	$-DBGR_GDT_BASE	;Unused Entry
	dd 00000000h
	dd 00000000h
SYS_DATA64_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x30], DATA 64-bit
	dd 0000FFFFh
	dd 00cf9300h
SYS_CODE64_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x38], CODE 64-bit
	dd 0000FFFFh
	dd 00af9b00h
UNUSED_ENTRY2	equ	$-DBGR_GDT_BASE	;Unused Entry
	dd 00000000h
	dd 00000000h
SYS_DATA16_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x40], DATA 16-bit Limit: 0 ~ 0xffffffff
	dd 0000ffffh
	dd 008f9300h
SYS_CODE16_SEL	equ	$-DBGR_GDT_BASE	; Selector [0x48], CODE 16-bit Limit: 0 ~ 0xfffff
	dd 0000ffffh
	dd 000f9b00h
DBGR_GDT_SIZE	equ	$-DBGR_GDT_BASE	;Size of Descriptor Table

DBGR_GDT_LIMIT:
	dw	DBGR_GDT_SIZE - 1					; GDT limit
DBGR_GDT_PTR:
	DQ	offset DBGR_GDT_BASE - RealModeIntHandlerStartAddr	; GDT base	;To be patched
RealModeIntHandlerEndAddr EQU $

DummyRealModeIntEntry PROC
	ret
DummyRealModeIntEntry ENDP

align 16
;UINTN DebugGetCR3();
DebugGetCR3 PROC PUBLIC
	mov rax, CR3
	ret
DebugGetCR3 ENDP

align 16
;VOID InitDebugHardware();
InitDebugHardware PROC PUBLIC
	mov rax, cr4
	or eax, 01h SHL 3
	mov cr4, rax
	ret
InitDebugHardware ENDP

align 16
;VOID DebugCPUID(UINT32 *EAX(in rcx),UINT32 *EBX(in rdx),UINT32 *ECX(in r8),UINT32 *EDX(in r9));
DebugCPUID PROC PUBLIC
	push r10
	push r11
	push rax
	push rbx
	push rcx
	push rdx
	mov r10, rcx	;Arg0 - UINT32 *EAX
	mov r11, rdx	;Arg1 - UINT *EBX
	mov eax, [r10]	;eax := *EAX
	mov ebx, [r11]	;ebx := *EBX
	mov ecx, [r8]	;ecx := *ECX
	mov edx, [r9]	;edx := *EDX
	cpuid
	mov [r10], eax	;*EAX := eax
	mov [r11], ebx	;*EBX := ebx
	mov [r8], ecx	;*ECX := ecx
	mov [r9], edx	;*EDX := edx
	pop rdx
	pop rcx
	pop rbx
	pop rax
	pop r11
	pop r10
	ret
DebugCPUID ENDP

align 16
;VOID DebugRDMSR(UINT32 *eax(in rcx),UINT32 *ecx(in rdx),UINT32 *edx(in r8));
DebugRDMSR PROC PUBLIC
	push r10
	push r11
	push rax
	push rcx
	push rdx
	mov r10, rcx	;Arg0 - UINT32 *EAX
	mov r11, rdx	;Arg1 - UINT32 *ECX
	mov eax, [r10]	;eax := *EAX
	mov ecx, [r11]	;ecx := *ECX
	mov edx, [r8]	;edx := *EDX
	rdmsr
	mov [r10], eax	;*EAX := eax
	mov [r11], ecx	;*ECX := ecx
	mov [r8], edx	;*EDX := edx
	pop rdx
	pop rcx
	pop rax
	pop r11
	pop r10
	ret
DebugRDMSR ENDP

align 16
;VOID DebugWRMSR(UINT32 eax(in rcx),UINT32 ecx(in rdx),UINT32 edx(in r8));
DebugWRMSR PROC PUBLIC
	push rax
	push rcx
	push rdx
	mov rax, rcx	;Arg0 - UINT32 EAX
	mov rcx, rdx	;Arg1 - UINT32 ECX
	mov rdx, r8	;Arg2 - UINT32 EDX
	wrmsr
	pop rdx
	pop rcx
	pop rax
	ret
DebugWRMSR ENDP

align 16
;VOID DebugLoadIDT(struct IdtDescriptor *IDTp(in rcx));
DebugLoadIDT PROC PUBLIC
	lidt fword ptr [rcx]
	ret
DebugLoadIDT ENDP

align 16
;VOID DebugSaveIDT(struct IdtDescriptor *IDTp);
DebugSaveIDT PROC PUBLIC
	sidt fword ptr [rcx]
	ret
DebugSaveIDT ENDP

align 16
;UINT16 DebugGetCS();
DebugGetCS PROC PUBLIC
	mov rax, 0
	mov ax, cs
	ret
DebugGetCS ENDP

DBGR_REG_BUF	STRUCT
DBGR_RBX	QWORD	?
DBGR_RSP	QWORD	?
DBGR_RBP	QWORD	?
DBGR_RDI	QWORD	?
DBGR_RSI	QWORD	?
DBGR_R10	QWORD	?
DBGR_R11	QWORD	?
DBGR_R12	QWORD	?
DBGR_R13	QWORD	?
DBGR_R14	QWORD	?
DBGR_R15	QWORD	?
DBGR_RIP	QWORD	?
DBGR_REG_BUF	ENDS

PUBLIC  DebugSetJmp
;INTN DebugSetJmp(DBGR_REG_BUF *buf);
DebugSetJmp	PROC
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_RBX, rbx
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_RSP, rsp
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_RBP, rbp
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_RDI, rdi
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_RSI, rsi
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_R10, r10
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_R11, r11
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_R12, r12
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_R13, r13
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_R14, r14
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_R15, r15
	mov   rax, QWORD PTR [rsp+0]
	mov   (DBGR_REG_BUF PTR [rcx]).DBGR_RIP, rax
	mov   rax, 0
	ret
DebugSetJmp	ENDP

PUBLIC  DebugLongJmp
;void DebugLongJmp(DBGR_REG_BUF *buf,int value);
DebugLongJmp	PROC
	mov   rax, rdx			;rax = value
	mov   rbx, (DBGR_REG_BUF PTR [rcx]).DBGR_RBX
	mov   rsp, (DBGR_REG_BUF PTR [rcx]).DBGR_RSP
	mov   rbp, (DBGR_REG_BUF PTR [rcx]).DBGR_RBP
	mov   rdi, (DBGR_REG_BUF PTR [rcx]).DBGR_RDI
	mov   rsi, (DBGR_REG_BUF PTR [rcx]).DBGR_RSI
	mov   r10, (DBGR_REG_BUF PTR [rcx]).DBGR_R10
	mov   r11, (DBGR_REG_BUF PTR [rcx]).DBGR_R11
	mov   r12, (DBGR_REG_BUF PTR [rcx]).DBGR_R12
	mov   r13, (DBGR_REG_BUF PTR [rcx]).DBGR_R13
	mov   r14, (DBGR_REG_BUF PTR [rcx]).DBGR_R14
	mov   r15, (DBGR_REG_BUF PTR [rcx]).DBGR_R15
	add   rsp, 8
	jmp   QWORD PTR (DBGR_REG_BUF PTR [rcx]).DBGR_RIP
	ret
DebugLongJmp	ENDP

END

