// add with carry
void ADC_handler(mos6502_t *);

// and with accumulator
void AND_handler(mos6502_t *);

// arithmetic shift left
void ASL_handler(mos6502_t *);

// branch on carry clear 
void BCC_handler(mos6502_t *);

// branch on carry set 
void BCS_handler(mos6502_t *);

// branch on equal (zero set) 
void BEQ_handler(mos6502_t *);

// bit test 
void BIT_handler(mos6502_t *);

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

// comapre with accumulator 
void CMP_handler(mos6502_t *); 

// compare with X
void CPX_handler(mos6502_t *);

// compare with Y 
void CPY_handler(mos6502_t *);

// decrement
void DEC_handler(mos6502_t *); 

// decrement X
void DEX_handler(mos6502_t *);

// decrement Y
void DEY_handler(mos6502_t *); 

// exclusive or (with accumulator) 
void EOR_handler(mos6502_t *); 

// increment 
void INC_handler(mos6502_t *);

// increment X
void INX_handler(mos6502_t *); 

// increment Y
void INY_handler(mos6502_t *);

// Jump 
void JMP_handler(mos6502_t *); 

// Jump subroutine 
void JSR_handler(mos6502_t *);

// Load accumulator 
void LDA_handler(mos6502_t *); 

// Load X
void LDX_handler(mos6502_t *); 

// Load Y
void LDY_handler(mos6502_t *);

// Logical shift right 
void LSR_handler(mos6502_t *); 

// No operation 
void NOP_handler(mos6502_t *);

// Or with accumulator 
void ORA_handler(mos6502_t *);

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

// rotate right 
void ROR_handler(mos6502_t *); 

// return from interrupt
void RTI_handler(mos6502_t *); 

// return from subroutine 
void RTS_handler(mos6502_t *);

// subtract with carry 
void SBC_handler(mos6502_t *); 

// set carry 
void SEC_handler(mos6502_t *);

// set decimal 
void SED_handler(mos6502_t *);

// set interrupt disable
void SEI_handler(mos6502_t *); 

// store accumulator 
void STA_handler(mos6502_t *);

// store X
void STX_handler(mos6502_t *); 

// store Y
void STY_handler(mos6502_t *); 

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


