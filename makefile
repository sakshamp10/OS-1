all:
		yasm CD.asm -f elf64 -o CD.o
		gcc -no-pie CD.o