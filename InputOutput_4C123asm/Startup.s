; <<< Use Configuration Wizard in Context Menu >>>
;******************************************************************************
;
; startup_rvmdk.S - Startup code for use with Keil's uVision.
; EE319K Version, Jonathan Valvano with unlocking and PLL 80 MHz
; Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
; Software License Agreement
;
; Texas Instruments (TI) is supplying this software for use solely and
; exclusively on TI's microcontroller products. The software is owned by
; TI and/or its suppliers, and is protected under applicable copyright
; laws. You may not combine this software with "viral" open-source
; software in order to form a larger program.
;
; THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
; NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
; NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
; A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
; CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
; DAMAGES, FOR ANY REASON WHATSOEVER.
;
; This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
;
;******************************************************************************
; Edited to conform with ISR names as described in
;   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
;   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2012
;   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
;   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2012
;   "Embedded Systems: Real-Time Operating Systems for ARM Cortex M Microcontrollers",
;   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2013
;
;******************************************************************************
;
; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;
;******************************************************************************
Stack   EQU     0x00000400

;******************************************************************************
;
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;
;******************************************************************************
Heap    EQU     0x00000000

;******************************************************************************
;
; Allocate space for the stack.
;
;******************************************************************************
        AREA    STACK, NOINIT, READWRITE, ALIGN=3
StackMem
        SPACE   Stack
__initial_sp

;******************************************************************************
;
; Allocate space for the heap.
;
;******************************************************************************
        AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
HeapMem
        SPACE   Heap
__heap_limit

;******************************************************************************
;
; Indicate that the code in this file preserves 8-byte alignment of the stack.
;
;******************************************************************************
        PRESERVE8

;******************************************************************************
;
; Place code into the reset code section.
;
;******************************************************************************
        AREA    RESET, CODE, READONLY
        THUMB

;******************************************************************************
;
; The vector table.
;
;******************************************************************************
        EXPORT  __Vectors
