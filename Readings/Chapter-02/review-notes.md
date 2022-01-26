# Reading 2.1-2.3 

This was basically the difference between different types of interpretation 

The main thing here is to either fetch-decode or threaded interpretations. 

In a fetch-decode we fetch some code and then decoded it while a threaded interpretation is an optimazation measurement where we can have this indirectly or directly. 

With an indirect interpretation we get that code portability but in the cost of performance but with direct interpretation we get beefier code but we get better performance. 

# Reading 2.5-2.10

### Binary Translation 

With binary translation we significantly increase performance by mapping each individual source binary instruction to it's own customized target code. 

Mapping source registers to target registers is an example of guest-to-host state mapping. 

### Code Discovery and Dynamic Translation 

Static predecoding or static translation is difficult in many cases for example when there is a jump.

### The Code Location Problem 

During emulation we can get the translated code with a target program counter, which is different from the source program counter. So we need to map the SPC address to a TPC address. 

### Incremental Predecoding and Translation 

The emulation manager has a high-level control which is part of runtime 


