;Validate.asm

extern printf

section .data
	format: db '%s',10,0
	message_fail: 

section .bss

global validate:

section .text
validate:
	xor rcx, rcx
	mov al, [r12]
	
check_first1:	;Checks the first character for being less than A
	cmp al, 64
	jge check_first2
	mov r12, 1	;First character was less than A
	jmp end

check_first2:	;Checks the first character for being more than Z
	cmp al, 91
	jle find_end
	mov r12, 1	;First character was more than Z
	jmp end

find_end:
	;Finds the last letter

	mov al, [r12+rcx+1]
	cmp al, 0
	je check_exclamation	;Once last character is found, go to process it
	inc rcx
	jmp find_end

check_exclamation:
	mov al, [r12+rcx]
	cmp al, 33
	je end			; Valid answer, go to end
	jmp check_period	; Not what we wanted, but there's other ways to pass

check_period:
	mov al, [r12+rcx]
	cmp al, 46
	je end			; Valid answer, go to end
	jmp check_question	; Not what we wanted, but there's other ways to pass

check_question:
	mov al, [r12+rcx]
	cmp al, 63
	je end			; Valid answer, go to end
	mov r12, 404
	jmp end			; Not what we wanted, go back and take a 404 with you

end:
	ret