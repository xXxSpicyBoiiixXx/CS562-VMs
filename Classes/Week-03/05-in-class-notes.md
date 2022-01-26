# Class 5
 
# TODO:  

# 1/26/2022

### MOS 6502 Architecture Intro

This is a 16 byte machine, so words size is one byte. 

3 8-bit registers (1 accumulator, 2 index regs for addressing modes)

Not general purpose register so 

A, X, Y 

X and Y are used for addressing. 


1) 8 bit stack pointer (SP) 
2) 8-bit status register (PSW)
3) 16-bit program counter (PC)

Little Endian (like x86) 
-- 0xdead
--> ad...de

Big Endian 
--> de...ad 

0x0000-0x0100 Zero Page
0x0100-0x0200 Stack 
0x0200-0x???? Useable RAM
0x????-0x???? I/O Space 
0x????-0xFFFF 

### Instruction Encoding 

256 possible opcodes, only 56 are actually used by the architecture 

1, 2, or 3 byte instructions

Data movement(LD/ST)

Arithmetic: ADD (with carry), SUB (with carry), DEC, INC, CMP

Logic: AND, OR, XOR, shigt/rotate 

Control Flow: branch cond, branch uncond, call subroutine, return

Other: PS manipulation, bit testing, stacks op

### Adressing Modes 

- Immediate: operand's value is in the instruction 

Pound sign '#' meanins immediate 

- Absolute: memory address included as operand in instruction 

- Implied: no operand necessary, implied by instruction 

- Indexed: Use a base register (either X or Y) and add it to the address given as operand

- Indirect: Add a level of indirection to address operand. 

- Indexed Indirect: Get target address

- Indirect Indexed: Get a target address from memory and offset it with an index register 

### Interrupts

1) IRQ - maskable interrupt. When invoked, PC and PS stored on the stack 

2) Further interrupts are disabled by the processor until handled 

3) Processor jumps to address of hnadler that is stored in 0xFFFE (2bytes). Handler (likely in ROM) returns with RTI instruction.

4) IRQ is masked/unmasked with CLI/SEI instructions

5) NMI - Nonmaskable interrupt. Same sequence, but procesor jumps to handler addr stored at 0xFFFA. This interrupt can't be disabled (power button) 

6) BRK - software interrupt. Same operation, but B flag is set in PSW stored on stack. CPU fetches from 0xFFFE (same vecotr as IRQ) 

7) RESET - System reset <-- We need to implement this as well 


READ THE BOOK "Racing the BEAM, the Atari Video computer system" 
 
 
