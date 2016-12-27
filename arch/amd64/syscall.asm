global syscall

section .text

syscall:
	push rbp
	mov rbp, rsp

	mov rax, rdi ; syscall
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, r10
	mov r10, r8
	mov r8, r9
	syscall

	pop rbp
	ret

section .data
