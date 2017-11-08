.686
.model flat,c

;extrn EnterGlobalWithInfo:PROC, LeaveGlobalWithInfo:PROC, TailcallGlobalWithInfo:PROC

public EnterNaked3WithInfo, LeaveNaked3WithInfo, TailcallNaked3WithInfo

EnterGlobalWithInfo PROTO STDCALL functionIdOrClientId:DWORD, COR_PRF_ELT_INFO:DWORD
LeaveGlobalWithInfo PROTO STDCALL functionIdOrClientId:DWORD, COR_PRF_ELT_INFO:DWORD
TailcallGlobalWithInfo PROTO STDCALL functionIdOrClientId:DWORD, COR_PRF_ELT_INFO:DWORD

.data

.code

EnterNaked3WithInfo proc
		push ebp
        mov ebp, esp
        pushad
        mov edx, [ebp + 12]
        push edx
        mov eax, [ebp + 8]
        push eax
        call EnterGlobalWithInfo
        popad
        pop ebp
        ret 20 ;20h?
EnterNaked3WithInfo endp

LeaveNaked3WithInfo proc
        push ebp
        mov ebp, esp
        pushad
        mov edx, [ebp + 12]
        push edx
        mov eax, [ebp + 8]
        push eax
        call LeaveGlobalWithInfo;
        popad
        pop ebp
        ret 20;
LeaveNaked3WithInfo endp

TailcallNaked3WithInfo proc
		push ebp
        mov ebp, esp
        pushad
        mov edx, [ebp + 12]
        push edx
        mov eax, [ebp + 8]
        push eax
        call TailcallGlobalWithInfo;
        popad
        pop ebp
        ret 20
TailcallNaked3WithInfo endp

		end