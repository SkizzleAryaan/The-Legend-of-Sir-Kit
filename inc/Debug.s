;Debug.s
; Debugging dump
; Variables are in Debug.h    
; Put your names here
; Last modification: January 1, 2023
; Variables are in Debug.h    
; Debug.s and Debug.h are in the inc folder, so you can use it in other labs

      IMPORT DumpBuf1        
      IMPORT DumpBuf2        
; two 32-element buffers for debugging dump
      IMPORT DumpIndex        
; DumpIndex is the index from 0 to 31, 32 means full
      AREA    |.text|, CODE, READONLY, ALIGN=2
      THUMB
      EXPORT Debug_Init
;initialize recording
;buffers are empty when DumpIndex=0
;buffers are full when DumpIndex>49
Debug_Init 
      LDR R1,=DumpIndex
      MOV R0,#0
      STR R0,[R1] ;DumpIndex=0 
      BX  LR
      EXPORT Debug_Dump
;Dump information into buffers
;Input: R0 is any 32-bit value 
;       R1 is any 32-bit value
Debug_Dump 
;pseudo code
;0)save registers according to AAPCS
;1)if DumpIndex is greater than 31, skip to 5)
;2)store R0 into DumpBuf1 at index DumpIndex 
; effective address is DumpBuf1+4*DumpIndex
;3)store R1 into DumpBuf2 at index DumpIndex
; effective address is DumpBuf2+4*DumpIndex
;4)DumpIndex = DumpIndex+1
;5)restore registers (balance stack)
  
   BX LR
   ALIGN 4
   END

    