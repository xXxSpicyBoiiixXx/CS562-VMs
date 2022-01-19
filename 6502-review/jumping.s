;; How jumping works in 6502 
	LDA #$03
	JMP there 
	BRK 
	BRK 
	BRK
there: 
	STA $0200

;; JSR/RTS (jump to subroutine and return to subroutine) 

	JSR init		;; This jumps to the init label 
	JSR loop 		;; This jumps to the loop label
	JSR end 		;; jumps to break label 

init:
	LDX #$00 		;; This set register X to $00
	RTS			;; We then return to the next instrut

loop:
	INX			;; Increments the register X 
	CPX #$05 		;; compares X with $05 
	BNE loop		;; branch if not equals 
	RTS 			;; Reseted to JSR end 

end:
	BRK			;; breaks the loop