__Vectors
        DCD     StackMem + Stack            ; Top of Stack
        DCD     Reset_Handler               ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler
        DCD     GPIOPortA_Handler           ; GPIO Port A
        DCD     GPIOPortB_Handler           ; GPIO Port B
        DCD     GPIOPortC_Handler           ; GPIO Port C
        DCD     GPIOPortD_Handler           ; GPIO Port D
        DCD     GPIOPortE_Handler           ; GPIO Port E
        DCD     UART0_Handler               ; UART0 Rx and Tx
        DCD     UART1_Handler               ; UART1 Rx and Tx
        DCD     SSI0_Handler                ; SSI0 Rx and Tx
        DCD     I2C0_Handler                ; I2C0 Master and Slave
        DCD     PWM0Fault_Handler           ; PWM 0 Fault
        DCD     PWM0Generator0_Handler      ; PWM 0 Generator 0
        DCD     PWM0Generator1_Handler      ; PWM 0 Generator 1
        DCD     PWM0Generator2_Handler      ; PWM 0 Generator 2
        DCD     Quadrature0_Handler         ; Quadrature Encoder 0
        DCD     ADC0Seq0_Handler            ; ADC0 Sequence 0
        DCD     ADC0Seq1_Handler            ; ADC0 Sequence 1
        DCD     ADC0Seq1_Handler            ; ADC0 Sequence 2
        DCD     ADC0Seq1_Handler            ; ADC0 Sequence 3
        DCD     WDT_Handler                 ; Watchdog
        DCD     Timer0A_Handler             ; Timer 0 subtimer A
        DCD     Timer0B_Handler             ; Timer 0 subtimer B
        DCD     Timer1A_Handler             ; Timer 1 subtimer A
        DCD     Timer1B_Handler             ; Timer 1 subtimer B
        DCD     Timer2A_Handler             ; Timer 2 subtimer A
        DCD     Timer2B_Handler             ; Timer 2 subtimer B
        DCD     Comp0_Handler               ; Analog Comp 0
        DCD     Comp1_Handler               ; Analog Comp 1
        DCD     Comp2_Handler               ; Analog Comp 2
        DCD     SysCtl_Handler              ; System Control
        DCD     FlashCtl_Handler            ; Flash Control
        DCD     GPIOPortF_Handler           ; GPIO Port F
        DCD     GPIOPortG_Handler           ; GPIO Port G
        DCD     GPIOPortH_Handler           ; GPIO Port H
        DCD     UART2_Handler               ; UART2 Rx and Tx
        DCD     SSI1_Handler                ; SSI1 Rx and Tx
        DCD     Timer3A_Handler             ; Timer 3 subtimer A
        DCD     Timer3B_Handler             ; Timer 3 subtimer B
        DCD     I2C1_Handler                ; I2C1 Master and Slave
        DCD     Quadrature1_Handler         ; Quadrature Encoder 1
        DCD     CAN0_Handler                ; CAN0
        DCD     CAN1_Handler                ; CAN1
        DCD     CAN2_Handler                ; CAN2
        DCD     Ethernet_Handler            ; Ethernet
        DCD     Hibernate_Handler           ; Hibernate
        DCD     USB0_Handler                ; USB0
        DCD     PWM0Generator3_Handler      ; PWM 0 Generator 3
        DCD     uDMA_Handler                ; uDMA Software Transfer
        DCD     uDMA_Error                  ; uDMA Error
        DCD     ADC1Seq0_Handler            ; ADC1 Sequence 0
        DCD     ADC1Seq1_Handler            ; ADC1 Sequence 1
        DCD     ADC1Seq2_Handler            ; ADC1 Sequence 2
        DCD     ADC1Seq3_Handler            ; ADC1 Sequence 3
        DCD     I2S0_Handler                ; I2S0
        DCD     ExtBus_Handler              ; External Bus Interface 0
        DCD     GPIOPortJ_Handler           ; GPIO Port J
        DCD     GPIOPortK_Handler           ; GPIO Port K
        DCD     GPIOPortL_Handler           ; GPIO Port L
        DCD     SSI2_Handler                ; SSI2 Rx and Tx
        DCD     SSI3_Handler                ; SSI3 Rx and Tx
        DCD     UART3_Handler               ; UART3 Rx and Tx
        DCD     UART4_Handler               ; UART4 Rx and Tx
        DCD     UART5_Handler               ; UART5 Rx and Tx
        DCD     UART6_Handler               ; UART6 Rx and Tx
        DCD     UART7_Handler               ; UART7 Rx and Tx
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     I2C2_Handler                ; I2C2 Master and Slave
        DCD     I2C3_Handler                ; I2C3 Master and Slave
        DCD     Timer4A_Handler             ; Timer 4 subtimer A
        DCD     Timer4B_Handler             ; Timer 4 subtimer B
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     Timer5A_Handler             ; Timer 5 subtimer A
        DCD     Timer5B_Handler             ; Timer 5 subtimer B
        DCD     WideTimer0A_Handler         ; Wide Timer 0 subtimer A
        DCD     WideTimer0B_Handler         ; Wide Timer 0 subtimer B
        DCD     WideTimer1A_Handler         ; Wide Timer 1 subtimer A
        DCD     WideTimer1B_Handler         ; Wide Timer 1 subtimer B
        DCD     WideTimer2A_Handler         ; Wide Timer 2 subtimer A
        DCD     WideTimer2B_Handler         ; Wide Timer 2 subtimer B
        DCD     WideTimer3A_Handler         ; Wide Timer 3 subtimer A
        DCD     WideTimer3B_Handler         ; Wide Timer 3 subtimer B
        DCD     WideTimer4A_Handler         ; Wide Timer 4 subtimer A
        DCD     WideTimer4B_Handler         ; Wide Timer 4 subtimer B
        DCD     WideTimer5A_Handler         ; Wide Timer 5 subtimer A
        DCD     WideTimer5B_Handler         ; Wide Timer 5 subtimer B
        DCD     FPU_Handler                 ; FPU
        DCD     PECI0_Handler               ; PECI 0
        DCD     LPC0_Handler                ; LPC 0
        DCD     I2C4_Handler                ; I2C4 Master and Slave
        DCD     I2C5_Handler                ; I2C5 Master and Slave
        DCD     GPIOPortM_Handler           ; GPIO Port M
        DCD     GPIOPortN_Handler           ; GPIO Port N
        DCD     Quadrature2_Handler         ; Quadrature Encoder 2
        DCD     Fan0_Handler                ; Fan 0
        DCD     0                           ; Reserved
        DCD     GPIOPortP_Handler           ; GPIO Port P (Summary or P0)
        DCD     GPIOPortP1_Handler          ; GPIO Port P1
        DCD     GPIOPortP2_Handler          ; GPIO Port P2
        DCD     GPIOPortP3_Handler          ; GPIO Port P3
        DCD     GPIOPortP4_Handler          ; GPIO Port P4
        DCD     GPIOPortP5_Handler          ; GPIO Port P5
        DCD     GPIOPortP6_Handler          ; GPIO Port P6
        DCD     GPIOPortP7_Handler          ; GPIO Port P7
        DCD     GPIOPortQ_Handler           ; GPIO Port Q (Summary or Q0)
        DCD     GPIOPortQ1_Handler          ; GPIO Port Q1
        DCD     GPIOPortQ2_Handler          ; GPIO Port Q2
        DCD     GPIOPortQ3_Handler          ; GPIO Port Q3
        DCD     GPIOPortQ4_Handler          ; GPIO Port Q4
        DCD     GPIOPortQ5_Handler          ; GPIO Port Q5
        DCD     GPIOPortQ6_Handler          ; GPIO Port Q6
        DCD     GPIOPortQ7_Handler          ; GPIO Port Q7
        DCD     GPIOPortR_Handler           ; GPIO Port R
        DCD     GPIOPortS_Handler           ; GPIO Port S
        DCD     PWM1Generator0_Handler      ; PWM 1 Generator 0
        DCD     PWM1Generator1_Handler      ; PWM 1 Generator 1
        DCD     PWM1Generator2_Handler      ; PWM 1 Generator 2
        DCD     PWM1Generator3_Handler      ; PWM 1 Generator 3
        DCD     PWM1Fault_Handler           ; PWM 1 Fault

