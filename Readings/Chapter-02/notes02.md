# Basic Interpretation 

We are more interersted in applying interpretation techniques to program binaries rather that high-level languages. 

There is a table in the interpreter's memory, called the cotext block, and this contains the source's information. 

A simple interpreter operates by going from one instruction to the next, reading and then modifying it. This is typically called a decode-and-dispatch interpreter. (kinda like in the research portion) 

* There is a loop, that decodes the instruction and then dispatches it to an interpretations routine based on the type of instruction.

While this process of interpretation is straightforward, the prefromance cost of interpretation is high. Even if it was in assembly lanugage. 


