#include <mos6502/handlers.h>
#include <rc.h>
#include <base.h>
#include <membus.h>
#include <timekeeper.h>
#include <stdio.h>
#include <mos6502/vmcall.h>
#include <mos6502/mos6502.h>


// From original file
static inline uint8_t
read8 (mos6502_t * cpu, uint16_t addr)
{
	return membus_read(cpu->bus, addr);
}

static inline void
write8 (mos6502_t * cpu, uint16_t addr, uint8_t val)
{
	membus_write(cpu->bus, addr, val);
}

static inline uint16_t
read16 (mos6502_t * cpu, uint16_t addr)
{
	uint16_t lo = (uint16_t)read8(cpu, addr);
	uint16_t hi = (uint16_t)read8(cpu, addr + 1);
	uint16_t val = lo | (uint16_t)(hi << 8);
	return val;
}

static inline uint16_t
buggy_read16 (mos6502_t * cpu, uint16_t addr)
{
	uint16_t first = addr;
    uint16_t msb = addr & 0xff00;
    uint16_t lsb = ((addr & 0xff) == 0xff) ? 0 : ((addr & 0xff) + 1);
	uint16_t secnd = msb | lsb;
	uint16_t lo = (uint16_t)read8(cpu, first);
	uint16_t hi = (uint16_t)read8(cpu, secnd);
	uint16_t val = (uint16_t)(hi << 8) | lo;
	return val;
}

