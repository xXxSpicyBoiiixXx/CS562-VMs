;; 
; Author: Md Ali 
; Date: 01/16/2022 
; Description: An implementation for the classic game Snake utilzing the 6502 processor 
; Instruction: Use a cross compiler for modern day system to compile this code to etiher cc65 or any other 6502 cross compliation. To change direction in this version use the values 'W' 'A' 'S' 'D' 
; Version: 01

;; Here we define the apple and snake's characteristcs. 
define appleL		$00		;; Screen location of apple, low byte
define appleH		$01 		;; Screen location of apple, high byte 
define snakeHeadL	$10		;; Screen location of snake head, low byte 
define snakeHeadH	$11		;; Screen location of snake head, high byte 
define snakeBodyStart 	$12 		;; Start of snake body byte pairs 
define snakeDirection	$02 		;; Direction of snake
define snakeLength	$03		;; snake length, in bytes 

;; Given the direction of each user interrupt on the processor 
define movingUp		1 
define movingRight	2
define movingDown	4
define movingLeft	8

;; ASCII key value aka W,A,S,D
define ASCII_w		$77
define ASCII_a		$61
define ASCII_s		$73
define ASCII_d		$64

;; Defining system level varaibles 
define sysRandom	$fe 
define sysLastKey	$ff 

;; JSR/RTS values 

	jsr init			;; inital jump 
	jsr loop			;; looping for jump values 

init: 
	jsr initSnake			;; initializing snake 
	jsr generateApplePosition	;; generates apple
	rts

initSnake: 
	lda #movingRight		;; staring direction 
	sta snakeDirection 
	
	lda #4				;; starting length of 2
	sta snakeLength

	lda #$11 
	sta snakeHeadL 
	lda #$10 
	sta snakeBodyStart
	lda #$0f 
	sta $14 
	




















