#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: calc

# Tool invocations
# Executable "hello" depends on the files hello.o and run.o.
calc: calc.o adds.o subt.o mult.o divide2.o
	gcc -g -Wall -o calc calc.o adds.o subt.o mult.o divide2.o

# Depends on the source and header files
calc.o: stack2.c
	gcc -g -Wall -c -o calc.o stack2.c 
adds.o: adds.s
	nasm -g -f elf64 -w+all -o adds.o adds.s 
subt.o: subt.s
	nasm -g -f elf64 -w+all -o subt.o subt.s
mult.o: mult.s
	nasm -g -f elf64 -w+all -o mult.o mult.s
divide2.o: divide2.s
	nasm -g -f elf64 -w+all -o divide2.o divide2.s
	
#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o calc
