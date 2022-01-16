	LDX #$00
	LDY #$00
firstloop: 
	TXA 
	STA $0200, Y 
	PHA
	INX
	INY
	CPY #$10
	BNE firstloop		;; Loops until Y is $10 
secondloop: 
	PLA 
	STA $0200, Y
	INY
	CPY #$20		;; Loops until Y is $20 
	BNE secondloop
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Here, X holds the picel color, and Y hold the postition of the cur-
;; rrent pixel. The first loop draws the current color as a pixed via 
;; register A. The number on register A is then increments the color 
;; and position. This is for the first loop. ;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; For the second loop we have that it pops values off the stack, dr-
;; aws a cikir as a pixel. This should have a mirror effect from the
;; first loop. ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
				
