#include <rc.h>
#include <base.h>
#include <membus.h>
#include <timekeeper.h>
#include <mos6502/vmcall.h>
#include <mos6502/mos6502.h>

// Including my files
#include <mos6502/handlers.h> 
#include <string.h>

static const uint8_t instr_cycles[256] = {
	7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
	2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
	2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	6, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
	2, 6, 2, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5,
	2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
	2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
	2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
};

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

size_t
mos6502_instr_repr (mos6502_t * cpu, uint16_t addr, char * buffer, size_t buflen)
{
char *opcode_table[16][16] = { 
    {"BRK impl", "ORA X, ind", "JAM", "SLO X, ind", "NOP zpg", "ORA zpg", "ASL zpg", "SLO zpg", "PHP impl", "ORA #", "ASL A", "ANC #", "NOP abs", "ORA abs", "ASL abs", "SLO abs"}, 
    {"BPL rel", "ORA ind, Y", "JAM", "SLO ind, Y", "NOP zpg, X", "ORA zpg, X", "ASL zpg, X", "SLO zpg, X", "CLC impl", "ORA abs, Y", "NOP impl", "SLO abs, Y","NOP abs, X", "ORA abs, X", "ASL abs, X", "SLO abs, X"}, 
    {"JSR abs", "AND X, ind", "JAM", "RLA X, ind", "BIT zpg", "AND zpg", "ROL zpg", "RLA zpg", "PLP impl", "AND #", "ROL A", "ANC #", "BIT abs", "AND abs", "ROL abs", "RLA abs"},
    {"BMI rel", "AND ind, Y", "JAM", "RLA ind, Y", "NOP zpg, X", "AND zpg, X", "ROL zpg, X", "RLA zpg, X", "SEC impl", "AND abs, Y", "NOP impl", "RLA abs, Y", "NOP abs, X", "AND abs, X", "ROL abs, X", "RLA abs, X"},
    {"RTI impl", "EOR X, ind", "JAM", "SRE X, ind", "NOP zpg", "EOR zpg", "LSR zpg", "SRE zpg", "PHA impl", "EOR #", "LSR A", "ALR #", "JMP abs", "EOR abs", "LSR abs", "SRE abs"},
    {"BVC rel", "EOR ind, Y", "JAM", "SRE ind, Y", "NOP zpg, X", "EOR zpg, X", "LSR zpg, X", "SRE zpg, X", "CLI impl", "EOR abs, Y", "NOP impl", "SRE abs, Y", "NOP abs, X", "EOR abs, X", "LSR abs, X", "SRE abs, X"},
    {"RTS impl", "ADC X, ind", "JAM", "RRA X, ind", "NOP zpg", "ADC zpg", "ROR zpg", "RRA zpg", "PLA impl", "ADC #", "ROR A", "ARR #", "JMP ind", "ADC abs", "ROR abs", "RRA abs"},
    {"BVS rel", "ADC ind, Y", "JAM", "RRA ind, Y", "NOP zpg, X", "ADC zpg, X", "ROR zpg, X", "RRA zpg, X", "SEI impl", "ADC abs, Y", "NOP impl", "RRA abs, Y", "NOP abs, Y", "ADC abs, X", "ROR abs, X", "RRA abs, X"},
    {"NOP #", "STA X, ind", "NOP #", "SAX X, ind", "STY zpg", "STA zpg", "STX zpg", "SAX zpg", "DEY impl", "NOP #", "TAX impl", "ANE #", "STY abs", "STA abs", "STX abs", "SAX abs"},
    {"BCC rel", "STA ind, Y", "JAM", "SHA ind, Y", "STY zpg, X", "STA zpg, X", "STX zpg, Y", "SAX zpg, Y", "TYA impl", "STA abs, Y", "TXS impl", "TAS abs, Y", "SHY abs, X", "STA abs, X", "SHX abs, Y", "SHA abs, Y"},
    {"LDY #", "LDA X, ind", "LDX #", "LAX X, ind", "LDY zpg", "LDA zpg", "LDX zpg", "LAX zpg", "TAY impl", "LDA #", "TAX impl", "LXA #", "LDY abs", "LDA abs", "LDX abs", "LAX abs"},
    {"BCS rel", "LDA ind, Y", "JAM", "LAX ind, Y", "LDY zpg, X", "LDA zpg, Y", "LDX zpg, Y", "LAX zpg, Y", "CLV impl", "LDA abs, Y", "TSX impl", "LAS abs, Y", "LDY abs, X", "LDA abs, X", "LDX abs, Y", "LAX abs, Y"},
    {"CPY #", "CMP X, ind", "NOP #", "DCP X, ind", "CPY zpg", "CMP zpg", "DEC zpg", "DCP zpg", "INY impl", "CMP #", "DEX impl", "SBX #", "CPY abs", "CMP abs", "DEC abs", "DCP abs"},
    {"BNE rel", "CMP ind, Y", "JAM", "DCP ind, Y", "NOP zpg, X", "CMP zpg, X", "DEC zpg, X", "DCP zpg, X", "CLD impl", "CMP abs, Y", "NOP impl", "DCP abs, Y", "NOP abs, X", "CMP abs, X", "DEC abs, X", "DCP abs, X"},
    {"CPX #", "SBC X, ind", "NOP #", "ISC X, ind", "CPX zpg", "SBC zpg", "INC zpg", "ISC zpg", "INX impl", "SBC #", "NOP impl", "USBC #", "CPX abs", "SBC abs", "INC abs", "ISC abs"},
    {"BEQ rel", "SBC ind, Y", "JAM", "ISC ind, Y", "NOP zpg, X", "SBC zpg, X", "INC zpg, X", "ISC zpg, X", "SED impl", "SBC abs, Y", "NOP impl", "ISC abs, Y", "NOP abs, X", "SBC abs, X", "INC abs, X", "ISC abs, X"}
    };
	
	uint8_t opcode = read8(cpu, addr); 
	uint8_t hi = opcode >> 4; 
	uint8_t lo = opcode & 0x0F;
	snprintf(buffer, buflen, "%s\n", opcode_table[hi][lo]); 


	return 0;
}