;******************************************************************************
;
; This is the code that gets called when the processor first starts execution
; following a reset event.
;
;******************************************************************************

        EXPORT  Reset_Handler
Reset_Handler
        
        BL   PLL_Init
        BL   UnlockPortD
        BL   UnlockPortF
        ;
        ; DO NOT enable the floating-point unit.  This must be done here to handle the
        ; case where main() uses floating-point and the function prologue saves
        ; floating-point registers (which will fault if floating-point is not
        ; enabled).  Any configuration of the floating-point unit using
        ; DriverLib APIs must be done here prior to the floating-point unit
        ; being enabled.
        ;
        ; Note that this does not use DriverLib since it might not be included
        ; in this project.
        ;
;        MOVW    R0, #0xED88
;        MOVT    R0, #0xE000
;        LDR     R1, [R0]
;        ORR     R1, #0x00F00000
;        STR     R1, [R0]

        ;
        ; Call the C library enty point that handles startup.  This will copy
        ; the .data section initializers from flash to SRAM and zero fill the
        ; .bss section.
        ;
        IMPORT  Start
        B       Start     ;call user assembly language program

; The EQU statement SYSDIV2 initializes
; the PLL to the desired frequency.
SYSDIV2                EQU 4
; bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz

SYSCTL_RIS_R           EQU 0x400FE050
SYSCTL_RIS_PLLLRIS     EQU 0x00000040  ; PLL Lock Raw Interrupt Status
SYSCTL_RCC_R           EQU 0x400FE060
SYSCTL_RCC_XTAL_M      EQU 0x000007C0  ; Crystal Value
SYSCTL_RCC_XTAL_6MHZ   EQU 0x000002C0  ; 6 MHz Crystal
SYSCTL_RCC_XTAL_8MHZ   EQU 0x00000380  ; 8 MHz Crystal
SYSCTL_RCC_XTAL_16MHZ  EQU 0x00000540  ; 16 MHz Crystal
SYSCTL_RCC2_R          EQU 0x400FE070
SYSCTL_RCC2_USERCC2    EQU 0x80000000  ; Use RCC2
SYSCTL_RCC2_DIV400     EQU 0x40000000  ; Divide PLL as 400 MHz vs. 200
                                       ; MHz
SYSCTL_RCC2_SYSDIV2_M  EQU 0x1F800000  ; System Clock Divisor 2
SYSCTL_RCC2_SYSDIV2LSB EQU 0x00400000  ; Additional LSB for SYSDIV2
SYSCTL_RCC2_PWRDN2     EQU 0x00002000  ; Power-Down PLL 2
SYSCTL_RCC2_BYPASS2    EQU 0x00000800  ; PLL Bypass 2
SYSCTL_RCC2_OSCSRC2_M  EQU 0x00000070  ; Oscillator Source 2
SYSCTL_RCC2_OSCSRC2_MO EQU 0x00000000  ; MOSC


