// Debug.h
// Runs on TM4C123
// Implement debugging dump.
// Put your names here
// Last modification: January 1, 2023
// Debug.s and Debug.h are in the inc folder, so you can use it in other labs
// Feel free to modify exactly how this works
#ifndef __Debug_H__ // do not include more than once
#define __Debug_H__
#include <stdint.h>
uint32_t DumpBuf1[32]; // filled in Debug.s
uint32_t DumpBuf2[32]; // filled in Debug.s
uint32_t DumpIndex;     // incremented in Debug.s
// ------------Debug_Init------------
// Initialize debugging dump.
// This function should be called once at the beginning.
// Input: none
// Output: none
void Debug_Init(void);

// ------------Debug_Dump------------
// Save input in DumpBuf1  
// Save output in DumpBuf2  
// Input: input is any 32-bit value
//        output is any 32-bit value 
// Output: none
// Assumes: Debug_Init() has been called
// stops recording when buffera are full
void Debug_Dump(uint32_t input, uint32_t output);

#endif
