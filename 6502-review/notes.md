# 6502 Processor 

6502 was popular in the 80s, isn't it pretty cool that Bender from futurama had a 6502 processor. 

### Registers and Flags

So we have registers such as A, X, and Y. A is typically called the accumulator, each reigster holds a single byte.

SP is the stack pointer, this value decreases everytime we add something to the stack and added if we pop something off the stack 

PC is the program counter. It's how the processor knows at what point in the program it currently is. 

### Branching 

So the 6502 has a ton of branching logic to be honest. We're introduced to BNE, BEQ, BCC, BCS 

### Addressing Modes 

Now the 6502 uses a 16 bit address bus, where we have 65536 bytes of memory avaliable to the processor. So memory addresses are represented by hex so we have $0000-$ffff. 

So there's a few ways we can name these..

* Absolute: $c000
* Zero Page: $c0
* Zero Page, X: $c0, X
* Zero Page, Y: $c0, Y
* Absolute, X and Absolute, Y: $c000, X and $c000, Y 
* Immediate: #$c0 
* Relative: $c0 (or label) 

