# Predecoding and Direct Threaded Interpretation 

So, moving the a threaded interpreation ends up taking out the naively dispatch loop but we still have some sort of centralized dispatch table. 

Looking up this still requires a memory access, and it would be great if we could elimnate that. 

The notion of predecoding is to preform repeated operations just once and then reuse it each time the instruction is emulated. 

### Basic Predecoding

This invloves parasing an instruction and putting it in a form that simplifies interpretation. Predecoding extracts pieces of informations nad places them into easily accessible fields. 

### Direct Threaded Interpretation 

The portablity of indiectely threaded interpretation caused by the dispatch tables also has a performance cost, a memory looks up is required whenever the table is accessed. 

To get past this, we can put the instruction codes contatined in the intermetdiate code can be replaced with the actual addresses of the interpreter routines. 




