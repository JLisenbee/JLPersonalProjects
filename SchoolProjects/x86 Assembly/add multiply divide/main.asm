; main.asm  this is the main function
; compile:      nasm -f elf64 -g main.asm -o  main.o 
; link:         gcc -m64 -o main main.o
; run:          ./main > main.out
; view:         cat main.out
; result:       5 = sum(2,3)

        extern  printf
        extern 	sum, sub2, mult2

        section .data
x:      dq      2
y:      dq      3
fmt_sum:    db      "%ld = sum(%ld,%ld)",10,0
fmt_sub:    db      "%ld = sub(%ld,%ld)",10,0
fmt_mult:   db      "%ld = mult(%ld,%ld)",10,0

        section .bss
z:      resq    1

        section .text
        global  main

main:   push    rbp             ; set up stack

        mov     rdi, [x]        ; pass arguments for sum
        mov     rsi, [y]
        call    sum             ; coded below
        mov     [z],rax         ; save result from sum
        mov     rdi, fmt_sum    ; print
	call print

	mov     rdi, [x]        ; pass arguments for sub
        mov     rsi, [y]
        call    sub2            ; coded below
        mov     [z],rax         ; save result from sum
        mov     rdi, fmt_sub    ; print
	call print

	mov     rdi, [x]        ; pass arguments for mult
        mov     rsi, [y]
        call    mult2           ; coded below
        mov     [z],rax         ; save result from sum
        mov     rdi, fmt_mult   ; print
	call print

        pop     rbp             ; restore stack
        mov     rax,0

print:				;Print
        mov     rsi, [z]
        mov     rdx, [x]        ; yes, rdx comes before rcx
        mov     rcx, [y]
        mov     rax, 0          ; no float or double
        call    printf
	ret

; end main

; end main.asm