;------------PLL_Init------------
; Configure the system to get its clock from the PLL.
; Input: none
; Output: none
; Modifies: R0, R1, R2, R3
PLL_Init
    ; 0) configure the system to use RCC2 for advanced features
    ;    such as 400 MHz PLL and non-integer System Clock Divisor
    LDR R3, =SYSCTL_RCC2_R          ; R3 = SYSCTL_RCC2_R (pointer)
    LDR R2, [R3]                    ; R2 = [R3] (value)
    ORR R2, R2, #SYSCTL_RCC2_USERCC2; R2 = R2|SYSCTL_RCC2_USERCC2
    STR R2, [R3]                    ; [R3] = R2
    ; 1) bypass PLL while initializing
    ORR R2, R2, #SYSCTL_RCC2_BYPASS2; R2 = R2|SYSCTL_RCC2_BYPASS2
    STR R2, [R3]                    ; [R3] = R2
    ; 2) select the crystal value and oscillator source
    LDR R1, =SYSCTL_RCC_R           ; R1 = SYSCTL_RCC_R (pointer)
    LDR R0, [R1]                    ; R0 = [R1] (value)
    BIC R0, R0, #SYSCTL_RCC_XTAL_M  ; R0 = R0&~SYSCTL_RCC_XTAL_M (clear XTAL field)
    ORR R0, R0, #SYSCTL_RCC_XTAL_16MHZ;R0 = R0|SYSCTL_RCC_XTAL_16MHZ (configure for 16 MHz crystal)
    STR R0, [R1]                    ; [R1] = R0
                                    ; R2 = R2&~SYSCTL_RCC2_OSCSRC2_M (clear oscillator source field)
    BIC R2, R2, #SYSCTL_RCC2_OSCSRC2_M
                                    ; R2 = R2|SYSCTL_RCC2_OSCSRC2_MO (configure for main oscillator source)
    ORR R2, R2, #SYSCTL_RCC2_OSCSRC2_MO
    ; 3) activate PLL by clearing PWRDN
    BIC R2, R2, #SYSCTL_RCC2_PWRDN2 ; R2 = R2&~SYSCTL_RCC2_PWRDN2
    ; 4) set the desired system divider and the system divider least significant bit
    ORR R2, R2, #SYSCTL_RCC2_DIV400 ; R2 = R2|SYSCTL_RCC2_DIV400 (use 400 MHz PLL)
                                    ;R2 = R2&~SYSCTL_RCC2_SYSDIV2_M (clear system clock divider field)
    BIC R2, R2, #SYSCTL_RCC2_SYSDIV2_M
                                    ;R2 = R2&~SYSCTL_RCC2_SYSDIV2LSB (clear bit SYSDIV2LSB)
    BIC R2, R2, #SYSCTL_RCC2_SYSDIV2LSB
    ; set Divisor by writing 7-bit constant to bits 28-22
    ADD R2, R2, #(SYSDIV2<<22)      ; R2 = R2 + (SYSDIV2<<22) (configure SYSDIV2 and SYSDIV2LSB fields in RCC2)
    STR R2, [R3]                    ; [R3] = R2
    ; 5) wait for the PLL to lock by polling PLLLRIS
    LDR R1, =SYSCTL_RIS_R           ; R1 = SYSCTL_RIS_R (pointer)
PLL_Init_loop
    LDR R0, [R1]                    ; R0 = [R1] (value)
    ANDS R0, R0, #SYSCTL_RIS_PLLLRIS; R0 = R0&SYSCTL_RIS_PLLLRIS
    BEQ PLL_Init_loop               ; if(R0 == 0), keep polling
    ; 6) enable use of PLL by clearing BYPASS
    BIC R2, R2, #SYSCTL_RCC2_BYPASS2; R2 = R2&~SYSCTL_RCC2_BYPASS2
    STR R2, [R3]                    ; [R3] = R2
    BX  LR                          ; return


; SYSDIV2  Divisor  Clock (MHz)
; 0        1       reserved
; 1        2       reserved
; 2        3       reserved
; 3        4       reserved
; 4        5       80.000
; 5        6       66.667
; 6        7       reserved
; 7        8       50.000
; 8        9       44.444
; 9        10      40.000
; 10       11      36.364
; 11       12      33.333
; 12       13      30.769
; 13       14      28.571
; 14       15      26.667
; 15       16      25.000
; 16       17      23.529
; 17       18      22.222
; 18       19      21.053
; 19       20      20.000
; 20       21      19.048
; 21       22      18.182
; 22       23      17.391
; 23       24      16.667
; 24       25      16.000
; 25       26      15.385
; 26       27      14.815
; 27       28      14.286
; 28       29      13.793
; 29       30      13.333
; 30       31      12.903
; 31       32      12.500
; 32       33      12.121
; 33       34      11.765
; 34       35      11.429
; 35       36      11.111
; 36       37      10.811
; 37       38      10.526
; 38       39      10.256
; 39       40      10.000
; 40       41      9.756
; 41       42      9.524
; 42       43      9.302
; 43       44      9.091
; 44       45      8.889
; 45       46      8.696
; 46       47      8.511
; 47       48      8.333
; 48       49      8.163
; 49       50      8.000
; 50       51      7.843
; 51       52      7.692
; 52       53      7.547
; 53       54      7.407
; 54       55      7.273
; 55       56      7.143
; 56       57      7.018
; 57       58      6.897
; 58       59      6.780
; 59       60      6.667
; 60       61      6.557
; 61       62      6.452
; 62       63      6.349
; 63       64      6.250
; 64       65      6.154
; 65       66      6.061
; 66       67      5.970
; 67       68      5.882
; 68       69      5.797
; 69       70      5.714
; 70       71      5.634
; 71       72      5.556
; 72       73      5.479
; 73       74      5.405
; 74       75      5.333
; 75       76      5.263
; 76       77      5.195
; 77       78      5.128
; 78       79      5.063
; 79       80      5.000
; 80       81      4.938
; 81       82      4.878
; 82       83      4.819
; 83       84      4.762
; 84       85      4.706
; 85       86      4.651
; 86       87      4.598
; 87       88      4.545
; 88       89      4.494
; 89       90      4.444
; 90       91      4.396
; 91       92      4.348
; 92       93      4.301
; 93       94      4.255
; 94       95      4.211
; 95       96      4.167
; 96       97      4.124
; 97       98      4.082
; 98       99      4.040
; 99       100     4.000
; 100      101     3.960
; 101      102     3.922
; 102      103     3.883
; 103      104     3.846
; 104      105     3.810
; 105      106     3.774
; 106      107     3.738
; 107      108     3.704
; 108      109     3.670
; 109      110     3.636
; 110      111     3.604
; 111      112     3.571
; 112      113     3.540
; 113      114     3.509
; 114      115     3.478
; 115      116     3.448
; 116      117     3.419
; 117      118     3.390
; 118      119     3.361
; 119      120     3.333
; 120      121     3.306
; 121      122     3.279
; 122      123     3.252
; 123      124     3.226
; 124      125     3.200
; 125      126     3.175
; 126      127     3.150
; 127      128     3.125

