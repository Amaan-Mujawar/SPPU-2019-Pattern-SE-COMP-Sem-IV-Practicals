; Amaan Mujawar
  COMPUTER SE B 
  Roll No. 56 
  TSSM’s PVPIT, Bavdhan, Pune

; ---------- QUESTION - 9 ----------

; Write X86 ALP to find, (a) Number of Blank spaces (b) Number of lines 
  (c) Occurrence of a particular character. Accept the data from the text 
  file. The text file has to be accessed during Program_1 execution and write 
  FAR PROCEDURES in Program_2 for the rest of the processing. Use of PUBLIC 
  and EXTERN directives is mandatory.

; ------------------ Program_1.asm ------------------
; Assemble: nasm -f elf64 Program_1.asm
;           nasm -f elf64 Program_2.asm
; Link:     ld -o program Program_1.o Program_2.o

extern count_blanks              ; Externally defined far procedure to count spaces
extern count_lines               ; Externally defined far procedure to count lines
extern count_char                ; Externally defined far procedure to count a character

section .data
filename db "input.txt", 0       ; File to read from
char_to_search db 'a'            ; Character whose occurrences we want to count

msg1 db "Blank spaces: ", 0xA    ; Message for blank count
len1 equ $-msg1

msg2 db "Lines: ", 0xA           ; Message for line count
len2 equ $-msg2

msg3 db "Occurrences of 'a': ", 0xA ; Message for char count
len3 equ $-msg3

newline db 0xA                   ; Newline character

section .bss
buffer resb 1000                 ; Buffer to hold file content
blank_count resb 4               ; Result: blank space count
line_count resb 4                ; Result: line count
char_count resb 4                ; Result: char occurrence count

section .text
global _start

_start:
    ; Open the file (syscall open)
    mov rax, 2                   ; sys_open
    mov rdi, filename            ; File name
    mov rsi, 0                   ; Read-only
    syscall
    mov r12, rax                 ; Save file descriptor

    ; Read file contents into buffer (syscall read)
    mov rax, 0                   ; sys_read
    mov rdi, r12                 ; File descriptor
    mov rsi, buffer              ; Buffer
    mov rdx, 1000                ; Bytes to read
    syscall
    mov r13, rax                 ; Store number of bytes read

    ; Call far procedure to count blanks
    push r13                     ; Pass size of buffer
    push buffer                  ; Pass buffer pointer
    call count_blanks

    ; Call far procedure to count lines
    push r13                     ; Pass size again
    push buffer
    call count_lines

    ; Call far procedure to count character 'a'
    push r13                     ; Size
    push buffer
    push char_to_search          ; Character to search
    call count_char

    ; Exit the program (syscall exit)
    mov rax, 60
    xor rdi, rdi
    syscall

; ------------------ Program_2.asm ------------------

global count_blanks              ; Declare far procedures as global
global count_lines
global count_char

section .text

count_blanks:                    ; Count number of blank spaces in buffer
    push rbp
    mov rbp, rsp

    pop rsi                      ; Get buffer pointer from stack
    pop rcx                      ; Get number of bytes from stack
    xor rbx, rbx                 ; Blank counter = 0

.count_space_loop:
    cmp byte [rsi], ' '          ; Is current byte a space?
    jne .skip
    inc rbx                      ; Increment blank counter

.skip:
    inc rsi                      ; Move to next character
    loop .count_space_loop       ; Repeat for all bytes

    ; Store result in blank_count
    mov [blank_count], ebx

    pop rbp
    ret

count_lines:                     ; Count number of lines (newline = 0xA)
    push rbp
    mov rbp, rsp

    pop rsi                      ; Buffer pointer
    pop rcx                      ; Byte count
    xor rbx, rbx                 ; Line counter

.count_line_loop:
    cmp byte [rsi], 0xA          ; Is current byte newline?
    jne .skip_line
    inc rbx                      ; Increment line count

.skip_line:
    inc rsi
    loop .count_line_loop

    ; Store result in line_count
    mov [line_count], ebx

    pop rbp
    ret

count_char:                      ; Count number of occurrences of specific character
    push rbp
    mov rbp, rsp

    pop rdx                      ; Character to count
    pop rsi                      ; Buffer pointer
    pop rcx                      ; Byte count
    xor rbx, rbx                 ; Occurrence counter

.count_char_loop:
    cmp byte [rsi], dl           ; Compare current byte with target character
    jne .skip_char
    inc rbx                      ; Increment count if match

.skip_char:
    inc rsi
    loop .count_char_loop

    ; Store result in char_count
    mov [char_count], ebx

    pop rbp
    ret
