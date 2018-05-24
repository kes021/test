section .text

global exit

; exit(rax = error code): no return
exit:
	mov rdi, rax
	mov rax, 0x2000001
	syscall 



