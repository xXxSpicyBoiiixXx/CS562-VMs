#pragma once 

#include <stdint.h>
#include <stdbool.h>


#include <mos6502/mos6502.h>

// add with carry family
void ADC_handler(mos6502_t *);
void ADC_ZP_hander(mos6502_t *);
void ADC_ZPX_handler(mos6502_t *); 
void ADC_ABS_handler(mos6502_t *);
void ADC_ABSX_handler(mos6502_t *);
void ADC_ABSY_handler(mos6502_t *);
void ADC_IDX_IDR_handler(mos6502_t *);
void ADC_IDR_IDY_handler(mos6502_t *);

// and with accumulator family 
void AND_handler(mos6502_t *);
void AND_ZP_handler(mos6502_t *);
void AND_ZPX_handler(mos6502_t *);
void AND_ABS_handler(mos6502_t *);
void AND_ABSX_handler(mos6502_t *);
void AND_ABSY_handler(mos6502_t *);
void AND_IDX_IDR_handler(mos6502_t *);
void AND_IDR_IDY_handler(mos6502_t *);

// arithmetic shift left family
void ASL_handler(mos6502_t *);
void ASL_ZP_handler(mos6502_t *);
void ASL_ZPX_handler(mos6502_t *);
void ASL_ABS_handler(mos6502_t *);
void ASL_ABSX_handler(mos6502_t *);

// branch on carry clear 
void BCC_handler(mos6502_t *);

// branch on carry set 
void BCS_handler(mos6502_t *);

// branch on equal (zero set) 
void BEQ_handler(mos6502_t *);

// bit test 
void BIT_handler(mos6502_t *);
void BIT_ABS_handler(mos6502_t *); 

// branch on minus (negative set)  
void BMI_handler(mos6502_t *);

// branch on not equal (zero clear) 
void BNE_handler(mos6502_t *);

// branch on plus (negative clear) 
void BPL_handler(mos6502_t *);

// break/interrupt
void BRK_handler(mos6502_t *);

// branch on overflow clear
void BVC_handler(mos6502_t *);

// branch on overflow set 
void BVS_handler(mos6502_t *);

// clear carry 
void CLC_handler(mos6502_t *);

// clear decimal 
void CLD_handler(mos6502_t *);

// clear interrupt disable
void CLI_handler(mos6502_t *); 

// clear overflow 
void CLV_handler(mos6502_t *);

// comapre with accumulator family 
void CMP_handler(mos6502_t *); 
void CMP_ZP_handler(mos6502_t *);
void CMP_ZPX_handler(mos6502_t *);
void CMP_ABS_handler(mos6502_t *);
void CMP_ABSX_handler(mos6502_t *);
void CMP_ABSY_handler(mos6502_t *);
void CMP_IDX_IDR_handler(mos6502_t *);
void CMP_IDR_IDY_handler(mos6502_t *);

// compare with X family 
void CPX_handler(mos6502_t *);
void CPX_ZP_handler(mos6502_t *);
void CPX_ABS_handler(mos6502_t *);

// compare with Y family 
void CPY_handler(mos6502_t *);
void CPY_ZP_handler(mos6502_t *);
void CPY_ABS_handler(mos6502_t *);

// decrement family 
void DEC_ZP_handler(mos6502_t *);
void DEC_ZPX_handler(mos6502_t *);
void DEC_ABS_handler(mos6502_t *);
void DEC_ABSX_handler(mos6502_t *);

// decrement X
void DEX_handler(mos6502_t *);

// decrement Y
void DEY_handler(mos6502_t *); 

// exclusive or (with accumulator) family 
void EOR_handler(mos6502_t *); 
void EOR_ZP_handler(mos6502_t *);
void EOR_ZPX_handler(mos6502_t *);
void EOR_ABS_handler(mos6502_t *);
void EOR_ABSX_handler(mos6502_t *);
void EOR_ABSY_handler(mos6502_t *);
void EOR_IDX_IDR_handler(mos6502_t *);
void EOR_IDR_IDY_handler(mos6502_t *);

// increment family 
void INC_handler(mos6502_t *);
void INC_ZP_handler(mos6502_t *);
void INC_ZPX_handler(mos6502_t *);
void INC_ABS_handler(mos6502_t *);
void INC_ABSX_handler(mos6502_t *);

// increment X
void INX_handler(mos6502_t *); 

// increment Y
void INY_handler(mos6502_t *);

// Jump family  
void JMP_ABS_handler(mos6502_t *);
void JMP_IDR_handler(mos6502_t *);

// Jump subroutine 
void JSR_handler(mos6502_t *);

