
.code

MultiThread_REG_BUF	STRUCT
	MultiThread_RBX	QWORD	?
	MultiThread_RSP	QWORD	?
	MultiThread_RBP	QWORD	?
	MultiThread_RDI	QWORD	?
	MultiThread_RSI	QWORD	?
	MultiThread_R10	QWORD	?
	MultiThread_R11	QWORD	?
	MultiThread_R12	QWORD	?
	MultiThread_R13	QWORD	?
	MultiThread_R14	QWORD	?
	MultiThread_R15	QWORD	?
	MultiThread_RIP	QWORD	?
MultiThread_REG_BUF	ENDS

PUBLIC  MultiThread_SetJmp
;INTN MultiThread_SetJmp(MultiThread_REG_BUF *buf);
MultiThread_SetJmp PROC
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_RBX, rbx
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_RSP, rsp
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_RBP, rbp
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_RDI, rdi
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_RSI, rsi
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_R10, r10
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_R11, r11
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_R12, r12
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_R13, r13
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_R14, r14
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_R15, r15
	mov   rax, QWORD PTR [rsp+0]
	mov   (MultiThread_REG_BUF PTR [rcx]).MultiThread_RIP, rax
	mov   rax, 0
	ret
MultiThread_SetJmp ENDP

PUBLIC  MultiThread_LongJmp
;void MultiThread_LongJmp(DBGR_REG_BUF *buf,int value);
MultiThread_LongJmp PROC
	mov   rax, rdx ;rax = value
	mov   rbx, (MultiThread_REG_BUF PTR [rcx]).MultiThread_RBX
	mov   rsp, (MultiThread_REG_BUF PTR [rcx]).MultiThread_RSP
	mov   rbp, (MultiThread_REG_BUF PTR [rcx]).MultiThread_RBP
	mov   rdi, (MultiThread_REG_BUF PTR [rcx]).MultiThread_RDI
	mov   rsi, (MultiThread_REG_BUF PTR [rcx]).MultiThread_RSI
	mov   r10, (MultiThread_REG_BUF PTR [rcx]).MultiThread_R10
	mov   r11, (MultiThread_REG_BUF PTR [rcx]).MultiThread_R11
	mov   r12, (MultiThread_REG_BUF PTR [rcx]).MultiThread_R12
	mov   r13, (MultiThread_REG_BUF PTR [rcx]).MultiThread_R13
	mov   r14, (MultiThread_REG_BUF PTR [rcx]).MultiThread_R14
	mov   r15, (MultiThread_REG_BUF PTR [rcx]).MultiThread_R15
	add   rsp, 8
	jmp   QWORD PTR (MultiThread_REG_BUF PTR [rcx]).MultiThread_RIP
	ret
MultiThread_LongJmp ENDP

align 16
;UINTN MultiThread_GetSackPointer();
MultiThread_GetSackPointer PROC PUBLIC
	mov rax, rsp
	add rax, 8
	ret
MultiThread_GetSackPointer ENDP


EXTERN OsFinish:NEAR

align 16
;VOID MultiThread_SetSackPointer_and_call(VOID *tcb,UINTN StackPointer,MultiThread_Func func,void *arg);
MultiThread_SetSackPointer_and_call PROC PUBLIC
	mov rsp, rdx
	push rcx
	mov rcx, r9
	call r8
	pop rcx
	call OsFinish
MultiThread_Never_Reach:
	jmp MultiThread_Never_Reach
	ret
MultiThread_SetSackPointer_and_call ENDP

END