GPIO_PORTF_DATA_R  EQU 0x400253FC
GPIO_PORTF_DIR_R   EQU 0x40025400
GPIO_PORTF_AFSEL_R EQU 0x40025420
GPIO_PORTF_PUR_R   EQU 0x40025510
GPIO_PORTF_DEN_R   EQU 0x4002551C
GPIO_PORTF_LOCK_R  EQU 0x40025520
GPIO_PORTF_CR_R    EQU 0x40025524
GPIO_PORTF_AMSEL_R EQU 0x40025528
GPIO_PORTF_PCTL_R  EQU 0x4002552C
GPIO_LOCK_KEY      EQU 0x4C4F434B  ; Unlocks the GPIO_CR register
SYSCTL_RCGCGPIO_R  EQU 0x400FE608
;------------UnlockPortF------------
; Unlock GPIO Port .
; Input: none
; Output: none
; Modifies: R0, R1, R2
    EXPORT UnlockPortF
UnlockPortF
    LDR R1, =SYSCTL_RCGCGPIO_R      ; 1) activate all clocks
    LDR R0, [R1]
    ORR R0, R0, #0x20               ; set bit 5 to turn on clock
    STR R0, [R1]
    NOP
    NOP                             ; allow time for clock to finish
    LDR R1, =GPIO_PORTF_LOCK_R      ; 2) unlock the lock register
    LDR R0, =0x4C4F434B             ; unlock GPIO Port F Commit Register
    STR R0, [R1]
    LDR R1, =GPIO_PORTF_CR_R        ; enable commit for Port F
    MOV R0, #0xFF                   ; 1 means allow access
    STR R0, [R1]
    LDR R1, =GPIO_PORTF_AMSEL_R     ; 3) disable analog functionality
    MOV R0, #0                      ; 0 means analog is off
    STR R0, [R1]
    LDR R1, =GPIO_PORTF_PCTL_R      ; 4) configure as GPIO
    MOV R0, #0x00000000             ; 0 means configure Port F as GPIO
    STR R0, [R1]
    LDR R1, =GPIO_PORTF_DIR_R       ; 5) set direction register
    MOV R0,#0x0E                    ; PF0 and PF7-4 input, PF3-1 output
    STR R0, [R1]
    LDR R1, =GPIO_PORTF_AFSEL_R     ; 6) regular port function
    MOV R0, #0                      ; 0 means disable alternate function
    STR R0, [R1]
    LDR R1, =GPIO_PORTF_PUR_R       ; pull-up resistors for PF4,PF0
    MOV R0, #0x11                   ; enable weak pull-up on PF0 and PF4
    STR R0, [R1]
    LDR R1, =GPIO_PORTF_DEN_R       ; 7) enable Port F digital port
    MOV R0, #0xFF                   ; 1 means enable digital I/O
    STR R0, [R1]
    BX  LR
GPIO_PORTD_DATA_R  EQU 0x400073FC
GPIO_PORTD_DIR_R   EQU 0x40007400
GPIO_PORTD_AFSEL_R EQU 0x40007420
GPIO_PORTD_PUR_R   EQU 0x40007510
GPIO_PORTD_DEN_R   EQU 0x4000751C
GPIO_PORTD_LOCK_R  EQU 0x40007520
GPIO_PORTD_CR_R    EQU 0x40007524
GPIO_PORTD_AMSEL_R EQU 0x40007528
GPIO_PORTD_PCTL_R  EQU 0x4000752C
;------------UnlockPortD------------
; Unlock GPIO Port D
; Input: none
; Output: none
; Modifies: R0, R1, R2
    EXPORT UnlockPortD
