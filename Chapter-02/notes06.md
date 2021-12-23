# Binary Translation

The process of converting the source binary program into a target binary program. 

State mapping is essentially a form of virtualization from guest-to-host state mapping.

# Code Discovery and Dynamic Translation

We could predecode or binary translate a program in it entirety before beginning emulation, this is static predecoding or static translation. 

This might be difficult or impossible to implement. 

* If we hit an indirect jump: The register isn't assigned a value until run time. 

RISC has a fixed-length encodings, while CISC ISAs e.g. IA-32 have a variable btye boundary. 

Code Discovery becomes very difficult due to the varaible legth instruction sets in such ISAs 

### Code location problems 

TPC - Target Program Counter 
SPC - Source Program Coutner

The basic idea here is that we want to map SPC to TPC. 

### Incremental Predecoding and Translation 

We want to translate the binary while the program is oprtating on actualy input data dynamically and to predecode new sections of c ode incrementally as the program reaches them. 

Emulation manager, is part of the run time support 

The run time support is interpreter and binary translator, where the interpreter can be either decode-and-dispatch and simple threded interpreter. The intepreter operates on the original source binary code. 

Memory can be quite large for translated code, so we can use code cache to see what memory is used more often. So code cache is essentially holding more recently used blocks of translate code. 

Map Table: SPC for a block of souce code with the TPC for the corresponding block of translate code. 
(Typically implemented as a hash table.) 

Dynamic Basic Block: Alway begins at the instruction executed immediately after a branch or jump, follws the sequential instruction stream, and end with the next branch of jump. 

Static Basic Block: Contains a sequence with a single entry point and a single exit point. Begin and end at all branch/jump instructions and branch/jump targets. 

Dynamic basic block, often larger than static basic blocks are  determind by the actual flow of control at run time. Dynamic basic blocks terminate at the first conditional branch is encountered. 

The same static basic block can belong to multiple dynamic basic blocks 

Translation will have on one dynamic basic block at a time. 








