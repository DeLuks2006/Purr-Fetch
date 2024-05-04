.intel_syntax noprefix

.section .data
uptime_fmt:
    .asciz "(\\_/)      \033[0;33muptime:\t%s\033[0;0m\n"
shell_fmt:
    .asciz "(oᴥo)      \033[0;31mshell:\t%s\033[0;0m\n"
distro_fmt:
    .asciz "|U°U|      \033[0;35mdistro:\t%s\033[0;0m\n"
hostname_fmt:
    .asciz "|   |      \033[0;34mhostname:\t%s\033[0;0m\n"
kernel_fmt:
    .asciz "'U_U'      \033[0;36mkernel:\t%s\033[0;0m\n"
tail_str:
    .asciz "  U\n"

placeholder_str:
    .asciz "[placeholder]"

SHELL:
    .asciz "SHELL"

PRETTY_NAME:
    .asciz "PRETTY_NAME=\""

space_str:
    .asciz " "

seconds_scan_fmt:
    .asciz "%llu"

uptime_detail_fmt:
    .asciz "%02llu:%02llu:%02llu"

uptime_filepath:
    .asciz "/proc/uptime"

distro_filepath:
    .asciz "/etc/os-release"

file_permissions:
    .asciz "r"

.section .text

.extern free
.extern exit
.extern uname
.extern fopen
.extern fread
.extern memcpy
.extern fclose
.extern getenv
.extern strcat
.extern printf
.extern strstr
.extern strchr
.extern calloc
.extern strlen
.extern snprintf

# char* get_shell()
get_shell:
    lea rdi, [SHELL]
    call getenv
    ret

# char* get_hostname()
get_hostname:
    mov rdi, 400
    mov rsi, 1
    call calloc

    mov rdi, rax
    call uname

    # utsname::nodename
    add rdi, 65
    mov rax, rdi
    ret

# char* get_kernel()
get_kernel:
    push rbp
    mov rbp, rsp
    sub rsp, 8

    mov rdi, 390
    mov rsi, 1
    call calloc
    mov [rbp - 8], rax

    mov rdi, [rbp - 8]
    call uname
    call strlen

    # insert space after utsname::sysname
    add rdi, rax
    mov rsi, [space_str]
    mov [rdi], rsi

    # concatenate utsname::release level after utsname::sysname
    mov rdi, [rbp - 8]
    mov rsi, rdi
    add rsi, 130
    call strcat

    mov rax, [rbp - 8]
    add rsp, 8
    pop rbp
    ret

# char* get_uptime()
get_uptime:
    push rbp
    mov rbp, rsp
    sub rsp, 48

    # allocate fmt buffer
    mov rdi, 64
    mov rsi, 1
    call calloc
    mov [rbp - 48], rax

    # open /proc/uptime
    lea rdi, [uptime_filepath]
    lea rsi, [file_permissions]
    call fopen
    mov [rbp - 40], rax

    # parse out the number of seconds
    mov rdi, [rbp - 40]
    lea rsi, [seconds_scan_fmt]
    lea rdx, [rbp - 8]
    mov al, 0
    call fscanf

    mov rax, [rbp - 8]
    mov rcx, 0
    mov rdx, 0
    mov rbx, 3600
    div rbx

    mov [rbp - 16], rax # hours

    mov rax, rdx
    mov rcx, 0
    mov rdx, 0
    mov rbx, 60
    div rbx

    mov [rbp - 24], rax # minutes
    mov [rbp - 32], rdx # seconds

    # format into HH:MM:SS
    mov rdi, [rbp - 48]
    mov rsi, 64
    lea rdx, [uptime_detail_fmt]
    mov rcx, [rbp - 16]
    mov r8, [rbp - 24]
    mov r9, [rbp - 32]
    call snprintf

    # close /proc/uptime
    mov rdi, [rbp - 40]
    call fclose

    mov rax, [rbp - 48]
    add rsp, 48
    pop rbp
    ret

# char* get_distro()
get_distro:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    # allocate read buffer
    mov rdi, 128
    mov rsi, 1
    call calloc
    mov [rbp - 8], rax

    # allocate name buffer
    mov rdi, 64
    mov rsi, 1
    call calloc
    mov [rbp - 16], rax

    # open /etc/issue
    lea rdi, [distro_filepath]
    lea rsi, [file_permissions]
    call fopen
    mov [rbp - 24], rax

    # parse out the distro name string
    mov rdi, [rbp - 8]
    mov rsi, 128
    mov rdx, 1
    mov rcx, [rbp - 24]
    call fread

    mov rdi, [rbp - 8]
    lea rsi, [PRETTY_NAME]
    call strstr
    add rax, 13
    mov [rbp - 32], rax

    mov rdi, [rbp - 32]
    mov rsi, '"'
    call strchr

    sub rax, [rbp - 32]

    mov rdi, [rbp - 16]
    mov rsi, [rbp - 32]
    mov rdx, rax
    call memcpy

    # close /etc/issue
    mov rdi, [rbp - 24]
    call fclose

    # free read buffer
    mov rdi, [rbp - 8]
    call free

    mov rax, [rbp - 16]
    add rsp, 32
    pop rbp
    ret

# void print_fetched(char* uptime, char* shell, char* distro, char* hostname, char* kernel)
print_fetched:
    push r8
    push rcx
    push rdx
    push rsi
    push rdi

    # print uptime
    mov al, 0
    lea rdi, [uptime_fmt]
    pop rsi
    call printf

    # print shell
    mov al, 0
    lea rdi, [shell_fmt]
    pop rsi
    call printf

    # print distro name
    mov al, 0
    lea rdi, [distro_fmt]
    pop rsi
    call printf

    # print hostname/nodename
    mov al, 0
    lea rdi, [hostname_fmt]
    pop rsi
    call printf

    # print kernel info
    mov al, 0
    lea rdi, [kernel_fmt]
    pop rsi
    call printf

    # print the cat's tail
    mov al, 0
    lea rdi, [tail_str]
    call printf

    ret

.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 48

    call get_kernel
    mov [rbp - 8], rax

    call get_hostname
    mov [rbp - 16], rax

    call get_distro
    mov [rbp - 24], rax

    call get_shell
    mov [rbp - 32], rax

    call get_uptime
    mov [rbp - 40], rax

    mov rdi, [rbp - 40]
    mov rsi, [rbp - 32]
    mov rdx, [rbp - 24]
    mov rcx, [rbp - 16]
    mov r8, [rbp - 8]
    call print_fetched

    # free allocated buffers
    mov rdi, [rbp - 8]
    call free

    mov rdi, [rbp - 16]
    sub rdi, 65
    call free

    mov rdi, [rbp - 24]
    call free

    mov rdi, [rbp - 40]
    call free

    mov rax, 0
    add rsp, 48
    pop rbp
    ret