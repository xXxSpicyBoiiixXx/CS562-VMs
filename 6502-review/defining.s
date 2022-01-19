define sysRandom 	$fe			;; an address 
define a_dozen		$0c			;; constant 0x000c 

LDA sysRandom					;; Loading sysRandom in register A 
LDX #a_dozen					;; Loading X with reference to 0x000c in 6502 processor


