;; We'll write the first program here, so let's take a look at changing colors on the screen. 

;; $ the dollar sign is used to represent a hexadecimal format

;; In the simulator we have memroy addresses from $0200 to $05ff 

;; The values $00 to $0f represent 16 different colors.

;; 

LDA #$01    ;; Load A with 01 corresponding to a color
STA $0200   ;; This store what we loaded into our register of A into the memory

            ;; We can keep doing this as such with different colors from the correpsonding insturctions 

LDA #$02
STA $0201
LDA #$03
STA $0202
LDA #$04
STA $0203 

            ;; We can keep doing this on repeat until the memory adrress of $05ff
