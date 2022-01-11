# Control Transfer Optimizations 

So we want to reduce the long ass overhead for the emulation manager to do the whole transfer. SO we can minimize the overhead that is occuring. 

So how do we do that exactly? 

### Translation Chaining

Instead of branching to the emulation manager at the end of every translated block, the blocks can be linked directly to each other.

We replace the jump and link with a direct branch to the successor translation block. 

Thee are not ideal for indirect jumps, which have to have the emulation manager look it up just to be safe. 

### Software Indirect Jump Prediction 

In most cases, the jump target rarely changes. 

So we can implement a jump prediction, so inline caching. This is utilzing a series of cases with the most probable at top and so forth. 

This technique should be used with profiling to make more it more accuracy for indirect jump targets. 

### Shadow Stack 
So instead of going back to the mapping we will utilize this shadow stack. So this stack has a little bit more than the actual stack where we have that have the return address of the target translated code and the return address of the source binary. 

 

 
