;.686
;.model	flat

externdef EnterGlobalWithInfo:PROC
externdef LeaveGlobalWithInfo:PROC
externdef TailcallGlobalWithInfo:PROC

public EnterNaked3WithInfo
public LeaveNaked3WithInfo
public TailcallNaked3WithInfo

.data

.code

EnterNaked3WithInfo:
    push	rbp
    mov		rbp, rsp
    
	;pushad
	push	rdx
	push	rax

    mov		rdx, [rbp + 0Ch]
    push	rdx
    mov		rax, [rbp + 08h]
    push	rax
    call	EnterGlobalWithInfo

    ;popad
	pop		rax
	pop		rdx

    pop		rbp
    ret		16

LeaveNaked3WithInfo:
    push	rbp
    mov		rbp, rsp
    
	;pushad
	push	rdx
	push	rax

    mov		rdx, [rbp + 0Ch]
    push	rdx
    mov		rax, [rbp + 08h]
    push	rax
    call	LeaveGlobalWithInfo
    
	;popad
	pop		rax
	pop		rdx

    pop		rbp
    ret		16

TailcallNaked3WithInfo:
    push	rbp
    mov		rbp, rsp
    
	;pushad
	push	rdx
	push	rax

    mov		rdx, [rbp + 0Ch]
    push	rdx
    mov		rax, [rbp + 08h]
    push	rax
    call	TailcallGlobalWithInfo
    
	;popad
	pop		rax
	pop		rdx

    pop		rbp
    ret		8
	
END