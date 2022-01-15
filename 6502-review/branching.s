    LDX #$08        ;; Loading the value $08 into X 
decrement: 
    DEX             ;; Decrement X
    STX $0200       ;; Store $0200 in X 
    CPX #$03        ;; Compare the X value to $03 
    BNE decrement   ;; Shifting execution to the decrement label if the Z flag is set to 0 (two values not equal) otherwise it does nothing and we store X to $0201. 
    STX $0201       ;; The storing in X 
    BRK             ;; Break == Done

;; So the opposite of BNE is BEQ so if we wrote this in a way where we wanted it to break when get equal it would look something like this. 

    LDX #$08 
increase: 
    INX
    STX $0200
    CPX #$08
    BEQ increase
    STX $0201
    BRK

;; There is also BCC and BCS (Branch on carry clear and branch on carry set) are used to branch on the carry flag 

    LDX #$FF 
    INX 
    ;; I don't feel like doing the logic, but you get the point,
