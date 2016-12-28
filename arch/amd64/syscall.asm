global syscall

section .text

syscall:
	push rbp
	mov rbp, rsp

	mov rax, rdi ; syscall
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	mov r10, r8
	mov r8, r9
	;pop r9	; This will trash the stack if the argument isn't present
	syscall

	pop rbp
	ret

section .data
