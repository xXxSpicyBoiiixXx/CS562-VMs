# Class 6
 
# TODO:  

# 1/31/2022

### Code Walk

bin/hawknest-gcc-debug -i roms/testroms/snow.new

It will drop you into a shell into default 

type questions mark for the hawknest-shell for any help.

step -- will step the cpu by n instrucitions 

for the step function it's in the mos6502-skeleton.c 

modulize the code, 

uint8_t opcode = read8(cpu, cpu->pc) ;; this is fetch 

the emu/ directory is where the emulation lives... 
ines.c is the nes drive 
main.c is the driver code

most6502.h is where the interupt status 

decode_info <--- decoding 
mos6502_step_result.... <- 

read8(mos6502_t * cpu, uint16_t addr) { 
	return membus_read(cpu-> bus addr); ! This is calling another function.
}

We don't have to worry about memory it's done 

read16(mos6502_t * cpu, uint16_t addr) 

why do we need 16? It's cause it's 16 bits wide 

buggy_read16(mos6502_t * cpu, uint16_t addr) buggy logic 

emu/shell.c <--- shell code 

peek 0
impleied hex address 
so peek 127 is really hex 127 

poke sets it to a calue so poke 127 01 will set that to $0127 : 01 

b 1000 = break point set a $1000 

dm 0 1000 and it wil dump 100 bytes 

regs for registers 

igrs raises interups 

and q to exit 

ppu is for graphics emulation 

look at the reset sequence, based on a mmeory read 

op code x80 <--- then the test will hang if you dont implement it 




