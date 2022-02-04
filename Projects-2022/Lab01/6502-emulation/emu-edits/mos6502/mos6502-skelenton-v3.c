#include <rc.h>
#include <base.h>
#include <membus.h>
#include <timekeeper.h>
#include <mos6502/vmcall.h>
#include <mos6502/mos6502.h>

#include <string.h>

void (*op_table[16][16])(mos6502_t *cpu) { 
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
	{}
};

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
/*	// FILL ME IN
string *lookup_table_opcode[16][16] = { 
    {"BRK impl", "ORA X, ind", "JAM", "SLO X, ind", "NOP zpg", "ORA zpg", "ASL zpg", "SLO zpg", "PHP impl", "ORA #", "ASL A", "ANC #", "NOP abs", "ORA abs", "ASL abs", "SLO abs"}, 
    {"BPL rel", "ORA ind, Y", "JAM", "SLO ind, Y", "NOP zpg, X", "ORA zpg, X", "ASL zpg, X", "SLO zpg, X", "CLC impl", "ORA abs, Y", "NOP impl", "SLO abs, Y","NOP abs, X", "ORA abs, X", "ASL abs, X", "SLO abs, X"} 
    {"JSR abs", "AND X, ind", "JAM", "RLA X, ind", "BIT zpg", "AND zpg", "ROL zpg", "RLA zpg", "PLP impl", "AND #", "ROL A", "ANC #", "BIT abs", "AND abs", "ROL abs", "RLA abs"}
    {"BMI rel", "AND ind, Y", "JAM", "RLA ind, Y", "NOP zpg, X", "AND zpg, X", "ROL zpg, X", "RLA zpg, X", "SEC impl", "AND abs, Y", "NOP impl", "RLA abs, Y", "NOP abs, X", "AND abs, X", "ROL abs, X", "RLA abs, X"}
    {"RTI impl", "EOR X, ind", "JAM", "SRE X, ind", "NOP zpg", "EOR zpg", "LSR zpg", "SRE zpg", "PHA impl", "EOR #", "LSR A", "ALR #", "JMP abs", "EOR abs", "LSR abs", "SRE abs"}
    {"BVC rel", "EOR ind, Y", "JAM", "SRE ind, Y", "NOP zpg, X", "EOR zpg, X", "LSR zpg, X", "SRE zpg, X", "CLI impl", "EOR abs, Y", "NOP impl", "SRE abs, Y", "NOP abs, X", "EOR abs, X", "LSR abs, X", "SRE abs, X"}
    {"RTS impl", "ADC X, ind", "JAM", "RRA X, ind", "NOP zpg", "ADC zpg", "ROR zpg", "RRA zpg", "PLA impl", "ADC #", "ROR A", "ARR #", "JMP ind", "ADC abs", "ROR abs", "RRA abs"}
    {"BVS rel", "ADC ind, Y", "JAM", "RRA ind, Y", "NOP zpg, X", "ADC zpg, X", "ROR zpg, X", "RRA zpg, X", "SEI impl", "ADC abs, Y", "NOP impl", "RRA abs, Y", "NOP abs, Y", "ADC abs, X", "ROR abs, X", "RRA abs, X"}
    {"NOP #", "STA X, ind", "NOP #", "SAX X, ind", "STY zpg", "STA zpg", "STX zpg", "SAX zpg", "DEY impl", "NOP #", "TAX impl", "ANE #", "STY abs", "STA abs", "STX abs", "SAX abs"}
    {"BCC rel", "STA ind, Y", "JAM", "SHA ind, Y", "STY zpg, X", "STA zpg, X", "STX zpg, Y", "SAX zpg, Y", "TYA impl", "STA abs, Y", "TXS impl", "TAS abs, Y", "SHY abs, X", "STA abs, X", "SHX abs, Y", "SHA abs, Y"}
    {"LDY #", "LDA X, ind", "LDX #", "LAX X, ind", "LDY zpg", "LDA zpg", "LDX zpg", "LAX zpg", "TAY impl", "LDA #", "TAX impl", "LXA #", "LDY abs", "LDA abs", "LDX abs", "LAX abs"}
    {"BCS rel", "LDA in, Y", "JAM", "LAX ind, Y", "LDY zpg, X", "LDA zpg, Y", "LDX zpg, Y", "LAX zpg, Y", "CLV impl", "LDA abs, Y", "TSX impl", "LAS abs, Y", "LDY abs, X", "LDA abs, X", "LDX abs, Y", "LAX abs, Y"}
    {"CPY #", "CMP X, ind", "NOP #", "DCP X, ind", "CPY zpg", "CMP zpg", "DEC zpg", "DCP zpg", "INY impl", "CMP #", "DEX impl", "SBX #", "CPY abs", "CMP abs", "DEC abs", "DCP abs"}
    {"BNE rel", "CMP ind, Y", "JAM", "DCP ind, Y", "NOP zpg, X", "CMP zpg, X", "DEC zpg, X", "DCP zpg, X", "CLD impl", "CMP abs, Y", "NOP impl", "DCP abs, Y", "NOP abs, X", "CMP abs, X", "DEC abs, X", "DCP abs, X"}
    {"CPX #", "SBC X, ind", "NOP #", "ISC X, ind", "CPX zpg", "SBC zpg", "INC zpg", "ISC zpg", "INX impl", "SBC #", "NOP impl", "USBC #", "CPX abs", "SBC abs", "INC abs", "ISC abs"}
    {"BEQ rel", "SBC ind, Y", "JAM", "ISC ind, Y", "NOP zpg, X", "SBC zpg, X", "INC zpg, X", "ISC zpg, X", "SED impl", "SBC abs, Y", "NOP impl", "ISC abs, Y", "NOP abs, X", "SBC abs, X", "INC abs, X", "ISC abs, X"}
    };
*/	
	uint8_t opcode = read8(cpu, addr); 
	uint8_t hi = opcode >> 4; 
	uint8_t lo = opcode & 0x0F;
