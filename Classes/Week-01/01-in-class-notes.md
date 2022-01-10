# Class 1
 
# TODO: Prelim project, look over 6502, and reread chapter 1

# 1/10/2022

### Introductions 

Four Areas for Projects: 

1) Emulations -- 6502: Can play NES games on it

2) High Level Langauge Virtual Machine: JVM machines 

3) Barebones: Full system hypervisor, with KVM 

4) Lightweight version of Docker. 

Replace the last two projects with open end research project. 

All projects will be coded in C, closer to the real world applications. 

Projects, we will be using Vagrant files. 

Just a reminder: No homeworks, No exam, projects and research. Take this seriously. 

### Introduction to VMs 

What is virtualization? 
* Something different from something -> Software thinks it's running on something different?
* Emulation: Presetning fake HW
* Different behavior

What is virtualized by OS? 
* Address Space: Illusion of full access to memory, uniform interface 
* CPU: Illusion of sole ownership of CPU

So, we still have a cloudy judgement on virtualization.

1) Illusion of a phyiscal resource (presnted logically) 
    * Memory 
    * CPU 
    * GPU 
    * Entire Machine 

2) Virtualize a Resouce: Present an interface. 
    * Virtualized Memory: Architected loads/stores of a machine. 
    * Virtualized CPU: ISA -> "equivalence" 
    * Virtualization Platform: Buses, Chipsets, Devices, etc. 

So a common theme is interface and we must adhere to the interface. 

### Mechanisms for implementing a software interface 

1) Emulation: Behavioral equivalence
    * Programs behave the same way 

2) Simulation: equivalence + emulation of interal components 
    
So both of these are techniques to implement virtualization

In some cases, we can do both. If we have hardware support we don't need either because we can run code natively while still virtualizing it. 

### Taxonomy and Vocab 

1) Language VMs: An abstract machine is being virtualized
    * The interface is a fake ISA 
    * Java Virtual Machine --> Java --> Java bytecode (virtaul ISA)     
    * Typically used to implementing programming languages 

2) Full System VMs: Virtualizing a platform 
    * Virtual Box, VMware, HyperV, etc.
    * The goal is to mimic the whole system 

3) Process VMs: VM software runs as a process on some host machine. 
    * JVM, QEMU, Parallels, libvirt, etc. 

4) Hypervisors/Virtual Machines Monitors (VMMs) 
    * Lower-level OS, this requires some system software support 
    * OS/360 (Specialized OS and could support multiple VMs on top of it) 

   
