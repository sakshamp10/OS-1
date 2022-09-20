all:
		yasm Question2.asm -f elf64 -o Question2.o
		gcc -no-pie Question2.o