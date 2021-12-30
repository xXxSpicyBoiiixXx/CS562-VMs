# Process Virtual Machines

There is one problem that usually this has been compiled for the user's operating syste and the processor's instruction set.

The important factor of having a virtual machine is that you can have the user to run programs compiled for other systems. 

The simplest VM from the user's perspective, is to provide a virtual environment at the program or process level. 

Computer programs are compiled, distributed, and stored as executable binaries that confrom to a specific applications binary interface, or ABI. 

So what does a typical process virtual machine look like? 
* Essentially, we will take the runtime software we have and encapsulates an individual guest process, giving it the same outward appreance as a native host process. 

In addition, the guest process can interact with other guest processes as though they were running on a real machine. 

### VM implementation 

So let's look at the major componenets of a process VM.

1) The loaders writes the guest code and data into a region of memory holding the guest's memory image and loads the runtime, it is important to note that this is all data because source code is not directly executed. 

2) The control goes to the initialization block, where memory space for the code is cached for the emulation process. This usually invokes the host OS to establish singal handlers for all trap conditions that can occur. 

3) The emulation engine uses interpretation and/or binary translation to emulate the guest instructions. 

4) The translated target code is held in the code cache. This is an executable code where emulation is in progress. 

5) Due to the limited size of code cache, we have the code cache manager is kinda responsible for deciding which translation should be flushed out as they come and go here and there depending on what new translation needs to be added. 

6) A profile database contains dynamically collected program information that is used to guide optimization during the translation process. 

7) As emulation proceeds and the guest program a system call, the OS call emulator will translate the OS call into an appropriate call to the host OS where the OS will understand. 

8) We handle traps when we exedcute interpreter or translated instructions. The runtime does this with the exception emulator. 

9) Side tables are used for exception model with respect to the source ISA. 

More will be discussed in later chapters ~~ 
 




