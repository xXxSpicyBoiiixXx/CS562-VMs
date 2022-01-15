LDA #$c0        ;; Loading the hex value $c0 into the register A 
TAX             ;; Transfer teh value in register A to register X
INX             ;; Increment the value in the X register 
ADC #$c4        ;; Add the hex value $c4 to register A 
BRK             ;; Break -- done boiiiiii

;; Okay hold up...

;; So the value in register A was orginal C0 but when we add C4 we get 184. Now we can't add the value 184 into a single byte as the max is $FF, to work around this there is a carry flag that was put in the 1 place. 

LDA #$80        ;; Loading the hex value $80 into the register A 
STA $01         ;; Storing the value in memory location $01 
ADC $01         ;; This command adds the value stored at memory location $01 to the register A so we get that $80 + $80 which equals $100, but this is bigger than $FF so reigster A is set to $00 and the carry flag is set. 

;; So TAX, transfers between register A to X 
;; So TAY, transfers between register A to Y 
;; So TXA, transfers between register X to A 
;; So TYA, transfers between register Y to A 

;; So let's rewrite this... 

LDA #$c0
TAY
INY
ADC #$c4
BRK

;; Now the opposite of ADC (addition with carry) is SBC (subtract with carry) 

LDA #$c0 
TAX 
INX 
SBC #$c4
LDA #$c0 
TAY 
INY 
SBC #$c4 
BRK


