
 section .data

        
section .text
	 global divide_by_2


;algorithm to divide by 2
divide_by_2:
  mov rax, QWORD  [rdi]
  cmp rax, 1
  je .first
  mov edx, 0
  mov r8d, 0
  test rax, rax
  jg .L17
  jmp .second
.first:
  mov rax, QWORD  [rdi+16]
  movsx eax, BYTE  [rax]
  sub eax, 48
  mov rdx, QWORD  [rsi+16]
  mov ecx, eax
  shr ecx, 31
  add eax, ecx
  sar eax,1
  add eax, 48
  mov BYTE  [rdx], al
  mov rax, QWORD  [rsi+16]
  mov BYTE  [rax+1], 0
  ret
.L17:
  movsx r9, r8d
  mov rcx, QWORD  [rdi+16]
  movsx eax, BYTE  [rcx+r9]
  sub eax, 48
  test dl, 1
  jne .third
  cmp eax, 1
  ja .forth
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 48
.forth:
  lea edx, [rax-2]
  cmp edx, 1
  ja .fifth
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 49
.fifth:
  lea edx, [rax-4]
  cmp edx, 1
  ja .six
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 50
.six:
  lea edx, [rax-6]
  cmp edx, 1
  ja .sev
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 51
.sev:
  sub eax, 8
  cmp eax, 1
  ja .nu8
  mov rax, QWORD  [rsi+16]
  mov BYTE  [rax+r9], 52
  jmp .nu8
.third:
  cmp eax, 1
  ja .nu9
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 53
.nu9:
  lea edx, [rax-2]
  cmp edx, 1
  ja .nu10
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 54
.nu10:
  lea edx, [rax-4]
  cmp edx, 1
  ja .nu11
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 55
.nu11:
  lea edx, [rax-6]
  cmp edx, 1
  ja .nu12
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+r9], 56
.nu12:
  sub eax, 8
  cmp eax, 1
  ja .nu8
  mov rax, QWORD  [rsi+16]
  mov BYTE  [rax+r9], 57
.nu8:
  mov rdx, QWORD  [rdi+16]
  movsx edx, BYTE  [rdx+r9]
  sub edx, 48
  add r8d, 1
  movsx rcx, r8d
  cmp rcx, QWORD  [rdi]
  jl .L17
.second:
  movsx rax, r8d
  mov rdx, QWORD  [rsi+16]
  mov BYTE  [rdx+rax], 0
  ret