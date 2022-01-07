# State Mapping 
When we describe state mapping, we do so in the term of resource mapping, e.g. the memory and associated memory that actually contain the state. 

So a VM views a memory as a logical address space supported by the host machine. When we talk about memory in this context, we are referring to the logical address space not the implemented real memory. 

In some situations it might be convenitent to map guest memory onto files system storage rather than the host's main memory. 

Overall the state mappings has huge impacts on the overall emulation techniques used on the resulting performance that is achieved. 

### Register Mapping 
If the number of guest ISA registers is less than the number of host ISA registers, than we could map all for the duration of the emulation. 

If they are roughly equal, it would be theortically possible but might be troublesome. For instance in the case of interpretation or if the runtime does dynamic optimization. So for instance, if all registers are in use by the emulation process than additional register are just not avalible. 
The last case, where we have that the guest registers are larger than the number of host reigster, then some of the host registers must be mapped to a register context block in the host's memory. This responsiblity is dumped onto the host registers as emulation proceeds. 

### Memory Address Space Memory 
The runtime has to map the guest's address space to the host's address space. This is also know as a translation table. 

So the higher the flecivle the more software intensive it would be for a general rule of thumb

So the most flexible way is the translation table between guest application address space and host application address space. 

CODE TO ANALYZE... 
////////////////////////////////////////////
// Load instruction with software mapping //
////////////////////////////////////////////

Initially, r1 holds souce address 
	   r30 holds base address of translation table 

srwi r29, r1, 16 	; shift r1 right by 16
slwi r29, r29, 2	; convery to a byte address in our table 
lwzx r29, r29, r30	; load block location in host memory 
slwi r28, r1, 16	; shift left/right to zero out source block num
srwi r28, r28, 16	;
slwi r29, r28, r29	; shift up target block number 
or   r29, r28, r29	; form address 
lwz  r2, 0(r29) 	; do load

///////////////////////////////////////////




