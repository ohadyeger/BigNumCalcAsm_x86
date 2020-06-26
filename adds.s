 section .data
	cf:  db	0	;carry flag
        
section .text
	 global adds

adds: 
	push	rbp
	mov	rbp,   rsp 
;==========================================================================================
        mov r8,qword [rdi];first bignum size copied
        mov r9,qword [rsi];second bignum size
    
        mov rcx,qword [rdx];ans size
        mov rdi,qword [rdi+16];first bignum char
        add rdi,r8;move pointer to last char bn1
        sub rdi,1
        mov rsi,qword [rsi+16];second bignum char
        add rsi,r9;move to last char bn2
        sub rsi,1
        mov r10,qword [rdx+16];third bignum char
        add r10,rcx;;move to last char ans
        sub r10,1
 
        my_loop:
            
            cmp r8,0;finished with all first num 
            je finished_1
            
            mov byte al,[rdi]
        not_finished_1:     
            cmp r9,0;finished with all second num
            je finished_2
            
            mov byte ah,[rsi]
        not_finished_2:
            sub al,'0'
            sub ah,'0'
            add al,ah
            add al,[cf];add carry
            mov byte [cf],0 ;zero the carry
            cmp al,10;check if there is a carry
            jl no_carry
            sub al,10
            mov byte [cf],1
            
            
            no_carry:
                add al,'0';make ascii char of the number
                mov [r10],al
                dec r8
                dec r9
                dec r10
                sub rdi,1
                sub rsi,1
 
          
 
 
 
        loop my_loop
        
        jmp end
 
   finished_1:;if the first bignum chars has ended insert 0 instead of nothing
                mov al,'0'
                add r8,1
                jmp not_finished_1
                
                
            
            
    finished_2:;if the second bignum chars had ended insert 0 instead of nothing
                mov ah,'0'
                add r9,1
                jmp not_finished_2
 
 
 
 
 end:
 mov     rsp, rbp
     pop     rbp
     ret 
