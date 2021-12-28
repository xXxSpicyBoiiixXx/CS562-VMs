# Process Virtual Machines

There is one problem that usually this has been compiled for the user's operating syste and the processor's instruction set.

The important factor of having a virtual machine is that you can have the user to run programs compiled for other systems. 

The simplest VM from the user's perspective, is to provide a virtual environment at the program or process level. 

Computer programs are compiled, distributed, and stored as executable binaries that confrom to a specific applications binary interface, or ABI. 

So what does a typical process virtual machine look like? 
* Essentially, we will take the runtime software we have and encapsulates an individual guest process, giving it the same outward appreance as a native host process. 

In addition, the guest process can interact with other guest processes as though they were running on a real machine. 

### VM implementation 

Major block performance

* The loader writes the guest code and data into a region of memory holding the guest's memory image and loads the runtime code. 





