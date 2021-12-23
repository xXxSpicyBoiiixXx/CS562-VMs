# Interpreting a Complex Instruction Set 

Virutal instruction sets such as Pascal P-code and Java bytecodes. 

The most commonly emulated instructions sets is not a RISC or a simple virtual ISA; rather is a CISC -- The intel IA-32

### Interpretation of the IA-32 ISA 

There is many variations for the IA-32 ISA and the CISC ISA, so we will divide instruction interpretation into two major phases. 

The first phase scans and decodes the various instruction fields. As it does so, it fills in fields of a general insturciton template. This template, constains a superset of the possible instructon options. Then there is a dispatch step that jumps to routines specialized for each instruction type. 

A decode-and-dispatch interpreter is easy but it's really slow because of generality. This is due to teh sequienital decoding first to cover all possible cases, before going to the instruction interpretation. 

An efficient interpreter utilizing make the common case fast. 

For the IA-32 ISA, there are common cases are: 

1. No pre-fix bytes
2. single-byte opcode
3. simple operand specifiers, often just registers

### Threaded Interpretation 

For a RISC, this was simple and small. 

But in the IA-32 ISA were to implement this, it would become very large.

For the CISC ISA this can be implemented. 

If predecoding and direct threaded interpretation are to be used for a CISC ISA, there's two problems. 
 
* We have a fixed-length predecoded instruction whcih is very large predecoded program. This comes to about six words per instruction. 
* The problem wiht predecoding most CISC ISAs is the need to perfrom code discovery. 

Now this could be like binary translation but there is one difference for predecoding and that is portability. 

### A high-prefromance IA-32 Intepreter



