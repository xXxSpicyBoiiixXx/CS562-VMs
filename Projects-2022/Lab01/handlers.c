#include <mos6502/handlers.h>
#include <rc.h>
#include <base.h>
#include <membus.h>
#include <timekeeper.h>
#include <mos6502/vmcall.h>
#include <mos6502/mos6502.h>


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

}

// clear interrupt disable
void CLI_handler(mos6502_t *cpu) {

}	

// clear overflow 
void CLV_handler(mos6502_t *cpu) {

}

// comapre with accumulator 
void CMP_handler(mos6502_t *cpu) {

}	

// compare with X
void CPX_handler(mos6502_t *cpu) {

}

// compare with Y 
void CPY_handler(mos6502_t *cpu) { 

}

// decrement
void DEC_handler(mos6502_t *cpu) {

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

// increment 
void INC_handler(mos6502_t *cpu) {

}

// increment X
void INX_handler(mos6502_t *cpu) {

}	

// increment Y
void INY_handler(mos6502_t *cpu) {

}

// Jump 
void JMP_handler(mos6502_t *cpu) {

}

// Jump subroutine 
void JSR_handler(mos6502_t *cpu) {

}

// Load accumulator 
void LDA_handler(mos6502_t *cpu) {

}	

// Load X
void LDX_handler(mos6502_t *cpu) {

}	

// Load Y
void LDY_handler(mos6502_t *cpu) {

}

// Logical shift right 
void LSR_handler(mos6502_t *cpu) { 

}	

// No operation 
void NOP_handler(mos6502_t *cpu) {

}

// Or with accumulator 
void ORA_handler(mos6502_t *cpu) { 

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

// rotate right 
void ROR_handler(mos6502_t *cpu) {

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

// store X
void STX_handler(mos6502_t *cpu) {

}	

// store Y
void STY_handler(mos6502_t *cpu) {

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