// add with carry family 
void ADC_handler(mos6502_t *cpu) { 
    uint8_t operand = read8(cpu, cpu-> pc + (uint8_t)1);
    uint16_t value = cpu -> a + operand; 

   if(cpu -> p.c) { 
        value = value + 1; 
   } else { 
     value = value; 
   }
    if(value > 0xFF) { 
        if((value >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = value & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = value & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x02;


   }

void ADC_ZP_handler(mos6502_t *cpu) {
    uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
    uint8_t value = read8(cpu, (uint16_t)operand); 

    uint16_t result = cpu -> a + value; 
    
    if(cpu -> p.c) { 
        result = result + 1; 
    } else { 
        result = result; 
    }

if(result > 0xFF) { 
        if((result >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = result & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = result & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x02;

}

void ADC_ZPX_handler(mos6502_t * cpu) { 
    uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
    uint8_t value = read8(cpu, (uint16_t)(operand + cpu -> x)); 

    uint16_t result = cpu -> a + value; 
    
    if(cpu -> p.c) { 
        result = result + 1; 
    } else { 
        result = result; 
    }

if(result > 0xFF) { 
        if((result >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = result & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = result & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x02;



}


void ADC_ABS_handler(mos6502_t *cpu) {
      uint16_t operand = read8(cpu, cpu -> pc + (uint16_t)1); 
    uint8_t value = read8(cpu, operand); 

    uint16_t result = cpu -> a + value; 
    
    if(cpu -> p.c) { 
        result = result + 1; 
    } else { 
        result = result; 
    }

if(result > 0xFF) { 
        if((result >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = result & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = result & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x03;

}

void ADC_ABSX_handler(mos6502_t *cpu) { 
    uint16_t operand = read8(cpu, cpu -> pc + (uint16_t)1); 
    uint8_t value = read8(cpu, operand + cpu -> x); 

    uint16_t result = cpu -> a + value; 
    
    if(cpu -> p.c) { 
        result = result + 1; 
    } else { 
        result = result; 
    }

if(result > 0xFF) { 
        if((result >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = result & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = result & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x03;  

}

void ADC_ABSY_handler(mos6502_t *cpu) { 
    uint16_t operand = read8(cpu, cpu -> pc + (uint16_t)1); 
    uint8_t value = read8(cpu, operand + cpu -> y); 

    uint16_t result = cpu -> a + value; 
    
    if(cpu -> p.c) { 
        result = result + 1; 
    } else { 
        result = result; 
    }

if(result > 0xFF) { 
        if((result >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = result & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = result & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x03;  

}

void ADC_IDX_IDR_handler(mos6502_t *cpu) {
    uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
    uint8_t lo = operand + cpu -> x; 
    uint8_t hi = lo + 1; 

    uint16_t addr = (hi << 8) | lo; 

    uint8_t value = read8(cpu, addr); 

    uint16_t result = cpu -> a + value; 
    
    if(cpu -> p.c) { 
        result = result + 1; 
    } else { 
        result = result; 
    }

if(result > 0xFF) { 
        if((result >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = result & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = result & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x02;



}

void ADC_IDR_IDY_handler(mos6502_t * cpu) { 

    uint8_t first = read8(cpu, cpu -> pc + (uint8_t)1); 
    uint8_t second = first + 1;

    uint8_t lo = read8(cpu, first + cpu -> y); 
    uint8_t hi = read8(cpu, second); 

    uint16_t addr = (hi << 8) | lo; 

    uint8_t value = read8(cpu, addr); 

    uint16_t result = cpu -> a + value; 
    
    if(cpu -> p.c) { 
        result = result + 1; 
    } else { 
        result = result; 
    }

if(result > 0xFF) { 
        if((result >> 8) & 0x01) { 
            cpu -> p.c = 1;
        } else { 
            cpu->p.c = 0;
        }
        cpu -> p.v = 1; 
        cpu -> a = result & 0xFF; 
   } else { 
        cpu -> p.c = 0; 
        cpu -> a = result & 0xFF;
   }

   if(cpu-> a >> 7 & 0x01) { 
        cpu -> p.n = 1;
   } else { 
        cpu -> p.n = 0;
   }

   if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
   } else { 
        cpu -> p.z = 0;
   }

   cpu -> pc += (uint8_t)0x02;

}

// and with accumulator
void AND_handler(mos6502_t *cpu) { 
 uint8_t operand = read8(cpu, (cpu -> pc) + (uint8_t)1);
    uint8_t result = (cpu -> a & operand); 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
    }
    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    } 
    cpu -> pc += (uint8_t)0x02; 

   

}

void AND_ZP_handler(mos6502_t *cpu) {
 uint8_t operand = read8(cpu, (cpu -> pc) + (uint8_t)1);
 uint8_t value = read8(cpu, (uint16_t)operand); 

 uint8_t result = (cpu -> a & value); 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
    } 

    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    } 

    cpu -> pc += (uint8_t)0x02; 

}


void AND_ZPX_handler(mos6502_t *cpu) {
 uint8_t operand = read8(cpu, (cpu -> pc) + (uint8_t)1);
 uint8_t value = read8(cpu, (uint16_t)(operand + cpu -> x)); 

 uint8_t result = (value) & cpu -> a; 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
    }

    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    } 

    cpu -> pc += (uint8_t)0x03; 

}


void AND_ABS_handler(mos6502_t *cpu) {
 uint8_t operand = read8(cpu, (cpu -> pc) + (uint8_t)1);
 uint8_t value = read8(cpu, (uint16_t)(operand + cpu -> x)); 

 uint8_t result = (value) & cpu -> a; 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
    }

    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    } 

    cpu -> pc += (uint8_t)0x03; 

}


void AND_ABSX_handler(mos6502_t *cpu) {
 uint16_t operand = read16(cpu, cpu -> pc + 1);
 uint8_t value = read8(cpu, operand + cpu -> x); 

 uint8_t result = (value) & cpu -> a; 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
    } 

    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    }

    cpu -> pc += (uint8_t)0x03; 

}


void AND_ABSY_handler(mos6502_t *cpu) {
 uint16_t operand = read16(cpu, cpu -> pc + 1);
 uint8_t value = read8(cpu, operand + cpu -> y); 

 uint8_t result = (value) & cpu -> a; 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
  }

    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    } 

    cpu -> pc += (uint8_t)0x03; 

}


void AND_IDX_IDR_handler(mos6502_t *cpu) {
 uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1);
 
 uint8_t lo = operand + cpu -> x;
 uint8_t hi = lo + 1; 

 uint16_t addr = (hi << 8) | lo;  
 uint8_t value = read8(cpu, addr); 

 uint8_t result = (value) & cpu -> a; 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
    } 

    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    } 

    cpu -> pc += (uint8_t)0x02; 

}


void AND_IDR_IDY_handler(mos6502_t *cpu) {
 
 uint8_t first = read8(cpu, cpu -> pc + 1); 
 uint8_t second = first + 1; 
   
 //uint8_t operand = read8(cpu, cpu -> pc + 1);

 uint8_t lo = read8(cpu, first + cpu -> y);
 uint8_t hi = read8(cpu, second);

 uint16_t addr = (hi << 8) | lo;  
 uint8_t value = (uint16_t)read8(cpu, addr); 

 uint8_t result = (value) & cpu -> a; 
    
    cpu -> a = result; 
    
    if(!result) { 
        cpu -> p.z = 1; 
    } 

    if((result >> 7) & 0x1) { 
        cpu -> p.n = 1; 
    } 

    cpu -> pc += (uint8_t)0x02; 

}


// arithmetic shift left
void ASL_handler(mos6502_t *cpu) {
    cpu -> p.c = (cpu -> a >> 7); 
    cpu -> a = (cpu -> a << 1);
    
    if(cpu -> a == 0) { 
        cpu -> p.z = 1; 
    }

    if((cpu -> a >> 7) & 0x1) {
        cpu->p.n = 1; 
    } 

    cpu -> pc += (uint8_t)0x1; 
}


void ASL_ZP_handler(mos6502_t *cpu) {
    uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
    uint8_t value = read8(cpu, (uint16_t)operand); 

    cpu -> p.c = value >> 7; 

    write8(cpu, operand, (value << 1) & 0x00FF); 
    
    if(!((value <<1) & 0x00FF)) { 
        cpu -> p.z = 1; 
    }

    cpu -> pc += (uint8_t)0x2;
}

void ASL_ZPX_handler(mos6502_t *cpu) { 
    uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
    uint8_t value = read8(cpu, (uint16_t)operand); 

    cpu -> p.c = value >> 7; 

    write8(cpu, operand + cpu -> x, (value << 1) & 0x00FF); 
    
    if(!((value <<1) & 0x00FF)) { 
        cpu -> p.z = 1; 
    }

    cpu -> pc += (uint8_t)0x2;
}

void ASL_ABS_handler(mos6502_t *cpu) {
	uint16_t operand = read16(cpu, cpu -> pc + (uint16_t)1); 
    uint8_t value = read8(cpu, operand); 

    cpu -> p.c = value >> 7; 

    write8(cpu, operand, (value << 1) & 0x00FF); 
    
    if(!((value <<1) & 0x00FF)) { 
        cpu -> p.z = 1; 
    }
    cpu -> pc += (uint8_t)0x3;
}

void ASL_ABSX_handler(mos6502_t *cpu) {
	uint16_t operand = read16(cpu, cpu -> pc + (uint16_t)1); 
    uint8_t value = read8(cpu, operand); 

    cpu -> p.c = value >> 7; 

    write8(cpu, operand, (value << 1) & 0x00FF); 
    
    if(!((value <<1) & 0x00FF)) { 
        cpu -> p.z = 1; 
    }
    cpu -> pc += (uint8_t)0x3;
}



// branch on carry clear 
void BCC_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand;

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}



cpu -> pc += 0x2;

if((cpu -> p).c == 0) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}


}

// branch on carry set 
void BCS_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand; 

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}



cpu -> pc += 0x2;

if((cpu -> p).c == 1) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}


}

