
.code

getTEB proc
mov rax, qword ptr gs : [30h] ; the value of the TEB(thread env block) is in the gs reg
ret

getTEB endp

CustomError proc

xor eax, eax
call getTEB
mov eax, dword ptr[rax + 68h]; LastError is in 0x68
ret

customError endp
end