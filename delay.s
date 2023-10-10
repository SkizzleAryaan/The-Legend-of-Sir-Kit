;Software delay functions
; Your name
; Date last modified
   AREA    |.text|, CODE, READONLY, ALIGN=2
   THUMB
   EXPORT Delay
;*********Delay**********************
; Software delay loop
; Input: R0 is count, the amount to delay in 100ns
; Output: none
      ALIGN 8
Delay NOP ;dummy operation
      NOP
      NOP
      NOP
      SUBS R0,R0,#1
      BNE  Delay
      BX   LR
      
   EXPORT Wait10ms
;*********Wait10ms**********************
; Software delay loop
; Input: R0 is count, the amount to delay in 10ms
; Output: none
Wait10ms
; implement this using AAPCS
      BX  LR
      END      