// branch on equal (zero set) 
void BEQ_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand;

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}

cpu -> pc += 0x2;

if((cpu -> p).z == 1) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}




}

// bit test 
void BIT_handler(mos6502_t *cpu) { 
uint8_t operand = read16(cpu, cpu -> pc + 1); 
uint8_t value = read8(cpu, operand); 

if(value & cpu -> a) {
	cpu -> p.z = 1;
}

if(value >> 7) {
	cpu -> p.n = 1;
}

if(value >> 6 & 0x01) {
	cpu -> p.v = 1; 
}

cpu -> pc += (uint8_t)0x2; 



}

void BIT_ABS_handler(mos6502_t *cpu) { 
uint16_t operand = read16(cpu, cpu -> pc + 1); 
uint8_t value = read8(cpu, operand); 

if(value & cpu -> a) {
	cpu -> p.z = 1;
}

if(value >> 7) {
	cpu -> p.n = 1;
}

if(value >> 6 & 0x01) {
	cpu -> p.v = 1; 
}

cpu -> pc += (uint8_t)0x3; 



}

// branch on minus (negative set)  
void BMI_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand;

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}

cpu -> pc += 0x2;

if((cpu -> p).n == 1) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}



}

// branch on not equal (zero clear) 
void BNE_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand;

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}

