; StringConversion.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on TM4C123
; ECE319K lab 7 number to string conversions
;
; Used in ECE319K Labs 7,8,9,10. You write these two functions

 
    EXPORT   Dec2String
    EXPORT   Fix2String
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    PRESERVE8

  
;-----------------------Dec2String-----------------------
; Convert a 32-bit number into unsigned decimal format
; String the string into the empty array add null-termination
; Input: R0 (call by value) 32-bit unsigned number
;        R1 pointer to empty array
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
saveR0 EQU 0 
saveR1 EQU 4
	
Dec2String
	PUSH{R4, R5, LR} 
	MOV R4, #-1 ; count
	SUB SP, #8
	STR R0, [SP, #saveR0]  
Counter
	MOV R5, #10
	UDIV R0, R0, R5
	ADD R4, R4, #1 
	CMP R0, #0 
	BNE Counter
    LDR R0, [SP, #saveR0] 
	ADD R1, R1, R4
loop
	STR R0, [SP, #saveR0]  
	STR R1, [SP, #saveR1]  
	MOV R1, #10
	BL Modulus 
	LDR R1, [SP, #saveR1] 
	ADD R0, #0x30
	
	STRB R0, [R1] 
	SUB R1, #0x01
	LDR R0, [SP, #saveR0] 
	
	MOV R5, #10
	UDIV R0, R0, R5
	CMP R0, #0 
	BEQ Dec2Done
	B loop
Dec2Done
	MOV R5, #0 ; null-terminate
	ADD R1, R1, R4
	ADD R1, R1, #2
	STRB R5, [R1] 
	ADD SP, #8
	POP{R4, R5, LR} 

    BX LR
;* * * * * * * * End of Dec2String * * * * * * * *


; -----------------------Fix2String----------------------
; Create characters for LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
;          R1 pointer to empty array
; Outputs: none
; E.g., R0=0,    then create "0.000 "
;       R0=3,    then create "0.003"
;       R0=89,   then create "0.089"
;       R0=123,  then create "0.123"
;       R0=9999, then create "9.999"
;       R0>9999, then create "*.***"
; Invariables: This function must not permanently modify registers R4 to R11
num1 EQU 0 ;MSB
num2 EQU 4
num3 EQU 8
num4 EQU 12 ;LSB
savefR0 EQU 16
savefR1 EQU 20


Fix2String
    PUSH{R4, R5, LR}
	SUB SP, #24

    ; Check if greater than 9999
    LDR R3,= 9999
    CMP R0, R3
    BHI Asterick
	
    STR R0, [SP, #savefR0]  
	STR R1, [SP, #savefR1]  
	MOV R1, #10
	BL Modulus 
	LDR R1, [SP, #savefR1] 
	ADD R0, #0x30	
	STR R0, [SP, #num4] 
	LDR R0, [SP, #savefR0] 
	MOV R5, #10
	UDIV R0, R0, R5
	
	STR R0, [SP, #savefR0]  
	STR R1, [SP, #savefR1]  
	MOV R1, #10
	BL Modulus 
	LDR R1, [SP, #savefR1] 
	ADD R0, #0x30	
	STR R0, [SP, #num3] 
	LDR R0, [SP, #savefR0] 
	MOV R5, #10
	UDIV R0, R0, R5
	
	STR R0, [SP, #savefR0]  
	STR R1, [SP, #savefR1]  
	MOV R1, #10
	BL Modulus 
	LDR R1, [SP, #savefR1] 
	ADD R0, #0x30	
	STR R0, [SP, #num2] 
	LDR R0, [SP, #savefR0] 
	MOV R5, #10
	UDIV R0, R0, R5
	
	STR R0, [SP, #savefR0]  
	STR R1, [SP, #savefR1]  
	MOV R1, #10
	BL Modulus 
	LDR R1, [SP, #savefR1] 
	ADD R0, #0x30	
	STR R0, [SP, #num1] 
	LDR R0, [SP, #savefR0] 
	MOV R5, #10
	UDIV R0, R0, R5

ArraySet
	LDR R3, [SP, #num1] 
	STR R3, [R1] 
	MOV R3, #0x2E
	STR R3, [R1, #1] 
	LDR R3, [SP, #num2] 
	STR R3, [R1, #2] 
	LDR R3, [SP, #num3] 
	STR R3, [R1, #3] 
	LDR R3, [SP, #num4] 
	STR R3, [R1, #4] 
    ; Add space character
    MOV R3, #0x20
    STRB R3, [R1, #5]
	;null terminate
	MOV R3, #0
    STRB R3, [R1, #6]
	B FixDone 

; If input number is greater than 9999
Asterick
        ;Add asterisk 
    MOV R3, #0x2A
    STRB R3, [R1]
	MOV R3, #0x2E
    STRB R3, [R1, #1]
	MOV R3, #0x2A
    STRB R3, [R1, #2]
	MOV R3, #0x2A
    STRB R3, [R1, #3]
	MOV R3, #0x2A
    STRB R3, [R1, #4]
	MOV R3, #0
    STRB R3, [R1, #5]
FixDone
	ADD SP, #24
    POP{R4, R5, LR}

    BX LR


; Inputs:  R0 is x
;          R1 is D
; Outputs: R0 is R
Modulus 
	PUSH {R4, LR}
	UDIV R4, R0, R1
	MUL R4, R1
	SUB R0, R0, R4
	POP {R4, LR}
	
	BX LR


     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
