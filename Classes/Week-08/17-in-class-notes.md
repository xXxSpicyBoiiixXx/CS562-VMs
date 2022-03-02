# Class ~~
 
# TODO: Hawkbeans

# 03/02/2022

### System VMs 

- Infrasturcutre Consolidation 

- Unified Enivormenets

- Security Reasons 

- HW/local level Software Developemnt 

- Run multiple OSs 

How do we do this? 

### State Mapping 

Guest -> host resources 
e.g. disk, memory, register, etc. 

Solution 1: Indirection (Indirect pointers) 
--> Base + Offset Approach

Solution 2: Shadow State 

### Control of the system 

--> Can[t give full access to guests. 
--> Use trap and emulate 
1) We can either emulate everything (binary translation) 
2) Direct execution (limited) 

Same ISA virtualization -->
1) Efficiecny
2) Resrouces 
3) Equivalence --> behavior equivalene is roughly safe as the native 
This impleies: Trap all senstive insturcitons 

A sensitive instruction: relies on context or changes configuration 

When we exit a guest we have to do a state save. 


x86: behavior-sensitive instruction: dpends on the configuration of the machine. 

popfl (pop flags) 


