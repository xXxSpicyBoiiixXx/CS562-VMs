#include <rc.h>
#include <base.h>
#include <membus.h>
#include <timekeeper.h>
#include <mos6502/vmcall.h>
#include <mos6502/mos6502.h>

#include <string.h>

void (*op_table[16][16])(mos6502_t *cpu) { 
	{handle_BRK, handle_ORA_IDX_IDR, handle_JAM, handle_SLO_IDX_IDR, handle_NOP_ZP, handle_ORA_ZP, handle_ASL_ZP, handle_SLO_ZP, handle_PHP, handle_ORA, handle_ASL, handle_ANC, handle_NOP_ABS, handle_ORA_ABS, handle_ASL_ABS, handle_SLO_ABS}
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
	// FILL ME IN
	/*      // FILL ME IN
     *      string *lookup_table_opcode[16][16] = { 
     *          {"BRK impl", "ORA X, ind", "JAM", "SLO X, ind", "NOP zpg", "ORA zpg", "ASL zpg", "SLO zpg", "PHP impl", "ORA #", "ASL A", "ANC #", "NOP abs", "ORA abs", "ASL abs", "SLO abs"}, 
     *              {"BPL rel", "ORA ind, Y", "JAM", "SLO ind, Y", "NOP zpg, X", "ORA zpg, X", "ASL zpg, X", "SLO zpg, X", "CLC impl", "ORA abs, Y", "NOP impl", "SLO abs, Y","NOP abs, X", "ORA abs, X", "ASL abs, X", "SLO abs, X"} 
     *                  {"JSR abs", "AND X, ind", "JAM", "RLA X, ind", "BIT zpg", "AND zpg", "ROL zpg", "RLA zpg", "PLP impl", "AND #", "ROL A", "ANC #", "BIT abs", "AND abs", "ROL abs", "RLA abs"}
     *                      {"BMI rel", "AND ind, Y", "JAM", "RLA ind, Y", "NOP zpg, X", "AND zpg, X", "ROL zpg, X", "RLA zpg, X", "SEC impl", "AND abs, Y", "NOP impl", "RLA abs, Y", "NOP abs, X", "AND abs, X", "ROL abs, X", "RLA abs, X"}
     *                          {"RTI impl", "EOR X, ind", "JAM", "SRE X, ind", "NOP zpg", "EOR zpg", "LSR zpg", "SRE zpg", "PHA impl", "EOR #", "LSR A", "ALR #", "JMP abs", "EOR abs", "LSR abs", "SRE abs"}
     *                              {"BVC rel", "EOR ind, Y", "JAM", "SRE ind, Y", "NOP zpg, X", "EOR zpg, X", "LSR zpg, X", "SRE zpg, X", "CLI impl", "EOR abs, Y", "NOP impl", "SRE abs, Y", "NOP abs, X", "EOR abs, X", "LSR abs, X", "SRE abs, X"}
     *                                  {"RTS impl", "ADC X, ind", "JAM", "RRA X, ind", "NOP zpg", "ADC zpg", "ROR zpg", "RRA zpg", "PLA impl", "ADC #", "ROR A", "ARR #", "JMP ind", "ADC abs", "ROR abs", "RRA abs"}
     *                                      {"BVS rel", "ADC ind, Y", "JAM", "RRA ind, Y", "NOP zpg, X", "ADC zpg, X", "ROR zpg, X", "RRA zpg, X", "SEI impl", "ADC abs, Y", "NOP impl", "RRA abs, Y", "NOP abs, Y", "ADC abs, X", "ROR abs, X", "RRA abs, X"}
     *                                          {"NOP #", "STA X, ind", "NOP #", "SAX X, ind", "STY zpg", "STA zpg", "STX zpg", "SAX zpg", "DEY impl", "NOP #", "TAX impl", "ANE #", "STY abs", "STA abs", "STX abs", "SAX abs"}
     *                                              {"BCC rel", "STA ind, Y", "JAM", "SHA ind, Y", "STY zpg, X", "STA zpg, X", "STX zpg, Y", "SAX zpg, Y", "TYA impl", "STA abs, Y", "TXS impl", "TAS abs, Y", "SHY abs, X", "STA abs, X", "SHX abs, Y", "SHA abs, Y"}
     *                                                  {"LDY #", "LDA X, ind", "LDX #", "LAX X, ind", "LDY zpg", "LDA zpg", "LDX zpg", "LAX zpg", "TAY impl", "LDA #", "TAX impl", "LXA #", "LDY abs", "LDA abs", "LDX abs", "LAX abs"}
     *                                                      {"BCS rel", "LDA in, Y", "JAM", "LAX ind, Y", "LDY zpg, X", "LDA zpg, Y", "LDX zpg, Y", "LAX zpg, Y", "CLV impl", "LDA abs, Y", "TSX impl", "LAS abs, Y", "LDY abs, X", "LDA abs, X", "LDX abs, Y", "LAX abs, Y"}
     *                                                          {"CPY #", "CMP X, ind", "NOP #", "DCP X, ind", "CPY zpg", "CMP zpg", "DEC zpg", "DCP zpg", "INY impl", "CMP #", "DEX impl", "SBX #", "CPY abs", "CMP abs", "DEC abs", "DCP abs"}
     *                                                              {"BNE rel", "CMP ind, Y", "JAM", "DCP ind, Y", "NOP zpg, X", "CMP zpg, X", "DEC zpg, X", "DCP zpg, X", "CLD impl", "CMP abs, Y", "NOP impl", "DCP abs, Y", "NOP abs, X", "CMP abs, X", "DEC abs, X", "DCP abs, X"}
     *                                                                  {"CPX #", "SBC X, ind", "NOP #", "ISC X, ind", "CPX zpg", "SBC zpg", "INC zpg", "ISC zpg", "INX impl", "SBC #", "NOP impl", "USBC #", "CPX abs", "SBC abs", "INC abs", "ISC abs"}
     *                                                                      {"BEQ rel", "SBC ind, Y", "JAM", "ISC ind, Y", "NOP zpg, X", "SBC zpg, X", "INC zpg, X", "ISC zpg, X", "SED impl", "SBC abs, Y", "NOP impl", "ISC abs, Y", "NOP abs, X", "SBC abs, X", "INC abs, X", "ISC abs, X"}
     *                                                                          };
     *                                                                          */  
	// Delete this line when you're done
	//buffer[0] = 0;
	
	uint8_t opcode = read8(cpu, addr); 
	uint8_t hi = opcode >> 4; 
	uint8_t lo = opcode & 0x0F; 
	
	return 0;
}

mos6502_step_result_t
mos6502_step (mos6502_t * cpu)
{
	uint8_t opcode = read8(cpu, cpu->pc);

	// FILL ME IN

	mos6502_advance_clk(cpu, instr_cycles[opcode]);
	return MOS6502_STEP_RESULT_SUCCESS;
}
