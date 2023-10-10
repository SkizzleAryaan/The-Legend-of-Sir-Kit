; BusyWait.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly

; Runs on TM4C123

; As part of Lab 7, students need to implement these two functions
; This file is in the inc folder so it automatically will be applied to labs 7 8 9 and 10


      EXPORT   SPIOutCommand
      EXPORT   SPIOutData

      AREA    |.text|, CODE, READONLY, ALIGN=2
      THUMB
      ALIGN
; Used in ECE319K Labs 7,8,9,10. You write these two functions

; ***********SPIOutCommand*****************
; This is a helper function that sends an 8-bit command to the LCD.
; Inputs: R0 = 32-bit command (number)
;         R1 = 32-bit SPI status register address
;         R2 = 32-bit SPI data register address
;         R3 = 32-bit GPIO port address for D/C
; Outputs: none
; Assumes: SPI and GPIO have already been initialized and enabled
; Note: must be AAPCS compliant
; Note: access to bit 6 of GPIO must be friendly
SPIOutCommand
; --UUU-- Code to write a command to the LCD
;1) Read the SPI status register (R1 has address) and check bit 4, 
;2) If bit 4 is high, loop back to step 1 (wait for BUSY bit to be low)
;3) Clear D/C (GPIO bit 6) to zero, be friendly (R3 has address)
;4) Write the command to the SPI data register (R2 has address)
;5) Read the SPI status register (R1 has address) and check bit 4, 
;6) If bit 4 is high, loop back to step 5 (wait for BUSY bit to be low)
	PUSH{R4, R5}
loopSR
    LDR R4, [R1] 
	AND R4, R4, #0x10
	CMP R4, #0
	BNE loopSR 
	LDR R4, [R3] 
	BIC R4, R4, #0x40
	STR R4, [R3] 
	STRB R0, [R2] 
loopSR2	
	LDR R5, [R1] 
	AND R5, R5, #0x10
	CMP R5, #0
	BNE loopSR2 
	POP{R4, R5}
   
    BX  LR             ;   return



; ***********SPIOutData*****************
; This is a helper function that sends an 8-bit data to the LCD.
; Inputs: R0 = 32-bit data (number)
;         R1 = 32-bit SPI status register address
;         R2 = 32-bit SPI data register address
;         R3 = 32-bit GPIO port address for D/C
; Outputs: none
; Assumes: SPI and GPIO have already been initialized and enabled
; Note: must be AAPCS compliant
; Note: access to bit 6 of GPIO must be friendly
SPIOutData
; --UUU-- Code to write data to the LCD
;1) Read the SPI status register (R1 has address) and check bit 1, 
;2) If bit 1 is low, loop back to step 1 (wait for TNF bit to be high)
;3) Set D/C (GPIO bit 6) to one, be friendly (R3 has address)
;4) Write the data to the SPI data register (R2 has address)
	PUSH{R4, R5}
loopSR3
	LDR R4, [R1] 
	AND R4, R4, #0x02
	CMP R4, #0
	BEQ loopSR3 
	LDR R1, [R3] 
	ORR R1, R1, #0x40
	STR R1, [R3] 
	STRB R0, [R2] 
	POP{R4, R5}
	
	
	
	
   
   


    BX  LR             ;return
;****************************************************

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