cpu -> pc += 0x2;

if((cpu -> p).z == 0) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}




}

// branch on plus (negative clear) 
void BPL_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand;

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}

cpu -> pc += 0x2;

if(cpu -> p.n == 0) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}



}

// break/interrupt
void BRK_handler(mos6502_t *cpu) { 
    
    // writing to cpu 
    cpu -> pc += 2; 
    write8(cpu, cpu -> sp--, (cpu -> pc >> 8) & 0xFF); 
    write8(cpu, cpu -> sp--, (cpu -> pc) & 0x00FF); 
    write8(cpu, cpu -> sp--, (cpu -> p.val)); 

    uint8_t lo = read8(cpu, 0xFFFE);
    uint8_t hi = read8(cpu, 0xFFFF); 
    
    cpu -> p.b = 1; 

    uint8_t value  = (hi << 8) | lo; 
    cpu -> pc = value; 

}


// branch on overflow clear
void BVC_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand;

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}

cpu -> pc += 0x2;

if((cpu -> p).v == 0) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}



}

// branch on overflow set 
void BVS_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t new_operand;

if(operand >> 7) { 
new_operand = operand + 1; 
} else {
new_operand = operand;
}

cpu -> pc += 0x2;

if((cpu -> p).v == 1) { 
	if(operand >> 7) { 
		cpu -> pc = cpu -> pc - new_operand; 
	} else {
		cpu -> pc = cpu -> pc + operand; 
	}

}



}

// clear carry 
void CLC_handler(mos6502_t *cpu) {

cpu -> p.c = 0;
cpu -> pc += (uint8_t)0x1;

}

// clear decimal 
void CLD_handler(mos6502_t *cpu) { 

	cpu -> p.d = 0;
	cpu -> pc += (uint8_t)0x1;
}

// clear interrupt disable
void CLI_handler(mos6502_t *cpu) {
	cpu -> p.i = 0;
	cpu -> pc += (uint8_t)0x1;
}	

// clear overflow 
void CLV_handler(mos6502_t *cpu) {
	cpu -> p.v = 0;
	cpu -> pc += (uint8_t)0x1; 
}

// comapre with accumulator 
void CMP_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 

if(cpu -> a >= operand) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - operand) >> 7) {
    cpu -> p.n = 1;  
} else { 
    cpu -> p.n = 0;
}

if(cpu -> a == operand) { 
    cpu -> p.z = 1; 
} else { 
    cpu -> p.z = 0; 
}

cpu -> pc += (uint8_t)0x2;

}

void CMP_ZP_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
uint8_t value = read8(cpu, (uint16_t)operand); 

if(cpu -> a >= value) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - value) >> 7) {
    cpu -> p.n = 1;  
} else {
    cpu -> p.n = 0;
}

if(cpu -> a == value) { 
    cpu -> p.z = 1; 
} else {
    cpu -> p.z = 0;
}

cpu -> pc += (uint8_t)0x2;

}