UnlockPortD
    LDR R1, =SYSCTL_RCGCGPIO_R      ; 1) activate  clock
    LDR R0, [R1]
    ORR R0, R0, #0x08               ; set bit 3 to turn on clock
    STR R0, [R1]
    NOP
    NOP                             ; allow time for clock to finish
    LDR R1, =GPIO_PORTD_LOCK_R      ; 2) unlock the lock register
    LDR R0, =0x4C4F434B             ; unlock GPIO Port F Commit Register
    STR R0, [R1]
    LDR R1, =GPIO_PORTD_CR_R        ; enable commit for Port D
    MOV R0, #0xFF                   ; 1 means allow access
    STR R0, [R1]
    LDR R1, =GPIO_PORTD_AMSEL_R     ; 3) disable analog functionality
    MOV R0, #0                      ; 0 means analog is off
    STR R0, [R1]
    LDR R1, =GPIO_PORTD_PCTL_R      ; 4) configure as GPIO
    MOV R0, #0x00000000             ; 0 means configure Port D as GPIO
    STR R0, [R1]
    LDR R1, =GPIO_PORTD_DIR_R       ; 5) set direction register
    MOV R0,#0x00                    ; inputs
    STR R0, [R1]
    LDR R1, =GPIO_PORTD_AFSEL_R     ; 6) regular port function
    MOV R0, #0                      ; 0 means disable alternate function
    STR R0, [R1]
    LDR R1, =GPIO_PORTD_DEN_R       ; 7) enable Port D digital port
    MOV R0, #0xFF                   ; 1 means enable digital I/O
    STR R0, [R1]
    BX  LR
;******************************************************************************
;
; This is the code that gets called when the processor receives a NMI.  This
; simply enters an infinite loop, preserving the system state for examination
; by a debugger.
;
;******************************************************************************
NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP

;******************************************************************************
;
; This is the code that gets called when the processor receives a fault
; interrupt.  This simply enters an infinite loop, preserving the system state
; for examination by a debugger.
;
;******************************************************************************
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP

MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP
IntDefaultHandler\
                PROC

                EXPORT  GPIOPortA_Handler         [WEAK]
                EXPORT  GPIOPortB_Handler         [WEAK]
                EXPORT  GPIOPortC_Handler         [WEAK]
                EXPORT  GPIOPortD_Handler         [WEAK]
                EXPORT  GPIOPortE_Handler         [WEAK]
                EXPORT  UART0_Handler             [WEAK]
                EXPORT  UART1_Handler             [WEAK]
                EXPORT  SSI0_Handler              [WEAK]
                EXPORT  I2C0_Handler              [WEAK]
                EXPORT  PWM0Fault_Handler         [WEAK]
                EXPORT  PWM0Generator0_Handler    [WEAK]
                EXPORT  PWM0Generator1_Handler    [WEAK]
                EXPORT  PWM0Generator2_Handler    [WEAK]
                EXPORT  Quadrature0_Handler       [WEAK]
                EXPORT  ADC0Seq0_Handler          [WEAK]
                EXPORT  ADC0Seq1_Handler          [WEAK]
                EXPORT  ADC0Seq2_Handler          [WEAK]
                EXPORT  ADC0Seq3_Handler          [WEAK]
                EXPORT  WDT_Handler               [WEAK]
                EXPORT  Timer0A_Handler           [WEAK]
                EXPORT  Timer0B_Handler           [WEAK]
                EXPORT  Timer1A_Handler           [WEAK]
                EXPORT  Timer1B_Handler           [WEAK]
                EXPORT  Timer2A_Handler           [WEAK]
                EXPORT  Timer2B_Handler           [WEAK]
                EXPORT  Comp0_Handler             [WEAK]
                EXPORT  Comp1_Handler             [WEAK]
                EXPORT  Comp2_Handler             [WEAK]
                EXPORT  SysCtl_Handler            [WEAK]
                EXPORT  FlashCtl_Handler          [WEAK]
                EXPORT  GPIOPortF_Handler         [WEAK]
                EXPORT  GPIOPortG_Handler         [WEAK]
                EXPORT  GPIOPortH_Handler         [WEAK]
                EXPORT  UART2_Handler             [WEAK]
                EXPORT  SSI1_Handler              [WEAK]
                EXPORT  Timer3A_Handler           [WEAK]
                EXPORT  Timer3B_Handler           [WEAK]
                EXPORT  I2C1_Handler              [WEAK]
                EXPORT  Quadrature1_Handler       [WEAK]
                EXPORT  CAN0_Handler              [WEAK]
                EXPORT  CAN1_Handler              [WEAK]
                EXPORT  CAN2_Handler              [WEAK]
                EXPORT  Ethernet_Handler          [WEAK]
                EXPORT  Hibernate_Handler         [WEAK]
                EXPORT  USB0_Handler              [WEAK]
                EXPORT  PWM0Generator3_Handler    [WEAK]
                EXPORT  uDMA_Handler              [WEAK]
                EXPORT  uDMA_Error                [WEAK]
                EXPORT  ADC1Seq0_Handler          [WEAK]
                EXPORT  ADC1Seq1_Handler          [WEAK]
                EXPORT  ADC1Seq2_Handler          [WEAK]
                EXPORT  ADC1Seq3_Handler          [WEAK]
                EXPORT  I2S0_Handler              [WEAK]
                EXPORT  ExtBus_Handler            [WEAK]
                EXPORT  GPIOPortJ_Handler         [WEAK]
                EXPORT  GPIOPortK_Handler         [WEAK]
                EXPORT  GPIOPortL_Handler         [WEAK]
                EXPORT  SSI2_Handler              [WEAK]
                EXPORT  SSI3_Handler              [WEAK]
                EXPORT  UART3_Handler             [WEAK]
                EXPORT  UART4_Handler             [WEAK]
                EXPORT  UART5_Handler             [WEAK]
                EXPORT  UART6_Handler             [WEAK]
                EXPORT  UART7_Handler             [WEAK]
                EXPORT  I2C2_Handler              [WEAK]
                EXPORT  I2C3_Handler              [WEAK]
                EXPORT  Timer4A_Handler           [WEAK]
                EXPORT  Timer4B_Handler           [WEAK]
                EXPORT  Timer5A_Handler           [WEAK]
                EXPORT  Timer5B_Handler           [WEAK]
                EXPORT  WideTimer0A_Handler       [WEAK]
                EXPORT  WideTimer0B_Handler       [WEAK]
                EXPORT  WideTimer1A_Handler       [WEAK]
                EXPORT  WideTimer1B_Handler       [WEAK]
                EXPORT  WideTimer2A_Handler       [WEAK]
                EXPORT  WideTimer2B_Handler       [WEAK]
                EXPORT  WideTimer3A_Handler       [WEAK]
                EXPORT  WideTimer3B_Handler       [WEAK]
                EXPORT  WideTimer4A_Handler       [WEAK]
                EXPORT  WideTimer4B_Handler       [WEAK]
                EXPORT  WideTimer5A_Handler       [WEAK]
                EXPORT  WideTimer5B_Handler       [WEAK]
                EXPORT  FPU_Handler               [WEAK]
                EXPORT  PECI0_Handler             [WEAK]
                EXPORT  LPC0_Handler              [WEAK]
                EXPORT  I2C4_Handler              [WEAK]
                EXPORT  I2C5_Handler              [WEAK]
                EXPORT  GPIOPortM_Handler         [WEAK]
                EXPORT  GPIOPortN_Handler         [WEAK]
                EXPORT  Quadrature2_Handler       [WEAK]
                EXPORT  Fan0_Handler              [WEAK]
                EXPORT  GPIOPortP_Handler         [WEAK]
                EXPORT  GPIOPortP1_Handler        [WEAK]
                EXPORT  GPIOPortP2_Handler        [WEAK]
                EXPORT  GPIOPortP3_Handler        [WEAK]
                EXPORT  GPIOPortP4_Handler        [WEAK]
                EXPORT  GPIOPortP5_Handler        [WEAK]
                EXPORT  GPIOPortP6_Handler        [WEAK]
                EXPORT  GPIOPortP7_Handler        [WEAK]
                EXPORT  GPIOPortQ_Handler         [WEAK]
                EXPORT  GPIOPortQ1_Handler        [WEAK]
                EXPORT  GPIOPortQ2_Handler        [WEAK]
                EXPORT  GPIOPortQ3_Handler        [WEAK]
                EXPORT  GPIOPortQ4_Handler        [WEAK]
                EXPORT  GPIOPortQ5_Handler        [WEAK]
                EXPORT  GPIOPortQ6_Handler        [WEAK]
                EXPORT  GPIOPortQ7_Handler        [WEAK]
                EXPORT  GPIOPortR_Handler         [WEAK]
                EXPORT  GPIOPortS_Handler         [WEAK]
                EXPORT  PWM1Generator0_Handler    [WEAK]
                EXPORT  PWM1Generator1_Handler    [WEAK]
                EXPORT  PWM1Generator2_Handler    [WEAK]
                EXPORT  PWM1Generator3_Handler    [WEAK]
                EXPORT  PWM1Fault_Handler         [WEAK]

