global _start

section .data
message1: db 'Hello',10
message2: db 'world!',10
message3: db 'This is Group 2,',10
message4: db 'nice to meet you!',10

section .text
_start:
	;; Hello
	mov rax, 1       ;system call number should be stored in rax
	mov rdi, 1       ;argument #1 in rdi: where to write (descriptor)?
	mov rsi, message1;argument #2 in rsi: where does the string start?
	mov rdx, 6       ;argument #3 in rdx, how many bytes to write?
	syscall          ;this instruction invokes a system call
	
	;; world!
	mov rax, 1
	mov rdi, 1
	mov rsi, message2
	mov rdx, 7
	syscall

	;; This is Group X,
	mov rax, 1
	mov rdi, 1
	mov rsi, message3
	mov rdx, 17
	syscall

	;; nice to meet you!
	mov rax, 1
	mov rdi, 1
	mov rsi, message4
	mov rdx, 18
	syscall
	
	;; Ends the program without a segfault
	mov rax, 60 	;syscall command changed to 'exit'
	xor rdi, rdi	;clear up rdi to 0
	syscall 	;syscall (60, exit)