void CMP_ZPX_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
uint8_t value = read8(cpu, (uint16_t)(operand + cpu -> x)); 

if(cpu -> a >= value) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - value) >> 7) {
    cpu -> p.n = 1;  
} else { 
    cpu -> p.n = 0;
}

if(cpu -> a == value) { 
    cpu -> p.z = 1; 
} else { 
    cpu -> p.z = 0;
}

cpu -> pc += (uint8_t)0x2;

}


void CMP_ABS_handler(mos6502_t *cpu) { 
uint16_t operand = read16(cpu, cpu -> pc + (uint16_t)1); 
uint8_t value = read8(cpu, operand); 

if(cpu -> a >= value) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - value) >> 7) {
    cpu -> p.n = 1;  
} else { 
    cpu -> p.n = 0;
}

if(cpu -> a == value) { 
    cpu -> p.z = 1; 
} else { 
    cpu -> p.z = 0;
}

cpu -> pc += (uint8_t)0x3;

}


void CMP_ABSX_handler(mos6502_t *cpu) { 
uint16_t operand = read16(cpu, cpu -> pc + (uint16_t)1); 
uint8_t value = read8(cpu, operand + (uint16_t)cpu -> x); 

if(cpu -> a >= value) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - value) >> 7) {
    cpu -> p.n = 1;  
} else { 
    cpu -> p.n = 0;
}

if(cpu -> a == operand) { 
    cpu -> p.z = 1; 
} else {
    cpu -> p.z = 0;
}

cpu -> pc += (uint8_t)0x3;

}

void CMP_ABSY_handler(mos6502_t *cpu) { 
uint16_t operand = read16(cpu, cpu -> pc + (uint16_t)1);
uint8_t value = read8(cpu, operand + (uint16_t)cpu->y);

if(cpu -> a >= value) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - value) >> 7) {
    cpu -> p.n = 1;  
} else { 
    cpu -> p.n = 0; 
}

if(cpu -> a == value) { 
    cpu -> p.z = 1; 
} else { 
    cpu -> p.z = 0;
}

cpu -> pc += (uint8_t)0x3;

}


void CMP_IDX_IDR_handler(mos6502_t *cpu) { 
uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
uint8_t lo = operand + cpu -> x; 
uint8_t hi = lo + 1; 

uint16_t addr = (hi <<8) | lo; 

uint8_t value = read8(cpu, addr); 

if(cpu -> a >= value) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - value) >> 7) {
    cpu -> p.n = 1;  
} else { 
    cpu -> p.n = 0;
}

if(cpu -> a == value) { 
    cpu -> p.z = 1; 
} else { 
    cpu -> p.z = 0;    
}

cpu -> pc += (uint8_t)0x2;

}


void CMP_IDR_IDY_handler(mos6502_t *cpu) {
uint8_t first = read8(cpu, cpu -> pc + 1); 
uint8_t second = first + 1; 
uint8_t lo = read8(cpu, first + cpu -> y); 
uint8_t hi = read8(cpu, second); 

uint16_t addr = (hi << 8) | lo;

uint8_t value = read8(cpu, addr);

if(cpu -> a >= value) { 
    cpu -> p.c = 1;    
}

if((cpu -> a - value) >> 7) {
    cpu -> p.n = 1;  
} else { 
    cpu -> p.n = 0;
}

if(cpu -> a == value) { 
    cpu -> p.z = 1; 
}

cpu -> pc += (uint8_t)0x2;

}


// compare with X
void CPX_handler(mos6502_t *cpu) {

}

void CPX_ZP_handler(mos6502_t *cpu) { 

}

void CPX_ABS_handler(mos6502_t *cpu) {

}

// compare with Y 
void CPY_handler(mos6502_t *cpu) { 

}

void CPY_ZP_handler(mos6502_t *cpu) { 

}

void CPY_ABS_handler(mos6502_t *cpu) {

}

// decrement
void DEC_ZP_handler(mos6502_t *cpu) {

}	

