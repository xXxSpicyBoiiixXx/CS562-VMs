# Class 8
 
# TODO: Read Chapter 5 and 6

# 2/16/2022

### Review 

Object orieneted languages 

1. Object? -- Fields and Methods

- Field: State
- Methods: Mutate the state in some way 

2. Class
- Object is instance of a class 

In java, when you state a static field, it just means that all object share that state. 

- Inheritience: Classes within classes 

- Polymorphism: can you another class for another 

### JVM (Java Virtual Machine) 

- Primitive data types: int, char, byte, short, float, double

- Objects:

- Arrays: 

- References: 

There's 3 primary areas where this stuff is stored: 

1. Global data (heap) 
2. Stack -> (operands, locals) : refs/primitive types <-- stactically determine 
3. Constant Pool 

Instruction stream for byte code since the fields are 1 byte wide, these references into constnat pool 

A constant pool is read only data. 

Stack is split into two place, locals nad operands. 

The stack for the operands has a fixed depth. 
