extern EnterGlobalWithInfo:PROC, LeaveGlobalWithInfo:PROC, TailcallGlobalWithInfo:PROC

public EnterNaked3WithInfo, LeaveNaked3WithInfo, TailcallNaked3WithInfo

.data

.code

    align	16

EnterNaked3WithInfo proc frame
    push	rax
;	push	rbx
;	push	rcx
;	push	rdx
;	push	r8
;	push	r9
    push	r10
    push	r11
    .allocstack 32

    sub		rsp, 20h
    .allocstack	32
    

    .endprolog

    call	EnterGlobalWithInfo

    add		rsp, 20h

    pop		r11
    pop		r10
;	pop		r9
;	pop		r8
;	pop		rdx
;	pop		rcx
;	pop		rbx
    pop		rax

    ret
EnterNaked3WithInfo endp

    ;align	16

LeaveNaked3WithInfo proc frame    
    push	rax
    .allocstack	8

    sub		rsp, 20h
    .allocstack	20h

    .endprolog

    call	LeaveGlobalWithInfo
    
    add		rsp, 20h
    pop		rax
    ret
LeaveNaked3WithInfo endp

    ;align	16

TailcallNaked3WithInfo proc frame
    push	rax
    .allocstack	8

    sub		rsp, 20h
    .allocstack	20h

    .endprolog

    call	TailcallGlobalWithInfo

    add		rsp, 20h    
    pop		rax

    ret
TailcallNaked3WithInfo endp
    
END