//	snprintf(buffer, buflen, "%s\n", lookup_table_opcode[hi][lo]);
	
	// Delete this line when you're done
	//buffer[0] = 0;
	return 0;
}

mos6502_step_result_t
mos6502_step (mos6502_t * cpu)
{
	uint8_t opcode = read8(cpu, cpu->pc);
	uint8_t hi = opcode >> 4; 
	uint8_t lo = opcode & 0x0F; 
	decode_info_t decode_info; 
	
	printf("%x\n", opcode); 

	switch(opcode) {
		
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04: 
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0B:
		case 0x0C:
		case 0x0D: 
		case 0x0E:
		case 0x0F:

		case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                case 0x18:
                case 0x19:
                case 0x1A:
                case 0x1B:
                case 0x1C:
                case 0x1D:
                case 0x1E:
                case 0x1F:

		case 0x20:
                case 0x21:
                case 0x22:
                case 0x23:
                case 0x24:
                case 0x25:
                case 0x26:
                case 0x27:
                case 0x28:
                case 0x29:
                case 0x2A:
                case 0x2B:
                case 0x2C:
                case 0x2D:
                case 0x2E:
                case 0x2F:

		case 0x30:
                case 0x31:
                case 0x32:
                case 0x33:
                case 0x34:
                case 0x35:
                case 0x36:
                case 0x37:
                case 0x38:
                case 0x39:
                case 0x3A:
                case 0x3B:
                case 0x3C:
                case 0x3D:
                case 0x3E:
                case 0x3F:

		case 0x40:
                case 0x41:
                case 0x42:
                case 0x43:
                case 0x44:
                case 0x45:
                case 0x46:
                case 0x47:
                case 0x48:
                case 0x49:
                case 0x4A:
                case 0x4B:
                case 0x4C:
                case 0x4D:
                case 0x4E:
                case 0x4F:


		case 0x50:
                case 0x51:
                case 0x52:
                case 0x53:
                case 0x54:
                case 0x55:
                case 0x56:
                case 0x57:
                case 0x58:
                case 0x59:
                case 0x5A:
                case 0x5B:
                case 0x5C:
                case 0x5D:
                case 0x5E:
                case 0x5F:

		case 0x60:
                case 0x61:
                case 0x62:
                case 0x63:
                case 0x64:
                case 0x65:
                case 0x66:
                case 0x67:
                case 0x68:
                case 0x69:
                case 0x6A:
                case 0x6B:
                case 0x6C:
                case 0x6D:
                case 0x6E:
                case 0x6F:

		case 0x70:
                case 0x71:
                case 0x72:
                case 0x73:
                case 0x74:
                case 0x75:
                case 0x76:
                case 0x77:
                case 0x78:
                case 0x79:
                case 0x7A:
                case 0x7B:
                case 0x7C:
                case 0x7D:
                case 0x7E:
                case 0x7F:

		case 0x80:
                case 0x81:
                case 0x82:
                case 0x83:
                case 0x84:
                case 0x85:
			STA_handler(cpu); 
                case 0x86:
                case 0x87:
                case 0x88:
                case 0x89:
                case 0x8A:
                case 0x8B:
                case 0x8C:
                case 0x8D:
                case 0x8E:
                case 0x8F:

		case 0x90:
                case 0x91:
                case 0x92:
                case 0x93:
                case 0x94:
                case 0x95:
                case 0x96:
                case 0x97:
                case 0x98:
                case 0x99:
                case 0x9A:
			TXS_handler(cpu);
                case 0x9B:
                case 0x9C:
                case 0x9D:
                case 0x9E:
		case 0x9F:

		case 0xA0:
                case 0xA1:
                case 0xA2:
                case 0xA3:
                case 0xA4:
                case 0xA5:
                case 0xA6:
                case 0xA7:
                case 0xA8:
                case 0xA9:
			LDA_handler(cpu);
                case 0xAA:
                case 0xAB:
                case 0xAC:
                case 0xAD:
                case 0xAE:
                case 0xAF:

		case 0xB0:
                case 0xB1:
                case 0xB2:
                case 0xB3:
                case 0xB4:
                case 0xB5:
                case 0xB6:
                case 0xB7:
                case 0xB8:
                case 0xB9:
                case 0xBA:
                case 0xBB:
                case 0xBC:
                case 0xBD:
                case 0xBE:
                case 0xBF:

		case 0xC0:
                case 0xC1:
                case 0xC2:
                case 0xC3:
                case 0xC4:
                case 0xC5:
                case 0xC6:
                case 0xC7:
                case 0xC8:
                case 0xC9:
                case 0xCA:
                case 0xCB:
                case 0xCC:
                case 0xCD:
                case 0xCE:
                case 0xCF:

		case 0xD0:
                case 0xD1:
                case 0xD2:
                case 0xD3:
                case 0xD4:
                case 0xD5:
                case 0xD6:
                case 0xD7:
                case 0xD8:
			CLD_handler(cpu); 
                case 0xD9:
                case 0xDA:
                case 0xDB:
                case 0xDC:
                case 0xDD:
                case 0xDE:
                case 0xDF:

		case 0xE0:
                case 0xE1:
                case 0xE2:
                case 0xE3:
                case 0xE4:
                case 0xE5:
                case 0xE6:
                case 0xE7:
                case 0xE8:
                case 0xE9:
                case 0xEA:
                case 0xEB:
                case 0xEC:
                case 0xED:
                case 0xEE:
                case 0xEF:

		case 0xF0:
                case 0xF1:
                case 0xF2:
                case 0xF3:
                case 0xF4:
                case 0xF5:
                case 0xF6:
                case 0xF7:
                case 0xF8:
                case 0xF9:
                case 0xFA:
                case 0xFB:
                case 0xFC:
                case 0xFD:
                case 0xFE:
                case 0xFF:

		default: 
			break; 


	}
	mos6502_advance_clk(cpu, instr_cycles[opcode]);
	return MOS6502_STEP_RESULT_SUCCESS;
}