mos6502_step_result_t
mos6502_step (mos6502_t * cpu)
{
	uint8_t opcode = read8(cpu, cpu->pc);
//	printf("%x\n", opcode); 
// anyinstruction with only break in the statement is an illegal one, will implement later.
	switch(opcode) {
		
		        case 0x00:
                    BRK_handler(cpu); 
                    break; 
                case 0x01:
                    ORA_IDX_IDR_handler(cpu); 
                    break; 
		        case 0x02:
                    break;
                case 0x03: 
                    break;
		        case 0x04:
                    break; 
		        case 0x05:
                    ORA_ZP_handler(cpu);
		   break; 
		        case 0x06:
                    ASL_ZP_handler(cpu); 
		        case 0x07:
                    break; 
		        case 0x08:
                    PHP_handler(cpu);
                    break;  
		        case 0x09:
                    ORA_handler(cpu); 
                    break; 
		        case 0x0A:
                    ASL_handler(cpu); 
                    break;
		        case 0x0B:
                    break; 
		        case 0x0C:
                    break; 
		        case 0x0D:
                    ORA_ABS_handler(cpu); 
                    break; 
		        case 0x0E:
                    ASL_ABS_handler(cpu); 
                    break;
		        case 0x0F:
                    break; 

	            case 0x10:
                    BPL_handler(cpu); 
                    break; 
                case 0x11:
                    ORA_IDR_IDY_handler(cpu); 
                    break; 
                case 0x12:
                    break;
                case 0x13:
                    break;
                case 0x14:
                    break;
                case 0x15:
                    ORA_ZP_handler(cpu);
                    break;  
                case 0x16:
                    ASL_ZP_handler(cpu); 
                    break;
                case 0x17:
                    break;
                case 0x18:
                    CLC_handler(cpu);
                    break;  
                case 0x19:
                    ORA_ABSY_handler(cpu);
                    break; 
                case 0x1A:
                    break;
                case 0x1B:
                    break;
                case 0x1C:
                    break;
                case 0x1D:
                    ORA_ABSX_handler(cpu);
                    break;
                case 0x1E:
                    ASL_ABSX_handler(cpu);
                    break;
                case 0x1F:
                    break;

		        case 0x20:
                    JSR_handler(cpu); 
                    break;
                case 0x21:
                    AND_IDX_IDR_handler(cpu);
                    break; 
                case 0x22:
                    break;
                case 0x23:
                    break; 
                case 0x24:
                    BIT_handler(cpu); 
                    break;
                case 0x25:
                    AND_ZP_handler(cpu); 
                    break;
                case 0x26:
                    ROL_ZP_handler(cpu);
                    break;
                case 0x27:
                    break;
                case 0x28:
                    PLP_handler(cpu);
                    break;
                case 0x29:
                    AND_handler(cpu);
                    break;
                case 0x2A:
                    ROL_handler(cpu);
                    break;
                case 0x2B:
                    break;
                case 0x2C:
                    BIT_ABS_handler(cpu);
                    break;
                case 0x2D:
                    AND_ABS_handler(cpu);
                    break;
                case 0x2E:
                    ROL_ABS_handler(cpu);
                    break;
                case 0x2F:
                    break;

		        case 0x30:
                    BMI_handler(cpu);
                    break;
                case 0x31:
                    AND_IDR_IDY_handler(cpu);
                    break;
                case 0x32:
                    break;
                case 0x33:
                    break;
                case 0x34:
                    break;
                case 0x35:
                    AND_ZPX_handler(cpu);
                    break;
                case 0x36:
                    ROL_ZPX_handler(cpu);
                    break;
                case 0x37:
                    break;
                case 0x38:
                    SEC_handler(cpu); 
                    break;
                case 0x39:
                    AND_ABSY_handler(cpu);
                    break;
                case 0x3A:
                    break;
                case 0x3B:
                    break;
                case 0x3C:
                    break;
                case 0x3D:
                    AND_ABSX_handler(cpu);
                    break;
                case 0x3E:
                    ROL_ABSX_handler(cpu);
                    break;
                case 0x3F:
                    break;

		        case 0x40:
                    RTI_handler(cpu);
                    break;
                case 0x41:
                    EOR_IDX_IDR_handler(cpu);
                    break;
                case 0x42:
                    break;
                case 0x43:
                    break;
                case 0x44:
                    break;
                case 0x45:
                    EOR_ZP_handler(cpu);
                    break;
                case 0x46:
                    LSR_ZP_handler(cpu);
                    break;
                case 0x47:
                    break;
                case 0x48:
                    PHA_handler(cpu);
                    break;
                case 0x49:
                    EOR_handler(cpu);
                    break;
                case 0x4A:
                    LSR_handler(cpu);
                    break;
                case 0x4B:
                    break;
                case 0x4C:
                    JMP_ABS_handler(cpu);
                    break;
                case 0x4D:
                    EOR_ABS_handler(cpu);
                    break;
                case 0x4E:
                    LSR_ABS_handler(cpu);
                    break;
                case 0x4F:
                    break;


		        case 0x50:
                    BVC_handler(cpu);
                    break;
                case 0x51:
                    EOR_IDR_IDY_handler(cpu);
                    break;
                case 0x52:
                    break;    
                case 0x53:
                    break;
                case 0x54:
                    break;
                case 0x55:
                    EOR_ZPX_handler(cpu);
                    break;
                case 0x56:
                    LSR_ZPX_handler(cpu);
                    break;
                case 0x57:
                    break;
                case 0x58:
                    CLI_handler(cpu);
                    break;
                case 0x59:
                    EOR_ABSY_handler(cpu);
                    break;
                case 0x5A:
                    break;
                case 0x5B:
                    break;
                case 0x5C:
                    break;
                case 0x5D:
                    EOR_ABSX_handler(cpu);
                    break;
                case 0x5E:
                    LSR_ABSX_handler(cpu);
                    break;
                case 0x5F:
                    break;

        		case 0x60:
                    RTS_handler(cpu);
                    break;
                case 0x61:
                    ADC_IDX_IDR_handler(cpu);
                    break;
                case 0x62:
                    break;
                case 0x63:
                    break;
                case 0x64:
                    break;
                case 0x65:
                    ADC_ZP_handler(cpu);
                    break;
                case 0x66:
                    ROR_ZP_handler(cpu);
                    break;
                case 0x67:
                    break;
                case 0x68:
                    PLA_handler(cpu);
                    break;
                case 0x69:
			        ADC_handler(cpu);
			        break; 
                case 0x6A:
                    ROR_handler(cpu);
                    break;
                case 0x6B:
                    break;
                case 0x6C:
                    JMP_IDR_handler(cpu);
                    break;
                case 0x6D:
                    ADC_ABS_handler(cpu);
                    break;
                case 0x6E:
                    ROR_ABS_handler(cpu);
                    break;
                case 0x6F:
                    break;

		        case 0x70:
                    BVS_handler(cpu);
                    break;
                case 0x71:
                    ADC_IDR_IDY_handler(cpu);
                    break;
                case 0x72:
                    break;
                case 0x73:
                    break;
                case 0x74:
                    break;
                case 0x75:
                    ADC_ZPX_handler(cpu);
                    break;
                case 0x76:
                    ROR_ZPX_handler(cpu);
                    break;
                case 0x77:
                    break;
                case 0x78:
                    SEI_handler(cpu);
                    break;
                case 0x79:
                    ADC_ABSY_handler(cpu);
                    break;
                case 0x7A:
                    break;
                case 0x7B:
                    break;
                case 0x7C:
                    break;
                case 0x7D:
                    ADC_ABSX_handler(cpu);
                    break;
                case 0x7E:
                    ROR_ABSX_handler(cpu);
                    break;
                case 0x7F:
                    break;

		        case 0x80:
		            handle_vmcall(cpu, opcode); 	
			        break;
                case 0x81:
                    STA_IDX_IDR_handler(cpu);
                    break;
                case 0x82:
                    break;
                case 0x83:
                    break;
                case 0x84:
                    STY_ZP_handler(cpu); 
                    break;
                case 0x85:
                    STA_ZP_handler(cpu);
                    break;
                case 0x86:
                    STX_ZP_handler(cpu);
                    break;
                case 0x87:
                    break;
                case 0x88:
                    DEY_handler(cpu);
                    break;
                case 0x89:
                    break;
                case 0x8A:
                    TXA_handler(cpu);
                    break;
                case 0x8B:
                    break;
                case 0x8C:
                    STY_ABS_handler(cpu);
                    break;
                case 0x8D:
                    STA_ABS_handler(cpu);
                    break;
                case 0x8E:
                    STX_ABS_handler(cpu);
                    break;
                case 0x8F:
                    break;

		        case 0x90:
                    BCC_handler(cpu);
                    break;
                case 0x91:
                    STA_IDR_IDY_handler(cpu);
                    break;
                case 0x92:
                    break;
                case 0x93:
                    break;
                case 0x94:
                    STY_ZPX_handler(cpu);
                    break;
                case 0x95:
                    STA_ZPX_handler(cpu);
                    break;
                case 0x96:
                    STX_ZPY_handler(cpu);
                    break;
                case 0x97:
                    break;
                case 0x98:
                    TYA_handler(cpu);
                    break;
                case 0x99:
                    STA_ABSY_handler(cpu);
                    break;
                case 0x9A:
                    TXS_handler(cpu);
                    break;
                case 0x9B:
                    break;
                case 0x9C:
                    break;
                case 0x9D:
                    STA_ABSX_handler(cpu);
                    break;
                case 0x9E:
                    break;
		        case 0x9F:
                    break;

		        case 0xA0:
                    LDY_handler(cpu);
                    break;
                case 0xA1:
                    LDA_IDX_IDR_handler(cpu);
                    break;
                case 0xA2:
                    LDX_handler(cpu);
                    break;
                case 0xA3:
                    break;
                case 0xA4:
                    LDY_ZP_handler(cpu);
                    break;
                case 0xA5:
                    LDA_ZP_handler(cpu);
                    break;
                case 0xA6:
                    LDX_ZP_handler(cpu);
                    break;
                case 0xA7:
                    break;
                case 0xA8:
                    TAY_handler(cpu);
                    break;
                case 0xA9:
		    //printf("Are we going in here?");
                    LDA_handler(cpu);
                    break; 
                case 0xAA:
                    TAX_handler(cpu);
                    break;
                case 0xAB:
                    break;
                case 0xAC:
                    LDY_ABS_handler(cpu);
                    break;
                case 0xAD:
                    LDA_ABS_handler(cpu);
                    break;
                case 0xAE:
                    LDX_ABS_handler(cpu);
                    break;
                case 0xAF:
                    break;

		        case 0xB0:
                    BCS_handler(cpu);
                    break;
                case 0xB1:
                    LDA_IDR_IDY_handler(cpu);
                    break;
                case 0xB2:
                    break;
                case 0xB3:
                    break;
                case 0xB4:
                    LDY_ZPX_handler(cpu);
                    break;
                case 0xB5:
                    LDA_ZPX_handler(cpu);
                    break;
                case 0xB6:
                    LDX_ZPY_handler(cpu);
                    break;
                case 0xB7:
                    break;
                case 0xB8:
                    CLV_handler(cpu);
                    break;
                case 0xB9:
                    LDA_ABSY_handler(cpu);
                    break;
                case 0xBA:
                    TSX_handler(cpu);
                    break;
                case 0xBB:
                    break;
                case 0xBC:
                    LDY_ABSX_handler(cpu);
                    break;
                case 0xBD:
                    LDA_ABSX_handler(cpu);
                    break;
                case 0xBE:
                    LDX_ABSY_handler(cpu);
                    break;
                case 0xBF:
                    break;

		        case 0xC0:
                    CPY_handler(cpu);
                    break;
                case 0xC1:
                    CMP_IDX_IDR_handler(cpu);
                    break;
                case 0xC2:
                    break;
                case 0xC3:
                    break;
                case 0xC4:
                    CPY_ZP_handler(cpu);
                    break;
                case 0xC5:
                    CMP_ZP_handler(cpu);
                    break;
                case 0xC6:
                    DEC_ZP_handler(cpu);
                    break;
                case 0xC7:
                    break;
                case 0xC8:
                    INY_handler(cpu);
                    break;
                case 0xC9:
                    CMP_handler(cpu);
                    break;
                case 0xCA:
                    DEX_handler(cpu);
                    break;
                case 0xCB:
                    break;
                case 0xCC:
                    CPY_ABS_handler(cpu);
                    break;
                case 0xCD:
                    CMP_ABS_handler(cpu);
                    break;
                case 0xCE:
                    DEC_ABS_handler(cpu);
                    break;
                case 0xCF:
                    break;

		        case 0xD0:
                    BNE_handler(cpu);
                    break;
                case 0xD1:
                    CMP_IDR_IDY_handler(cpu);
                    break;
                case 0xD2:
                    break;
                case 0xD3:
                    break;
                case 0xD4:
                    break;
                case 0xD5:
                    CMP_ZPX_handler(cpu);
                    break;
                case 0xD6:
                    DEC_ZPX_handler(cpu);
                    break;
                case 0xD7:
                    break;
                case 0xD8:
                    CLD_handler(cpu);
                    break;
                case 0xD9:
                    CMP_ABSY_handler(cpu);
                    break;
                case 0xDA:
                    break;
                case 0xDB:
                    break;
                case 0xDC:
                    break;
                case 0xDD:
                    CMP_ABSX_handler(cpu);
                    break;
                case 0xDE:
                    DEC_ABSX_handler(cpu);
                    break;
                case 0xDF:
                    break;

		        case 0xE0:
                    CPX_handler(cpu);
                    break;
                case 0xE1:
                    SBC_IDX_IDR_handler(cpu);
                    break;
                case 0xE2:
                    break;
                case 0xE3:
                    break;
                case 0xE4:
                    CPX_ZP_handler(cpu);
                    break;
                case 0xE5:
                    SBC_ZP_handler(cpu);
                    break;
                case 0xE6:
                    INC_ZP_handler(cpu);
                    break;
                case 0xE7:
                    break;
                case 0xE8:
                    INX_handler(cpu);
                    break;
                case 0xE9:
                    SBC_handler(cpu);
                    break;
                case 0xEA:
                    NOP_handler(cpu);
                    break;
                case 0xEB:
                    break;
                case 0xEC:
                    CPX_ABS_handler(cpu);
                    break;
                case 0xED:
                    SBC_ABS_handler(cpu);
                    break;
                case 0xEE:
                    INC_ABS_handler(cpu);
                case 0xEF:
                    break;

		        case 0xF0:
                    BEQ_handler(cpu);
                    break;
                case 0xF1:
                    SBC_IDR_IDY_handler(cpu);
                    break;
                case 0xF2:
                    break;
                case 0xF3:
                    break;
                case 0xF4:
                    break;
                case 0xF5:
                    SBC_ZPX_handler(cpu);
                    break;
                case 0xF6:
                    INC_ZPX_handler(cpu);
                    break;
                case 0xF7:
                    break;
                case 0xF8:
                    SED_handler(cpu);
                    break;
                case 0xF9:
                    SBC_ABSY_handler(cpu);
                    break;
                case 0xFA:
                    break;
                case 0xFB:
                    break;
                case 0xFC:
                    break;
                case 0xFD:
                    SBC_ABSX_handler(cpu);
                    break;
                case 0xFE:
                    INC_ABSX_handler(cpu);
                    break;
                case 0xFF:
                    break;

		default: 
			break; 

	}
	mos6502_advance_clk(cpu, instr_cycles[opcode]);
	return MOS6502_STEP_RESULT_SUCCESS;
}

/* 
 * Addressing mode functions, calculate effective addresses
 */
/*
static void imp() { 
// implied 
}
*/
/*static void acc() { 
// accumulator
} */

/*static void imm() { 
// immediate 
ea = pc++; // what the hell is ea? 
}*/

/*
 * Illegal opcodes are below
 */

