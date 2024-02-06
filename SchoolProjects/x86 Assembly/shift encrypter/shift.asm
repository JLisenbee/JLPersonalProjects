;shift.asm

extern printf
extern encrypt

%define BUFLEN 50

section .data
	format: db '%s',10,0

section .bss
	encrypted: resb BUFLEN

global shift:

section .text
shift:
	; Shift each letter at a time
	xor r9, r9
	xor r8, r8
_loop:
	mov al, [r13+r9] 	;al holds r9-th character
	cmp al, 0
	je end			; Jump to end if we're at the end
	mov rdi, rax
	mov rsi, r12
	call encrypt		; Call to encryption function
	mov [encrypted+r9], rax
	mov [encrypted+r9+1], r8
	inc r9
	jmp _loop

end:
	; move encrypted stuff to r12 for moving to main function
	mov r12, encrypted
	ret
