global _start

section .text

extern main

_start:
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	call main

	mov rdi, rax ; Move the return value of main to the error code arg of sys_exit
	mov rax, 60 ; sys_exit
	syscall
	
	