GPIOPortA_Handler
GPIOPortB_Handler
GPIOPortC_Handler
GPIOPortD_Handler
GPIOPortE_Handler
UART0_Handler
UART1_Handler
SSI0_Handler
I2C0_Handler
PWM0Fault_Handler
PWM0Generator0_Handler
PWM0Generator1_Handler
PWM0Generator2_Handler
Quadrature0_Handler
ADC0Seq0_Handler
ADC0Seq1_Handler
ADC0Seq2_Handler
ADC0Seq3_Handler
WDT_Handler
Timer0A_Handler
Timer0B_Handler
Timer1A_Handler
Timer1B_Handler
Timer2A_Handler
Timer2B_Handler
Comp0_Handler
Comp1_Handler
Comp2_Handler
SysCtl_Handler
FlashCtl_Handler
GPIOPortF_Handler
GPIOPortG_Handler
GPIOPortH_Handler
UART2_Handler
SSI1_Handler
Timer3A_Handler
Timer3B_Handler
I2C1_Handler
Quadrature1_Handler
CAN0_Handler
CAN1_Handler
CAN2_Handler
Ethernet_Handler
Hibernate_Handler
USB0_Handler
PWM0Generator3_Handler
uDMA_Handler
uDMA_Error
ADC1Seq0_Handler
ADC1Seq1_Handler
ADC1Seq2_Handler
ADC1Seq3_Handler
I2S0_Handler
ExtBus_Handler
GPIOPortJ_Handler
GPIOPortK_Handler
GPIOPortL_Handler
SSI2_Handler
SSI3_Handler
UART3_Handler
UART4_Handler
UART5_Handler
UART6_Handler
UART7_Handler
I2C2_Handler
I2C3_Handler
Timer4A_Handler
Timer4B_Handler
Timer5A_Handler
Timer5B_Handler
WideTimer0A_Handler
WideTimer0B_Handler
WideTimer1A_Handler
WideTimer1B_Handler
WideTimer2A_Handler
WideTimer2B_Handler
WideTimer3A_Handler
WideTimer3B_Handler
WideTimer4A_Handler
WideTimer4B_Handler
WideTimer5A_Handler
WideTimer5B_Handler
FPU_Handler
PECI0_Handler
LPC0_Handler
I2C4_Handler
I2C5_Handler
GPIOPortM_Handler
GPIOPortN_Handler
Quadrature2_Handler
Fan0_Handler
GPIOPortP_Handler
GPIOPortP1_Handler
GPIOPortP2_Handler
GPIOPortP3_Handler
GPIOPortP4_Handler
GPIOPortP5_Handler
GPIOPortP6_Handler
GPIOPortP7_Handler
GPIOPortQ_Handler
GPIOPortQ1_Handler
GPIOPortQ2_Handler
GPIOPortQ3_Handler
GPIOPortQ4_Handler
GPIOPortQ5_Handler
GPIOPortQ6_Handler
GPIOPortQ7_Handler
GPIOPortR_Handler
GPIOPortS_Handler
PWM1Generator0_Handler
PWM1Generator1_Handler
PWM1Generator2_Handler
PWM1Generator3_Handler
PWM1Fault_Handler

                B       .

                ENDP

;******************************************************************************
;
; Make sure the end of this section is aligned.
;
;******************************************************************************
        ALIGN

;******************************************************************************
;
; Some code in the normal code section for initializing the heap and stack.
;
;******************************************************************************
        AREA    |.text|, CODE, READONLY

;******************************************************************************
;
; Useful functions.
;
;******************************************************************************
        EXPORT  DisableInterrupts
        EXPORT  EnableInterrupts
        EXPORT  StartCritical
        EXPORT  EndCritical
        EXPORT  WaitForInterrupt

;*********** DisableInterrupts ***************
; disable interrupts
; inputs:  none
; outputs: none
DisableInterrupts
        CPSID  I
        BX     LR

;*********** EnableInterrupts ***************
; disable interrupts
; inputs:  none
; outputs: none
EnableInterrupts
        CPSIE  I
        BX     LR

;*********** StartCritical ************************
; make a copy of previous I bit, disable interrupts
; inputs:  none
; outputs: previous I bit
StartCritical
        MRS    R0, PRIMASK  ; save old status
        CPSID  I            ; mask all (except faults)
        BX     LR

;*********** EndCritical ************************
; using the copy of previous I bit, restore I bit to previous value
; inputs:  previous I bit
; outputs: none
EndCritical
        MSR    PRIMASK, R0
        BX     LR

;*********** WaitForInterrupt ************************
; go to low power mode while waiting for the next interrupt
; inputs:  none
; outputs: none
WaitForInterrupt
        WFI
        BX     LR



;******************************************************************************
;
; Make sure the end of this section is aligned.
;
;******************************************************************************
        ALIGN

;******************************************************************************
;
; Tell the assembler that we're done.
;
;******************************************************************************
        END
