# Class 2
 
# TODO: Project 1

# 1/19/2022

### Adressing

* Page-Relative Addressing 

-- This is what 6502 procesoor going to do 

-- 4 bits for pages and 12 for offset 

The only reason we did 4 bits it matches the instruction coding 

The weakeness in thsi type of addressing is that we have to fix the instruction pages. 

LDPO1 $2 mean r0 <- mem[0x1000 + 2] 

In the 6502 processor there is a zero page addressing 

A more common addressning methodly

-- Segment based addressing

Instead of PC or register we have the offset relative to a 'special register" 

Legacy x86 has this addressing mode 

so every load and store would be 

R0 <- mem[base + offset]
LD R0, $20 <- 0x1000 + 20 

### DMA (Direct Memory Access) 

Try libvert? 

-- Maybe try vagrant file on laptop







