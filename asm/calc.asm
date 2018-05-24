section .data
	Digit db 0,10

extern exit

section .text
	global start
start:
	mov rax, 7
	call printRAXDigit	
	xor rax, rax
	call exit

printRAXDigit:
	add rax, 48
	mov [qword Digit], al
	mov rax, 0x2000004
	mov rdi, 1
	mov rsi, Digit
	mov rdx, 2
	syscall
	ret


