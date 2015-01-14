extern EnterGlobalWithInfo:PROC, LeaveGlobalWithInfo:PROC, TailcallGlobalWithInfo:PROC

public EnterNaked3WithInfo, LeaveNaked3WithInfo, TailcallNaked3WithInfo

.data

.code

EnterNaked3WithInfo:
    ;push	rbp
    ;mov		rbp, rsp
    
    push	r9
    push	r8
    push	rdx
    push	rcx
	sub		rsp, 20h
    call	EnterGlobalWithInfo

	add		rsp, 20h

    pop		rcx
    pop		rdx
    pop		r8
    pop		r9

    ;pop		rbp
    ret

LeaveNaked3WithInfo:
    push	rbp
    mov		rbp, rsp
    
    push	r9
    push	r8
    push	rdx
    push	rcx

    call	LeaveGlobalWithInfo
    
    pop		rcx
    pop		rdx
    pop		r8
    pop		r9

    pop		rbp
    ret

TailcallNaked3WithInfo:
    push	rbp
    mov		rbp, rsp
    
    push	r9
    push	r8
    push	rdx
    push	rcx

    call	TailcallGlobalWithInfo
    
    pop		rcx
    pop		rdx
    pop		r8
    pop		r9

    pop		rbp
    ret
    
END