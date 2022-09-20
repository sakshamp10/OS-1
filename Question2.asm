global main
extern printf, scanf

section .text
main:
        push rbp
        mov rbp, rsp
        sub rsp, 16

        xor eax,eax
        lea rdi, [msg]
        call printf

        mov eax, 0
        lea rdi, [format]
        lea rsi, [number]
        call scanf

        lea rdi, [format2]
        mov edx, [number]
        xor eax,eax
        call printf

        xor eax,eax
        lea rdi, [msg2]
        call printf

        mov eax,0
        lea rdi, [string]
        lea rsi, [s]
        call scanf

        lea rdi, [format3]
        lea rsi, [s]
        xor eax,eax
        call printf

        add rsp,16
        leave
        ret

section .data
    msg: db "Enter a number: ",0
    msg2: db "Enter a string: ",0
    format:db "%d",0
    string:db "%s",0
    format2:db "The number is: %d",10,0
    format3:db "The string is: %s",0
    s times 10000 db 0
section .bss
number resb 4
