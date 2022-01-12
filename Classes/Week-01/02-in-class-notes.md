# Class 2
 
# TODO: New Discord Server; some ISA references; 

# 1/12/2022

Virtualization is at it's core just mapping one interface to another. 

So this boils down to state transformation: Virtualization produces equivalent transformations to the case where there's no interface mapping. 

Transformation of these states can be determined by syscalls. (We can do this with many things) 

A typical ISA has two parts, which are privileged ISA and the user ISA

### User ISA 

* add
* mul
* get cpu info 
* cycle count

This is where user programs are run 

### Privilige 

* more complicated and needed priviliage 
* OS run here 

So sometimes the user needs to request something from the privileged ISA, so the OS sits in the middle with Syscall interface. Syscalls are function calls that transforms you from the user programs. 

### Application Binary Interface (ABI) OS + user ISA 

ABI = Syscall interface and the User ISA 

### System Virtualization 

So Host OS is in priviliged mode. ( This is a host process aka a process VM) 

The VM Software that sits on top of the Host OS, where the virtualized ISA site on top of VM software. 

So on top of the virtualized ISA, you can have guest OS and guest programs. 

### OS Virtualization 

So we can virtaulized ABI running programs without an OS.  

# Computer Architecture Review 

Most CPUs follow the von Neumann Model 

- Memory 
- Processing Unit 
- Input Device 
- Output Device 
- Control Unit

### Memory 

1) For our purposes, an array of bytes. We will not be dealing with virtual memory (yet) 
2) Addressability (refes to the size of a memory location) the thing that comes in and comes out of memory 
3) Address width, how many bits are required to represent an address 

ex. x86-64 machines have 64-bit address width and are byte addressable

So how do we access memory? 
Answer: Loads and Stores

* Accomplished with help of memory unit (MMU) on the CPU
* MAR: Memory address register (address from which to laod, to which to store) 
* MDR: Memory data register (stuff to store) 

### Processing Unit 

1) Can consist of many separate functional unites
2) Simplest one is the ALU (arithmetic logic unit) 
3) Size of data worked on by ALU is the CPU's word length 
4) Today we call this the datapath of the processor 

An ALU takes in 2 operands and spits out an output 

5) Temporary Storage: Mostly commonly register (fast access, close to functional units)
6) May also be stack

### I/O

1) hardware device, keybaord, monitor, disk, etc. etc. 
2) Two moethods of I/O: polling (CPU bust waits until something is read) or interrupt-driven (devices raises a wire hot ot notify CPU) 

### Control Unit

1) Essentailly how we keep track where we are. 
2) Whwere we are: Intruction Reigster (IR). Register which hold the currently executing instruction 
3) Where to go next: Instruction Pointer (IP). Memory address of next instruction to execute (also called PC) 
4) Finite State Machine: Given current input and current instruction. where do we go next? Essentialy implemented as a lookup table. You will implement as logic in C. 
5) Controls signals to the datapath (which arithmetic op shold ALU perform, what is the sequence of operations of the various regs.) 

# ISA 

- Instruction Set Architecture 
- Interface to the HW from programmer's point of view 
- The boundary between software and hardware

### Classes of ISAs 

1) Load-Store machines: can access memory only with explict load or store operation 

2) Register-Memory machines: can access memory in other types of operation as well (Super set of load store machiens, this makes decoding much more complicated, but its easier for programmers) ) 

3) Stack Machines: all operation are performed via a LIFO stack 

Stack machines are typically used for VM 

### The instruction cycle 

1) Fetch 
2) Decode 
3) Execute ---> where state transformation happens, registers are going to change or memory is going to change or some other internal part of the processor

* Real hardware involves more stages (20 + more) but for virtual machiens we just need these three 

# Design a simple ISA 

- Assume 16 bit address width and addressability 
- 2^16 memory location, 65k (just like 6502)
- 8 GPRs

--> Load Store machines 
--> Reigister (16-bit per size) 
--> Each GPR will be 16-bit wide
--> r0...r7 
--> Load, Store, Jump, Branch, Multiple, Compare, Increment, Or, Not

Now we need to encode these instruction. 

So we have 11 insturction so we need 4 bits, we will have the op code be 4 bits. 

Put the OpCode first. Look at lecture for constructing an ISA. 

### Things we had to consider 

1) Instruction length (variable/fixed) and encoding
....

### Memory Mapped I/O

1) Instead of using processor pins for I/O devices, just have devices respond to spiecal regions of memory addresses
2) Old Machines had hardcoded regions. These days regions are programmable e.g. PCI, PICe device, standard specification 


These look like we are access memory, but this corresponds to reading and writing to some device ex. PCI, and we can change them as an Operating System. 

Ex. LD R1, $0xa700
Ex. ST R2, $0xa720

### Memory Controller Logic 

In the old days we had northbridge the hardware logic was implementing a big switch statement

word_t read(addr) { 
    if(addr >= 0xa700 && addr < 0xb700) { 
        return my_device_read (addr);
    } else { 
        return ram_read(addr); 
    }
}






