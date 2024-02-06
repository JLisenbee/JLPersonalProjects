extern printf
extern scanf	

%define EXIT 60
%define WRITE 1
%define READ 0
%define BUFLEN 1
%define ZERO 0

section .data
	format_prompt: db '%s',10,0	
	format:	db '%d %s',10,0
	format_scan: db '%d',0
	prompt:	db 'Enter a year:',0
	messageTrue: db 'is a Leap Year',0
	messageFalse:	db 'is not a Leap Year',0
	
section .bss
	buf: resd BUFLEN
	isDiv4: resd 1
	isDiv100: resd 1
	isDiv400: resd 1
	isLeap: resd 1

section .text

divide400:		;Divides the number in buf by 400. If it's evenly divided, print true. If else, move on.
	mov r8, 400
	mov rax, [buf]
	mov rdx, 0
	idiv qword r8
	mov [isDiv400], rdx
	mov r8, 0
	cmp [isDiv400], r8
	je printTrue
	jmp divide100

divide100:		;Divides the number in buf by 100. If it's evenly divided, print false. If else, move on.
	mov r8, 100
	mov rax, [buf]
	mov rdx, 0
	idiv qword r8
	mov [isDiv100], rdx
	mov r8, 0
	cmp [isDiv100], r8
	je printFalse
	jmp divide4

divide4:		;Divides the number in buf by 4. If it's evenly divided, print true. If else, print false.
	mov r8, 4
	mov rax, [buf]
	mov rdx, 0
	idiv qword r8
	mov [isDiv4], rdx
	mov r8, 0
	cmp [isDiv4], r8
	je printTrue
	jmp printFalse

global _start:
_start:
	mov rdi, format_prompt       	;Print Prompt
	mov rsi, prompt
	mov rax, 0
	call printf

	mov rdi, format_scan		;Get user input
	mov rsi, buf
	mov rax, 0
	call scanf
	
	jmp divide400		;Start checking for leap year validity starting with the most restrictive requirement

printTrue:			;Branch to here if the year is a leap year
	mov rdi, format
	mov rsi, [buf]		
	mov rdx, messageTrue	
	mov rax, 0		
	call printf
	jmp done
	
printFalse:			;Branch to here if the number is not a leap year
	mov rdi, format
	mov rsi, [buf]
	mov rdx, messageFalse
	mov rax, 0
	call printf
	jmp done

done:			;Home Stretch and cleanup
	mov rax, 60	; 'exit' syscall number
	xor rdi, rdi	;rdi holds a 0
	syscall		;invokes a syscall
