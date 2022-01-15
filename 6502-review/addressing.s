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


