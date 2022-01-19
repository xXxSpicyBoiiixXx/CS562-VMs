; Fibonacci cacluclator in 6502 assembley 


LDX #$01            ;; x = 1 
STX $00             ;; Stores x 

SEC                 ;; clean carry 
LDY #$19            ;; 25 in Hex 
TYA                 ;; Transfers the y register to accumulator
SBC #$03            ;; Handles the alogrithm 
TAY                 ;; Transfers the accumulator to y 

CLC                 ;; clean carry 
LDA #$02            ;; a = 2
STA $01             ;; stores a 

loop:
    LDX $01         ;; x = a 
    ADC $00         ;; a += x 
    STA $01         ;; store a 
    STX $00         ;; stores x 
    DEY             ;; y -= 1
    BNE loop;       