/* 
 * Addressing mode functions, calculate effective addresses
 */

static void imp() { 
// implied 
}

static void acc() { 
// accumulator
} 

static void imm() { 
// immediate 
ea = pc++; // what the hell is ea? 
}

// add with carry
void ADC_handler(mos6502_t *cpu) {

}

// and with accumulator
void AND_handler(mos6502_t *cpu) { 

}

// arithmetic shift left
void ASL_handler(mos6502_t *cpu) {

}

// branch on carry clear 
void BCC_handler(mos6502_t *cpu) { 

}

// branch on carry set 
void BCS_handler(mos6502_t *cpu) { 

}

// branch on equal (zero set) 
void BEQ_handler(mos6502_t *cpu) { 

}

// bit test 
void BIT_handler(mos6502_t *cpu) { 

}

// branch on minus (negative set)  
void BMI_handler(mos6502_t *cpu) { 

}

// branch on not equal (zero clear) 
void BNE_handler(mos6502_t *cpu) { 

}

// branch on plus (negative clear) 
void BPL_handler(mos6502_t *cpu) { 

}

// break/interrupt 
void BRK_handler(mos6502_t *cpu) { 

}

// branch on overflow clear 
void BVC_handler(mos6502_t *cpu) { 

}

// branch on overflow set 
void BVS_handler(mos6502_t *cpu) { 

}

