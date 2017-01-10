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
	mov r9, [rsp] 	; Copy instead of pop
			; removing an argument if it's not passed in will trash the stack
	syscall

	pop rbp
	ret

section .data
