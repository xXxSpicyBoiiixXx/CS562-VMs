# Compatibility

The main issue is compatibility, how well does the guest's behavior is emulated on the host platform, compared with its behavior on its native platform. 

Of course, if the processes were identical that would be easy, but compatibility might not be be needed for a process virtual machine. 

Compatibility is a matter of correct functioning, not how fast the function is performed. So we exclude anything with performance when talking about compatibility between source and host. 

Even though performance isn't part of the definition in compatibility, it's a pretty big part. 

### Levels of Compatibility

To have 100% compatibility would be a very strict form of the definition but we can say that VMs that have this qulity is intrinsic compatibility. Another term to describe this is complete transparency. When using using such a system, everything will act like the native machine. This usual the case for microprocessors but is not the case in process VM. 

So for process VMs, we need extrinsic compatibilty. This type of compatibility may hold for some programs run on a virtual machine but not for others. So with this extrinsic compatibility comes the requirements of clearly stating the external properties that must hold in order for compatibility to be achieved. 

### A Compatibility Framework 

Either level of compatibiltiy is difficult problem. 

* The mapping of state between the guest and the host 
* The operations that transform the state in the guest and the host 

Application program performs operations on state in two ways by executing instructions: 
1) User ISA 
2) OS calls 

-- State Mapping 
Basically mapping from guest to host states are equivalent.

-- Operations 
The points where control is transferred between the user code and teh OS are key for compatibility framework. 

We do one-to-one mapping where control is transfered between user intructions and the OS. 

-- Sufficient Compatibility Conditions 
1) The point of control transfer fomr emuilating user instructions to the OS, the guest state is equivalent to the hose state. We also make the assumption that all the user-managed state may be exposed to the outsdie world when the OS takes over.  
2) At the point of control tansfer back to the user instructions, the guest state is equivalent to the host state still, given the mapping we have. The runtime and the host OS should make modifications to the guest state and the guest's native platform. 

### Discussion 
The important factor is that we make these assumptions where such a compatibile framework, we can easily identify compatibility issues when they arise and then evaluate their significance. 

To acheive intrinsic compatibility the conditions just stated must hold for all programs and data. In contrast, the extrinsic compatibility, conditions are imposed on a subset of guest software. 

Extrinsic compatibilits is only achieved for processes that don't exceed a certain size since it can't be more than the native platform. 

### Implementation Dependences





