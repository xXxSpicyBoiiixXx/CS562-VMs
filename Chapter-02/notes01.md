# Overview 

Tons of VMs are implementated on the notion of emulation. This means that emulation happes, where the interface and functionality of one system or subsystem is emulated on to a different interface and functionality. 

This chapter is essentially about emulations but on the insturction sets.

With regards to instruction sets, emulation allows a machine implementing one instruction set, the target instruction set, to reproduce the behavior of software compiled to another instruction set, the source instruction set.

Lower overhead for virtual machines is attractive. 

Java bytecode instructions... 

We will operate with user-level instrucitons in the absence of exceptions (traps and interrupts). 

-- Picking up from yesterday 12/21/2021

Insturction set emulation can be carried out from one extreme to another. So at one end we have the technique of interpretation, while on the other we have binary translation. 

### Interpretation 

This invloves a cycle of fetching a source instruction, analyzing it, perfroming the require operations, and then fetching the next source instruction -- all in software. 

### Binary Translation 

This translates a block of source instructions to a block of target instructions, while saving the translated part of the code for repeated use. In comparison, we have that the binary translation has a bigger intial translation cost but smaller execution cost than the interpretation method. 

The choice depends on how many times on the amount of times a block of source code is expected to be executed by the guest software. 

Obivously, we want the best of both worlds, so we can take a look at threaded interpretations, which eliminated the interpreter loop corresponding to the cycle mentioned eariler. 