void DEC_ZPX_handler(mos6502_t *cpu) { 

}

void DEC_ABS_handler(mos6502_t *cpu) {

}

void DEC_ABSX_handler(mos6502_t *cpu) {

}

// decrement X
void DEX_handler(mos6502_t *cpu) {

}

// decrement Y
void DEY_handler(mos6502_t *cpu) {

}	

// exclusive or (with accumulator) 
void EOR_handler(mos6502_t *cpu) {

}

void EOR_ZP_handler(mos6502_t *cpu) { 

}

void EOR_ZPX_handler(mos6502_t *cpu) {

}

void EOR_ABS_handler(mos6502_t *cpu) {

}

void EOR_ABSX_handler(mos6502_t *cpu) { 

}

void EOR_ABSY_handler(mos6502_t *cpu) {

}

void EOR_IDX_IDR_handler(mos6502_t *cpu) {

}

void EOR_IDR_IDY_handler(mos6502_t *cpu) {

}

// increment 
void INC_handler(mos6502_t *cpu) {

}

void INC_ZP_handler(mos6502_t *cpu) {

}

void INC_ZPX_handler(mos6502_t *cpu) {

}

void INC_ABS_handler(mos6502_t *cpu) {

}

void INC_ABSX_handler(mos6502_t *cpu) {

}
// increment X
void INX_handler(mos6502_t *cpu) {
	 cpu -> x++;
     
     if(cpu -> x >> 7) { 
        cpu -> p.n = 1; 
     }

     if(cpu -> x == 0) {
        cpu -> p.z = 1; 
     }

     cpu -> pc += 1; 
}	

// increment Y
void INY_handler(mos6502_t *cpu) {
	 cpu -> y++;
     
     if(cpu -> y >> 7) { 
        cpu -> p.n = 1; 
     }

     if(cpu -> y == 0) {
        cpu -> p.z = 1; 
     }

     cpu -> pc += 1; 
}

// Jump 
void JMP_ABS_handler(mos6502_t *cpu) {
uint8_t lo = read8(cpu, cpu -> pc + 1); 
uint8_t hi = read8(cpu, cpu -> pc + 2); 

cpu -> pc = hi << 8 | lo; 

}

void JMP_IDR_handler(mos6502_t *cpu) { 
uint16_t operand = read16(cpu, cpu -> pc + 1);
uint8_t lo = read8(cpu, operand); 
uint8_t hi = read8(cpu, operand + 1); 

uint16_t value = (hi << 8) | lo;

cpu -> pc = value; 

}

// Jump subroutine 
void JSR_handler(mos6502_t *cpu) {

}

// Load accumulator 
void LDA_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, (cpu -> pc) + (uint8_t)1); 

//printf("this is printing");
cpu -> a = operand; 

if(cpu -> a == 0) {
    cpu -> p.z = 1; 
    } else {
	cpu -> p.z = cpu -> p.z;
    }

if(cpu -> a >> 7) {
    cpu -> p.n = 1; 
} else {
	cpu -> p.n = cpu -> p.n;
}

cpu -> pc += (uint8_t)0x2; 

}

void LDA_ZP_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc + 1); 
uint8_t value = read8(cpu, (uint16_t)operand); 

cpu -> a = value;

if(cpu -> a == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> a >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x2; 

}	

void LDA_ZPX_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc +(uint8_t)1); 
uint8_t value = read8(cpu, (uint16_t)(operand + cpu -> x)); 

cpu -> a = value;

if(cpu -> a == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> a >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x2; 


}		