// Load accumulator family 
void LDA_handler(mos6502_t *);
void LDA_ZP_handler(mos6502_t *);
void LDA_ZPX_handler(mos6502_t *);
void LDA_ABS_handler(mos6502_t *);
void LDA_ABSX_handler(mos6502_t *);
void LDA_ABSY_handler(mos6502_t *);
void LDA_IDX_IDR_handler(mos6502_t *);
void LDA_IDR_IDY_handler(mos6502_t *);

// Load X family
void LDX_handler(mos6502_t *); 
void LDX_ZP_handler(mos6502_t *);
void LDX_ZPY_handler(mos6502_t *);
void LDX_ABS_handler(mos6502_t *);
void LDX_ABSY_handler(mos6502_t *);

// Load Y family
void LDY_handler(mos6502_t *);
void LDY_ZP_handler(mos6502_t *);
void LDY_ZPX_handler(mos6502_t *);
void LDY_ABS_handler(mos6502_t *);
void LDY_ABSX_handler(mos6502_t *);

// Logical shift right family 
void LSR_handler(mos6502_t *);
void LSR_ZP_handler(mos6502_t *);
void LSR_ZPX_handler(mos6502_t *);
void LSR_ABS_handler(mos6502_t *);
void LSR_ABSX_handler(mos6502_t *);

// No operation 
void NOP_handler(mos6502_t *);

// Or with accumulator family
void ORA_handler(mos6502_t *);
void ORA_ZP_handler(mos6502_t *);
void ORA_ZPX_handler(mos6502_t *);
void ORA_ABS_handler(mos6502_t *);
void ORA_ABSX_handler(mos6502_t *);
void ORA_ABSY_handler(mos6502_t *);
void ORA_IDX_IDR_handler(mos6502_t *);
void ORA_IDR_IDY_handler(mos6502_t *);

// push accumulator 
void PHA_handler(mos6502_t *);

// push processor status (SR) 
void PHP_handler(mos6502_t *); 

// pull accumulator
void PLA_handler(mos6502_t *); 

// pull accumulator status (SR)
void PLP_handler(mos6502_t *); 

// rotate left 
void ROL_handler(mos6502_t *); 
void ROL_ZP_handler(mos6502_t *);
void ROL_ZPX_handler(mos6502_t *);
void ROL_ABS_handler(mos6502_t *);
void ROL_ABSX_handler(mos6502_t *);

// rotate right 
void ROR_handler(mos6502_t *); 
void ROR_ZP_handler(mos6502_t *);
void ROR_ZPX_handler(mos6502_t *);
void ROR_ABS_handler(mos6502_t *);
void ROR_ABSX_handler(mos6502_t *);

// return from interrupt
void RTI_handler(mos6502_t *); 

// return from subroutine 
void RTS_handler(mos6502_t *);

// subtract with carry 
void SBC_handler(mos6502_t *); 
void SBC_ZP_handler(mos6502_t *);
void SBC_ZPX_handler(mos6502_t *);
void SBC_ABS_handler(mos6502_t *);
void SBC_ABSX_handler(mos6502_t *);
void SBC_ABSY_handler(mos6502_t *);
void SBC_IDX_IDR_handler(mos6502_t *);
void SBC_IDR_IDY_handler(mos6502_t *);

// set carry 
void SEC_handler(mos6502_t *);

// set decimal 
void SED_handler(mos6502_t *);

// set interrupt disable
void SEI_handler(mos6502_t *); 

// store accumulator 
void STA_handler(mos6502_t *);
void STA_ZP_handler(mos6502_t *);
void STA_ZPX_handler(mos6502_t *);
void STA_ABS_handler(mos6502_t *);
void STA_ABSX_handler(mos6502_t *);
void STA_ABSY_handler(mos6502_t *);
void STA_IDX_IDR_handler(mos6502_t *);
void STA_IDR_IDY_handler(mos6502_t *);

// store X
void STX_handler(mos6502_t *); 
void STX_ZP_handler(mos6502_t *);
void STX_ZPY_handler(mos6502_t *);
void STX_ABS_handler(mos6502_t *);

// store Y
void STY_handler(mos6502_t *); 
void STY_ZP_handler(mos6502_t *);
void STY_ZPX_handler(mos6502_t *);
void STY_ABS_handler(mos6502_t *);

// transfer accumulator to X
void TAX_handler(mos6502_t *); 

// transfer accumulator to Y
void TAY_handler(mos6502_t *); 

// transfer stack pointer to X
void TSX_handler(mos6502_t *);

// transfer X to accumulator 
void TXA_handler(mos6502_t *);

// transfer X to stack pointer 
void TXS_handler(mos6502_t *); 

// transfer Y to accumulator 
void TYA_handler(mos6502_t *); 

// Add Illegal Opcode handlers later. 
