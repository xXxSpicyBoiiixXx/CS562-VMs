# Class 4
 
# TODO:  

# 1/24/2022

### Emulation

An emulation: implement an interface for one machine on a different machine. 

Architected - State. really trying to emulate the system but we don't really care about the internals.

For architected state we care about memory and the other state 

### Memory 
1) Code
2) Data
3) Stack 
4) Heap 
5.... BIOS 

### Other State 
1) Register 
2) Control Register 
3) Conditional Codes 
4) PC 

#define HOW_MANY_REGS 8
struct machine_state { 
    uint8_t pc; 

    uint8_t regs[HOW_MANY_REGS];

    uint32_t control_the_world;

    uint8_t cc; 

    uint8_t sp; 

    uint8_t ram[RAM_SIZE]; 
    
}

// PUSH - pushes first reg onto stuck
fun push(struct machine_state * state) { 
    
    state -> ram[state -> sp] = state -> regs[0];
    state -> sp--; 
}

// POP - removes item from stack, store it in first regs inc stack pointer 
fun pop(strcut machine_state * state) { 
    state -> sp++; 
    state -> regs[0] = state -> ram[state -> sp];
}

// special op that writes a 1 to memoty location 0x2b 
fun foo(struct machine_state * state) { 
    state -> ram [0x2b] = 1; 
}


read_ram 

read_ram8

read_buggy 

static void handle_add () { 
        // handle the add
        regs[0] = regs[1] + regs[2]; 
        
        op = decode(get_pc());
        handler_table[op](); 
}

static void handle_sub () { 
        // handle the sub 
        regs[0] = regs[1] - regs[2]
        op = decode(get_pc());
        handler_table[op]();
}


handler_table = {&handle_add, &handle_sub///_ 





// assume state is initialized already
fun interp(struct machine_state * state ) { 
    
    while (1) { 
        
        if(interrupt_fired() || halted()) { 
            // special logic
        }


        // fetch 
        instr = read_ram(state -> pc);         
        
        // decode 
        op = decode(instr); // op is the opcode 

        // dispatch (execute) 
        switch (op) { 
        
        case ADD_INSTR:
            // code to handle add..  
        case SUB_INSTR:
            // code handle sub...
        case POP_INSTR:
        ..
        case CASE_COSINE:
        case PARMESAN:
        
        defualt: 
                printf("BAd instruction\n");
        }

        // Instead of having siwtch statment just have 
        handler_table[op]();

        // Suppose we wanted to get ride of the handler_table[op]() 
        // We could do a threaded interpretation  

    }
}


fun interp() { 
    instr = fetch_instr(); 
    
    op = decode(instr);

    switch(op) { 
        case A: 
          // do add logic 
          goto *get_pc();   
        case B:
    }       
    
}


PREDECODING 
- take densely endcoded program, and splay it out into a sparse representation 

| ADD 
| opcode | 1 bit type | modRM | src reg | dst reg ... | 

strcut instruction { 
    void (*handler)(); 
    uint8_t opcode; 
    uint8_t type; 
    uint8_t modRM;
    uint8_t src_reg; 
    uint8_t dst_reg; 
    ... 
    uint8_t branch_type;
}


// translated program (intermediate represenation, or IR)
struct instruction predecoded_instrs[MAX]; // pointed to by a new PC (target PC, TPC) 

for some sequence of real instruction: 
{   instr = * pc++; 
    struct instruction * i malloc(sizeof...); 
    decode(i, instr); // fils in the above insturction strcut
    predecoded_instrs[i] =  instrs 
}

fun decode (pc, instruction * i) { 
    instruction_encoded = read_ram(pc);

    i -> opcode = OP_ADD; 
    i -> type = TYPE_ADD_IMMEDIATE;
    i -> src_reg = 0; 

    i -> handler = &handle_add; 
}

execute the instruction { 
    instr = fetch(tpc);
    switch(instr -> opcode); 
}

fun handle_add () { 
    // do the add logic 
    instr* i = read_ram(pc); 
    i -> handler(); 
    
}

 