void LDA_ABS_handler(mos6502_t *cpu) {
uint16_t operand = read16(cpu, cpu -> pc +1); 
uint8_t value = read8(cpu, operand); 

cpu -> a = value;

if(cpu -> a == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> a >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x3; 


}	

void LDA_ABSX_handler(mos6502_t *cpu) {
uint16_t operand = read16(cpu, cpu -> pc + 1); 
uint8_t value = read8(cpu, operand + cpu -> x); 

cpu -> a = value;

if(cpu -> a == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> a >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x3; 


}

void LDA_ABSY_handler(mos6502_t *cpu) {
uint16_t operand = read16(cpu, cpu -> pc + 1); 
uint8_t value = read8(cpu, operand + cpu -> y); 

cpu -> a = value;

if(cpu -> a == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> a >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x3; 


}	

void LDA_IDX_IDR_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1);

uint8_t lo = operand + cpu -> x;
uint8_t hi = lo + 1; 

uint16_t addr = (hi << 8) | lo; 

uint8_t value = read8(cpu, addr); 

cpu -> a = value; 

if(cpu -> a == 0) { 
    cpu ->p.z = 1;
}

if(cpu -> a >> 7) { 
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x2;


}	


void LDA_IDR_IDY_handler(mos6502_t *cpu) {
uint8_t first = read8(cpu, cpu -> pc + (uint8_t)1); 
uint8_t second = first + 1; 
    
uint8_t lo = read8(cpu, first + cpu -> y);
uint8_t hi = read8(cpu,  second); 

uint16_t addr = (hi << 8) | lo; 

uint8_t value = read8(cpu, addr); 

cpu -> a = value; 

if(cpu -> a == 0) { 
    cpu ->p.z = 1;
}

if(cpu -> a >> 7) { 
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x2;
}	


// Load X
void LDX_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, (cpu -> pc) + (uint8_t)1); 

cpu -> x = operand;;

if(cpu -> x == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> x >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x2; 



}	
void LDX_ZP_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
uint8_t value = read8(cpu, operand); 

cpu -> x = value;

if(cpu -> x == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> x >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x2; 



}	
void LDX_ZPY_handler(mos6502_t *cpu) {
uint8_t operand = read8(cpu, cpu -> pc + (uint8_t)1); 
uint8_t value = read8(cpu, operand + (uint16_t)cpu -> y); 

cpu -> x = value;

if(cpu -> x == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> x >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x2; 



}	
void LDX_ABS_handler(mos6502_t *cpu) {
uint16_t operand = read16(cpu, cpu -> pc + (uint16_t)1); 
uint8_t value = read8(cpu, operand); 

cpu -> x = value;

if(cpu -> x == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> x >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x3; 



}	
void LDX_ABSY_handler(mos6502_t *cpu) {
uint16_t operand = read16(cpu, cpu -> pc + (uint16_t)1); 
uint8_t value = read8(cpu, operand + (uint16_t)cpu -> y); 

cpu -> x = value;

if(cpu -> x == 0) {
    cpu -> p.z = 1; 
    }

if(cpu -> x >> 7) {
    cpu -> p.n = 1; 
}

cpu -> pc += (uint8_t)0x3; 



}	





// Load Y
void LDY_handler(mos6502_t *cpu) {

}

void LDY_ZP_handler(mos6502_t *cpu) {

}

void LDY_ZPX_handler(mos6502_t *cpu) {

}

void LDY_ABS_handler(mos6502_t *cpu) {

}

void LDY_ABSX_handler(mos6502_t *cpu) {

}



// Logical shift right 
void LSR_handler(mos6502_t *cpu) { 

}	

void LSR_ZP_handler(mos6502_t *cpu) { 

}	

void LSR_ZPX_handler(mos6502_t *cpu) { 

}	

void LSR_ABS_handler(mos6502_t *cpu) { 

}	

void LSR_ABSX_handler(mos6502_t *cpu) { 

}	


// No operation 
void NOP_handler(mos6502_t *cpu) {

}

// Or with accumulator 
void ORA_handler(mos6502_t *cpu) { 

}

void ORA_ZP_handler(mos6502_t *cpu) { 

}

void ORA_ZPX_handler(mos6502_t *cpu) { 

}

void ORA_ABS_handler(mos6502_t *cpu) { 

}

void ORA_ABSX_handler(mos6502_t *cpu) { 

}

void ORA_ABSY_handler(mos6502_t *cpu) { 

}

void ORA_IDX_IDR_handler(mos6502_t *cpu) { 

}

void ORA_IDR_IDY_handler(mos6502_t *cpu) { 

}


// push accumulator 
void PHA_handler(mos6502_t *cpu) {

}

// push processor status (SR) 
void PHP_handler(mos6502_t *cpu) { 

}	

// pull accumulator
void PLA_handler(mos6502_t *cpu) {

}	

// pull accumulator status (SR)
void PLP_handler(mos6502_t *cpu) {

}	

// rotate left 
void ROL_handler(mos6502_t *cpu) {

}	
void ROL_ZP_handler(mos6502_t *cpu) {

}	

void ROL_ZPX_handler(mos6502_t *cpu) {

}	

void ROL_ABS_handler(mos6502_t *cpu) {

}	

void ROL_ABSX_handler(mos6502_t *cpu) {

}	


// rotate right 
void ROR_handler(mos6502_t *cpu) {

}	

void ROR_ZP_handler(mos6502_t *cpu) {

}	

void ROR_ZPX_handler(mos6502_t *cpu) {

}	

void ROR_ABS_handler(mos6502_t *cpu) {

}	

void ROR_ABSX_handler(mos6502_t *cpu) {

}	

// return from interrupt
void RTI_handler(mos6502_t *cpu) {

}	

// return from subroutine 
void RTS_handler(mos6502_t *cpu) {

}

// subtract with carry 
void SBC_handler(mos6502_t *cpu) {

}	

void SBC_ZP_handler(mos6502_t *cpu) {

}	

void SBC_ZPX_handler(mos6502_t *cpu) {

}	

void SBC_ABS_handler(mos6502_t *cpu) {

}	

void SBC_ABSX_handler(mos6502_t *cpu) {

}	

void SBC_ABSY_handler(mos6502_t *cpu) {

}	

void SBC_IDX_IDR_handler(mos6502_t *cpu) {

}	

void SBC_IDR_IDY_handler(mos6502_t *cpu) {

}	


// set carry 
void SEC_handler(mos6502_t *cpu) {

}

// set decimal 
void SED_handler(mos6502_t *cpu) {

}

// set interrupt disable
void SEI_handler(mos6502_t *cpu) {

}	

// store accumulator 
void STA_handler(mos6502_t *cpu) {

}
void STA_ZP_handler(mos6502_t *cpu) {

}
void STA_ZPX_handler(mos6502_t *cpu) {

}
void STA_ABS_handler(mos6502_t *cpu) {

}
void STA_ABSX_handler(mos6502_t *cpu) {

}
void STA_ABSY_handler(mos6502_t *cpu) {

}
void STA_IDX_IDR_handler(mos6502_t *cpu) {

}
void STA_IDR_IDY_handler(mos6502_t *cpu) {

}

// store X
void STX_handler(mos6502_t *cpu) {

}

void STX_ZP_handler(mos6502_t *cpu) {

}

void STX_ZPY_handler(mos6502_t *cpu) {

}

void STX_ABS_handler(mos6502_t *cpu) {

}

// store Y
void STY_handler(mos6502_t *cpu) {

}	
void STY_ZP_handler(mos6502_t *cpu) {

}	
void STY_ZPX_handler(mos6502_t *cpu) {

}	
void STY_ABS_handler(mos6502_t *cpu) {

}	


// transfer accumulator to X
void TAX_handler(mos6502_t *cpu) {

}	

// transfer accumulator to Y
void TAY_handler(mos6502_t *cpu) {

}	

// transfer stack pointer to X
void TSX_handler(mos6502_t *cpu) {

}

// transfer X to accumulator 
void TXA_handler(mos6502_t *cpu) {

}

// transfer X to stack pointer 
void TXS_handler(mos6502_t *cpu) {

}	

// transfer Y to accumulator 
void TYA_handler(mos6502_t *cpu) {

}


