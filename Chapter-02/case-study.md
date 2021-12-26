# Shade and the Role of Emulation During Simulation 

In simulation, the objective is to study the process of performing computation, not the computation itself. 

The mapping between source PC values and target PC values is maintained in the translation lookaside buffer or TLB. 

To speed up emulation, the source program counter (VPC) and the base of the source memory image (VMEM) are permanently mapped to target registes. 

A point to the base of the TLB is also permanently mapped to a target register. 

The Shade TLB is structed in a two-dimensional array, where a source PC hashes into a row, and each row containts n(source, target) pairs. 

The lookup algorithm linearly scans the row until it has a match or until it hits the end the array. If it hits the end, it assumes there is no translation and forms one. 

TC = trade cache 

A TC is the code cache meachanism that holds translated blocks of target instructions.

# Summary 

A comparission between each of the methodlogy in this chapter. 

### Decode and Dispatch 

* Memory Requirements: Low -- There is one interpreter routine for each instruction type in the target ISA 

* Start-up Performance: Fast -- There is essentially zero start-up time because no preprocessing or translation of the source binary is required.

* Steady-state Performance: Slow -- A source instruction must be parsed each time it is emulated. FUrthermore, the source code must be fetched through the data cache, which puts a lot of pressure on the cahce, leading to performance lost. This method results in a high number of control transfers (branches).

* Code Portability: Good -- If the interpreter is written in a high level language, it is very portable. 

### Indirect Threaded Interpreter 

* Memory Requirements: Low -- More memort is needed here than the decode and dispatch method. This depends on the ISA, this could be lowered with a hybrid implementations.

* Start-up Performance: Fast -- There is essentially zero start-up, no preprocessing is required.

* Steady-state Performance: Slow -- There is several branch instructions are eliminated which makes it better than decode and dispatch, but there is high data cache usage. 

* Code Portability: Good -- This is the same reason as decode and dispatch  

### Direct Theraded Interpreter with Predecoding 

* Memory Requirements: High -- The size of predecoded memeory image is proportional to the original source memory image.

* Start-up Performance: Slow -- The source memory image must frist be interpreted in otder to discover the control flow. 

* Steady-state Performance: Medium -- 

* Code Portability: Medium -- 

### Binary Translation 

* Memory Requirements: High -- 

* Start-up Performance: Very Slow -- 

* Steady-state Perfromacne: Fast -- 

* Code Portability: Poor -- 



