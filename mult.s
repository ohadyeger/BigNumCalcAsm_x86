 section .data

        
section .text
	 global mult
	 extern malloc

mult: 
  push r15
  push r14
  push r13
  push r12
  push rbp
  push rbx
  sub rsp, 40
  mov QWORD [rsp+16], rdx
  mov r15, QWORD [rdi]
  mov rax, QWORD [rsi]
  mov r14, rax
  lea rbp, [r15+rax]
  mov QWORD [rdx], rbp
  mov r12, QWORD [rdi+16]
  mov rbx, QWORD [rsi+16]
  lea rdi, [rbp+1]
  call malloc
  mov r10, rax
  mov BYTE [rax+rbp], 0
  test rbp, rbp
  jle .c_size_check
  mov eax, 0
  
.init_arr:                          ;;initiate digit array with
  movsx rdx, eax
  mov BYTE [r10+rdx], 0
  add eax, 1
  movsx rdx, eax
  cmp rbp, rdx
  jg .init_arr
  jmp .2nd_loop
  
.add_zero_loop:                     ;;when done calc, add '0' to every digit
  mov rbp, QWORD [rsp+24]
  test rbp, rbp
  jg .reset_eax
  jmp .flip_arr
  
.calc_start:                        ;;start multiplication
  mov r8d, 0
  mov rax, r14
  mov edi, r14d
  lea r9d, [r14-1]
  sub edi, 2
  mov DWORD [rsp+12], edi
  mov QWORD [rsp+24], rbp
  mov rbp, rax
  
.calc_help:                         ;;mult help function
  movsx rax, r15d
  movzx r11d, BYTE [r12+rax]
  sub r11d, 48
  test r9d, r9d
  js .calc_loop_dec
  mov edi, 0
  mov edx, 0
  movsx r11d, r11b
  
.calculate:                         ;;main calculation loop
  mov r13d, r8d
  lea esi, [r8+rdi]
  movsx rsi, esi
  add rsi, r10
  mov eax, r9d
  sub eax, edi
  cdqe
  movzx ecx, BYTE [rbx+rax]
  sub ecx, 48
  movsx ecx, cl
  imul ecx, r11d
  movsx eax, BYTE [rsi]
  add ecx, eax
  add ecx, edx
  mov eax, ecx
  mov r14d, 1717986919                  ;;constant for dividing by 10
  imul r14d
  sar edx, 2
  mov eax, ecx
  sar eax, 31
  sub edx, eax
  lea eax, [rdx+rdx*4]
  add eax, eax
  sub ecx, eax
  mov BYTE [rsi], cl
  add edi, 1
  cmp r9d, edi
  jns .calculate
  test edx, edx
  jle .calc_loop_dec
  cmp DWORD [rsp+12], -1
  mov eax, 1
  cmovge eax, ebp
  add r13d, eax
  movsx r13, r13d
  add BYTE [r10+r13], dl
  
.calc_loop_dec:                         ;;dec index and continue loop
  add r8d, 1
  sub r15d, 1
  jns .calc_help
  jmp .add_zero_loop
  
.flip_arr:                              ;;when calculation done, mirror the digit array to fit
  mov rax, rbp
  shr rax, 63
  add rax, rbp
  sar rax, 1
  mov r8, rax
  test rax, rax
  jle .assign_ans
  mov ecx, 0
  mov edx, 0
  jmp .flip_arr_help
  
.reset_eax:
  mov eax, 0
  
.add_zero:                              ;;adds '0' to element inside the loop
  movsx rdx, eax
  add BYTE [r10+rdx], 48
  add eax, 1
  movsx rdx, eax
  cmp rbp, rdx
  jg .add_zero
  jmp .flip_arr
  
.flip_arr_help:                        ;; main flip method
  movsx rax, edx    
  add rax, r10
  movzx esi, BYTE [rax]
  mov rbx, rbp
  sub rbx, rcx
  lea rcx, [r10-1+rbx]
  movzx edi, BYTE [rcx]
  mov BYTE [rax], dil
  mov BYTE [rcx], sil
  add edx, 1
  movsx rcx, edx
  cmp rcx, r8
  jl .flip_arr_help
  
.assign_ans:                         ;;set new digit array to c
  mov rax, QWORD [rsp+16]
  mov QWORD [rax+16], r10
  jmp .end
  
.c_size_check:                      ;;check if calculation is needed
  sub r15d, 1
  jns .calc_start
  jmp .flip_arr
  
.2nd_loop:                          ;;start looping over second multiple
  sub r15d, 1
  jns .calc_start
  jmp .reset_eax
  
.end:
  add rsp, 40
  pop rbx
  pop rbp
  pop r12
  pop r13
  pop r14
  pop r15
  ret