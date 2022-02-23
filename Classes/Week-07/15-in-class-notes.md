# Class 10
 
# TODO: Hawkbeans

# 2/23/2022

### JVM 

These objects are mananged by the JVM, so there is no malloc or free needed for the heap, so this is the notion of managed memory.

A mananged langage takes care of memory 

Garbage collection 
-- memory management is hard 

In C is not straight forward for allocations. 

Garbage collection takes care of memory leakage. 

ref counting (kind of) manual
- The basic idea is the allocator gives back memory with a count. 

We need some algorithm to walk through the heap and looks through these objects, and model these objects on the heap as a graph. There is something called the root set which are always in the heap no matter what. 

In java, the root set has
1) stack <--- Important, referencing everything in the program 
2) constant pool 
3) static objects 

When something is not used we free it or kill it, so we are removing it from the heap. 

Modeling objects in our graph and figure out what is no longer is reference and deallocating things from the heap.

Have I seen it table. 

Graph traversal ---> Comparison and collection of garbage

This is mark-and-sweep

Precise GC is known about being one type or another, putting a tag. Prepan a few bits to tell you what type of data it is, which we could tell what is a referecne is. 

Boehm GC for C and C++ 


