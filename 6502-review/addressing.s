;; Absolute: $c000

STA $c000           ;; Store the value in the accumulator at memory location $c000

;; Zero page: $c0

STA $c0             ;; This is the same but generally faster and takes up less space as it only needs one byte. 

;; Zero page, X: $c0, X 

LDX #$01            ;; X is $01 
LDA #$aa            ;; A is $aa 
STA $a0, X          ;; Store the value of A at memory location $a1 
INX                 ;; Increment X 
STA $a0, X          ;; Store the value of A at memory location $a2 

;; If the result of the addition is larger than a single byte, the address wraps around: 

LDX #$05 
STA $$ff, X         ;; Store the value of A at memory location $04 

;; Zero page, Y: $c0, Y 

LDY #$01
LDA #$aa 
STA $a0, Y 
INY
STA $a0, Y 

;; Absolute, X and absolute, Y: $c000, x and $c000, Y

LDX #$01 
STA $0200, X        ;; Store the value of A at memory location $0201 

;; Immediate: #$c0, this is where addressing doesn't strictly deal with memory addresses -- this is the mode where actual values are used. 

LDX #$01            ;; Loads the value $01 into register X 
LDX $01             ;; loads the value at memory location $01 into register X

;; Relative : This is used for branching instruction.

    LDA #$01 
    CMP #$02 
    BNE notequal 
    STA $22         ;; You can switch this to 2222 where it will be three bytes long instead of two bytes 
notequal:
    BRK


;; Implicit: INX this doesn't deal with memory locations 

INX                 ;; increment the X register

;; Indirect: $c000  ;; This uses and absolute address to look up another address 

LDA #$01            ;; Loads register A with $01 
STA $f0             ;; Stores the value in memory location f0 
LDA #$cc            ;; Loads register A with $cc 
STA $f1             ;; Stores the value in memory location f1 
JMP ($00f0)         ;; dereferences to $cc01

;; Indexed indirect: ($c0, X) This one is a cross between zero page and indrirect

LDX #$01
LDA #$05
STA $01
LDA #$07
STA $02
LDY #$0a
STY $0705
LDA ($00,X)

;; Indirect Index   ;; here the zero page address is dereferenced and the Y reigster is added to the resulting address

LDY #$01 
LDA #$03 
STA $01 
LDA #$07
STA $02 
LDX #$0a 
STX $0704 
LDA ($01), Y 

;;;;;;;;;;;;;;;; Write programs using each of these as an exercise... 




