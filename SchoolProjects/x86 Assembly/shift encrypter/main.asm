;Main.asm
;Progression for calling C functions: rdi, rsi, rdx, rcx, r8, r9. returns to rax.

extern printf
extern scanf
extern validate, shift

%define EXIT 60
%define WRITE 1
%define READ 0
%define BUFLEN 50
%define STDIN 0
%define STDOUT 1

section .data
	default_text: db 'This is the original message.',0
	menu_text1: db 'Menu',10,'1. Input a New Message',10,0
	menu_text2: db '2. Shift Encypt',10,0
	menu_text3: db '3. Display Unencrypted Message',10,0
	menu_text4: db '4. Quit',10,0
	menu_text5: db 'Enter a Number (1-4):',10,0
	new_msg_text: db 'Enter a New Message',10,'New Message must start with a Capital Letter',10,'and end with a period, question, or exclamation point',0
	disp_header_msg: db 'The Current Unencrypted Message Is:',0
	disp_encrypt_msg: db 'The message encrypted is:',0
	shift_prompt_text: db 'Enter a number between 0 and 25: ',0
	debug_text: db 'DEBUG TEXT',0
	exit_text: db 'Goodbye! :)',0

	menu_format: db '%s%s%s%s%s',0
	formatd: db '%d',0
	formatso: db '%s',10,0
	formatsi: db '%s',0
	formatsd: db '%s %d',10,0
	formatss: db '%s %s',10,0
		
section .bss
	i: resb 10
	msg_output: resb BUFLEN
	new_msg: resb BUFLEN
	shift_amt: resb BUFLEN
	encrypted: resb BUFLEN

section .text

global _start:
_start:
	xor rcx, rcx

_preload:
	;Pre-Load Default Message
	mov al, [default_text+rcx]
	mov [msg_output+rcx], al
	cmp al, 0
	je _menu
	inc rcx
	jmp _preload

_menu:
	;Print the menu
	mov rax, 0
	mov rdi, menu_format
	mov rsi, menu_text1
	mov rdx, menu_text2
	mov rcx, menu_text3
	mov r8, menu_text4
	mov r9, menu_text5
	call printf

	;Get user's menu choice
	mov rax, 0
	mov rdi, formatd
	mov rsi, i
	call scanf

_break:
	;Determine where to go from here based on user selection
	mov r8, [i]

	cmp r8, 1
	je new_message 		;go get a new message
	
	cmp r8, 2
	je shift_encrypt 	;shift the current message

	cmp r8, 3
	je display_current 	;display the current message

	cmp r8, 4 		
	je end			;end the program
	
	jmp _menu		;Entry was invalid, return to top of menu

new_message:
	;Prompt for New Message
	mov rax, 0
	mov rdi, formatso
	mov rsi, new_msg_text
	call printf

	mov rax, READ
	mov rdi, STDIN
	mov rsi, msg_output
	mov rdx, BUFLEN
	syscall
	
	;Set up this like you would for printf (0 at end instead of 10)
	xor rcx, rcx
_load:
	mov al, [msg_output+rcx]
	cmp al, 10
	je end_load
	inc rcx
	jmp _load
end_load:
	xor r10, r10
	mov [msg_output+rcx], r10

	mov r12, msg_output
	call validate		;Validate the Entry

	;check return of Validate. Call for new message again if invalid.
	cmp r12, 404
	je new_message

	jmp _menu

shift_encrypt:
	; Prompt for shift #
	mov rax, 0
	mov rdi, formatso
	mov rsi, shift_prompt_text
	call printf

	mov rax, 0
	mov rdi, formatd
	mov rsi, shift_amt
	call scanf

	mov al, [shift_amt]

	; Validate that the number is between 0 and 25
	cmp al, 0
	jl shift_encrypt
	cmp al, 25
	jg shift_encrypt

	; Mov to persistant registers for moving to subroutine
	xor rcx, rcx
	xor r12, r12
	xor r13, r13
	mov r12, [shift_amt+rcx]
	mov r13, msg_output

	; encrypt the message
	call shift

	; display the encrypted function
	mov rax, 0
	mov rdi, formatss
	mov rsi, disp_encrypt_msg
	mov rdx, r12
	call printf

	;Return to Menu
	jmp _menu

display_current:
	;Display Message
	mov rax, 0
	mov rdi, formatss
	mov rsi, disp_header_msg
	mov rdx, msg_output
	call printf

	;Return to Menu
	jmp _menu

end:			;Exit the program
	mov rax, 0
	mov rdi, formatso
	mov rsi, exit_text
	call printf

	xor rdi, rdi
	mov rax, EXIT
	syscall
	