// clear carry 
void CLC_handler(mos6502_t *cpu) { 

}

// clear decimal
void CLD_handler(mos6502_t *cpu) { 
	printf("CLD handler\n"); 
	cpu->p.d = 0; 
	printf("%d\n", cpu->p.d); 
	cpu->pc = cpu->pc + (uint16_t)1; 
}

void CLI_handler(mos6502_t *cpu) {

}

void CLV_handler(mos6502_t *cpu) { 

}

void CMP_handler(mos6502_t *cpu) { 

}

void CPX_handler(mos6502_t *cpu) { 

}

void CPY_handler(mos6502_t *cpu) { 

}

void DEC_handler(mos6502_t *cpu) { 

}

void DEX_handler(mos6502_t *cpu) {

}

void DEY_handler(mos6502_t *cpu) { 

}

void EOR_handler(mos6502_t *cpu) { 

}

void INC_handler(mos6502_t *cpu) { 

}

void INX_handler(mos6502_t *cpu) { 

}

void INY_handler(mos6502_t *cpu) { 

}

void JMP_handler(mos6502_t *cpu) { 

}

void JSR_handler(mos6502_t *cpu) { 

}

void LDA_handler(mos6502_t *cpu) { 
	printf("LDA handler\n"); 
	printf("operand: %x\n", read16(cpu, cpu->pc));
	cpu->pc = cpu-> + (uint16_t)2;
}

void LDX_handler(mos6502_t *cpu) {
	printf("LDX handler\n"); 
	printf("operand: %x\n", read16(cpu, cpu->pc)); 
	cpu->pc = cpu->pc + (uint16_t)2;
}

void LDY_handler(mos6502_t *cpu) { 

}

void LSR_handler(mos6502_t *cpu) {

}

void NOP_handler(mos6502_t *cpu) { 

}

void ORA_handler(mos6502_t *cpu) { 

}

void PHA_handler(mos6502_t *cpu) {

}

void PHP_handler(mos6502_t *cpu) {

}

void PLA_handler(mos6502_t *cpu) {

}

void PLP_handler(mos6502_t *cpu) {

}

void ROL_handler(mos6502_t *cpu) {

}

void ROR_handler(mos6502_t *cpu) {

}

void RTI_handler(mos6502_t *cpu) {

}

void RTS_handler(mos6502_t *cpu) {

}

void SBC_handler(mos6502_t *cpu) {

}

void SEC_handler(mos6502_t *cpu) { 

}

void SED_handler(mos6502_t *cpu) {

}

void SEI_handler(mos6502_t *cpu) { 

}

void STA_handler(mos6502_t *cpu) {
	printf("STA handler\n");
	printf("operand : %x\n", read16(cpu, cpu->pc));
        cpu->pc = cpu->pc + (uint16_t)2; 	
	
}

void STX_handler(mos6502_t *cpu) {

}

void STY_handler(mos6502_t *cpu) {

}

void TAX_handler(mos6502_t *cpu) {

}

void TAY_handler(mos6502_t *cpu) {

}

void TSX_handler(mos6502_t *cpu) {

}

void TXA_handler(mos6502_t *cpu) { 

}

void TXS_handler(mos6502_t *cpu) {
	printf("TXS handler\n"); 
	cpu->sp = cpu->x;
	printf("X register : %x, A register : %x, Y register: %x\n"); 	      cpu->pc = cpu->pc + (uint8_t)1; 
}

void TYA_handler(mos6502_t *cpu) { 

}


/*
 * Illegal opcodes are below
 */

