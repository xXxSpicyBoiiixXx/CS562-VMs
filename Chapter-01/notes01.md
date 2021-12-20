# Introduction to Virtual Machines 

As the World Wide Web grew, so did the use of many different types of computers. In the exciting new world where many different computers were being implemetned from their operating systems, programming languages, compilers, etc. There was one restricitve issue here, that the diversity that was in networked computers becomes very restricitive as we can only operate in certain parameters. In today's world, we want to move data pretty freely between on computer to another that may have different underlining systems. 

The underlying assumption is taht the hardware resources of a system are managed by a single operating system. But this isn't always the case.. So we can see the restrictive nature here.. one operating system for one set of hardware resources. Which can be kinda problematic in today's world of networked computers? 

This is where virtualization comes in play. Virtualizing probides a way of relaxing the such restrictions and increase flexibility. Which is everything we exactly want in today's world of computing. When a system is virtualized, its interface and all resources visible through the interface are mapped on the the interface and resources of a real systems actually implementing it.

So let's talk about virtual machines, which this course is about. A virtual machine adds a layer of software to a real machine to support some type other or the same architecture. 

The benefits of having operating systems running is that it can provide isolation and enhanced security wiht multiple layers of OSs on top of one another. This also add isolation from one another so to the user it can look like completely different systems. 

Despite there being differences in this or that operating system, there are some common underlying technoliogies that support them. So we'll see here in a minute. 

### Computer Architecutre 

Revisting computer architectural design, since virtual machines quite often bridge architecture boundaries, and one thing that is useful for VMs to consider is the implemetned architected infterfaces. 

### Virtual Machine Basics 

In general a VM either executes software either individual process or a full system as the same manner as the machine for which the software was developed. Virtual machines often have less performance than the real machine. 

So there is process persepective and systems perspective, so essentially there is also a process-level and system-level virtual machines. So you might have guess there is some virtualization that go here too lol.

There are process-level and system-level virtual machines. So a process virtual machien is capable of supporting an individual process. In process VMs virtualized software is referred to as the runtime, aka runtime software. From there a system virtual machine provides a complete system environment.

### Process VMs versus Systems VMs 

* Process Virtual Machines 

1. Multiprogramming 

This is the OS call interface and the user instruction set, The operating system support multiple user processes through multiprogramming, so each processor is given the illusion having the entire system to themselves. 

2. Emulators and Dynamic Binary Translators 

This is to emulate one insturction set on hardware designed for another. Source ISA to target ISA.
The most straightforward emulation method is interpretations, wherer an interpreter program executing the target ISA fetches, decodes, and emulates the execution of individual source instructions.
 
A better way of doing this is using a binary translation, This essentially means that blocks of source instructions are converted to target instructions that does the equivalen functionality. High overhead intially, but once the block translation is put in cache and repeatedly used this becomes much faster. Sometimes called dynamic binary translation.  

The overhead meantioned above can be limited with profiling. 

3. Same-ISA Binary Optimizers 

Most effective for source binaries that are relatively unoptimized to begin with. But WHY.

4. High-Level Language Virtual Machines: Platform Independence 

These are focused on minimizing hardware-specific and OS-specific features because these would compromise platform independence. 

JAVA Vm and CLI are boths based on bytecodes, that is the instructions are encode as a sequence of bytres, where each byte is a nopcode, a single-byte operand, or part of a multibyte operandl. 

Typically the memory size is conceptually unbounded, with garbage collection as an assumed part of the implementations. 

So, like in the research project, these applications are not compiled for a specfic OS, but for a set of standard libraries is provided as part of the overall execution environement. 

* System Virtual Machines 

1. The origins of a virtual machines. So basically a single host hardware platform can support mutiple guest OS environments simulataneously. 

So going from traditional mainframes with tons of users utilizing Vms today we use servers and have multiple people so they offer security with isolation. This way we partitioning majopr software systems that run concurrently on the same hardware platform. 

In system VMs, playform replication is the major feauture provided by a VMM. Guest OS or software is unware of the behind-the-scences work performed by the VMM. 

2. Implementations of System Virtual Machines

There is two ways, the first way is the VMM is first placed on the bare hardware and virtual machines fit on top. An alternative system VMM implementations builds virtualizing software on top of an existing host operatin system, this is called hosted VM. 

3. Whole System VMs: Emulation 

A whole system VM is where a complete software system, both OS and applications, is support on a host system that runs a different ISA and OS. Due to the ISAs are different, both application and OS code require emulation. The VM software executes as an application program supported by the host OS and uses no system ISA operations. 

Basically the system VM, the VM software must emulate the entire hardware environment. We have to convert the guest system ISA operations to equivalent OS calls made to the hose OS. 

Codesigned Virtual Machines: Hardware Optimization 

The goal in all VM models is to etiher support multiple OS on the same platform or the support different ISAs and OS on the same platfrom. 

But in cases of Codesigned VMs which aim to innovative ISAs and/or hardware implementations for improved perfromance, power efficiency, or both. 

### Taxonomy 

There are many types of VMs but in the broad range of things they are divided into two major types: process VMs and system VMs. 

In a process VM, it support an ABI - user instruction plus system calls 

In a system VM, it support an compolte ISA - both user and system instructions 

Look at the text... Need to break this down...


### Summary 

Chapter 2-6: Process VMs

Chapter 7-9: System VMs







