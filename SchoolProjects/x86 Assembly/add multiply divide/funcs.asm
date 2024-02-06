;sum.asm

section .text
global sum, sub2, mult2

sum:    ; function long int sum(long int x, long int y)
        ; so simple, do not need to save anything

        mov     rax,rdi         ; get argument x
        add     rax,rsi         ; add argument y, x+y result in rax
        ret

sub2:
	mov rax, rdi
	sub rax, rsi
	ret

mult2:
	mov rax, rdi
	imul rsi
	ret