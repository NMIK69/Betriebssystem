CFLAGS=-ffreestanding -m32 -g
CC=~/opt/cross/bin/i686-elf-gcc
LD=~/opt/cross/bin/i686-elf-ld

CSRCS=$(wildcard kernel/*.c drivers/*.c utils/*.c cpu/*.c)
OBJ=$(patsubst %.c,%.o,$(CSRCS))




all: mfos.bin
	
# put image together
mfos.bin: boot.bin kernel.bin empty_end.bin
	cat $^ > mfos.bin
	cat $^ > os-image/mfos.bin


boot.bin: boot_sector/boot.asm
	nasm -f bin $< -o boot.bin


kernel.bin: kernel_entry.o interrupt.o $(OBJ)
	$(LD) -o $@ -Ttext 0x7ef0 $^ --oformat binary


empty_end.bin: kernel/empty_end.asm
	nasm -f bin $< -o $@

kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf -o $@

interrupt.o: cpu/interrupt.asm
	nasm $< -f elf -o $@

%.o:%.asm
	nasm $< -f elf -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -fr *.bin *.o
	rm -fr kernel/*.o
	rm -fr drivers/*.o
	rm -fr cpu/*.o
	rm -fr utils/*.o
	

run:
	qemu-system-x86_64 -drive format=raw,file=mfos.bin,index=0,if=floppy -m 128M