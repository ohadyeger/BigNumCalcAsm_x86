 section .data
	cf:  db	0	;carry flag
        
section .text
	 global subt

subt: 
	push	rbp
	mov	rbp,   rsp 
;==========================================================================================
        mov r8,qword [rdi];first bignum size copied
        mov r9,qword [rsi];second bignum size
    
        mov rcx,qword [rdx];ans size for the loop command
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
            sub al,[cf]
            
            mov byte [cf],0
            
            sub ah,'0'
            sub al,ah
            
            cmp al,0
            jge no_carry
            
        with_carry:
            add al,10
            mov byte [cf],1
            jmp no_carry
            
            
             
        no_carry:
       
            add al,'0';make ascii char of the number
            mov [r10],al;put the char in ans 
            dec r8;dec size1
            dec r9;dec size2
            dec r10
            sub rdi,1
            sub rsi,1
    
        loop my_loop
    
    jmp end

    
    
    finished_1:
                mov al,'0'
                add r8,1
                jmp not_finished_1
                
                
            
    finished_2:
                mov ah,'0'
                add r9,1
                jmp not_finished_2
       
        
    end:
     mov     rsp, rbp
     pop     rbp
     ret 