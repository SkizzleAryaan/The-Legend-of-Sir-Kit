// ****************** Lab2.c ***************
// Program written by: put your names here
// Date Created: 1/18/2017 
// Last Modified: 12/31/2022 
#include "Lab2.h"
// Put your name and EID in the next two lines
char Name[] = "Aryaan Saxena";
char EID[] = "as225582";

#include <stdint.h>

// Inputs: x1,y1 is the first point
//         x2,y2 is the second point
// Output: calculate distance
// see UART window to see if you have square, Manhattan or ECE319K distance
// The input/output values will be displayed in the UART window
int abs(int); 
/* I mean *technically* this is an extra code I added, and I'm assuming 
that I was supposed to do an if negative, then make positive, but hey, I know it exists so I added it :)
(work smarter not harder)
*/
int32_t Distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2){
// Replace this following line with your solution
	//x1-x2
	int32_t x_sub = x1 - x2; 
	//y1-y2
	int32_t y_sub = y1 - y2; 
	//abs x
	x_sub = abs(x_sub); 
	//abs y
	y_sub = abs(y_sub); 
	int32_t final; 
	// check max for 319K and return 
	if (x_sub > y_sub) 
	{
		return x_sub; 
	}
  return y_sub;
}

// Inputs: rect1 is x1,y1,w1,h1 the first rectangle
//         rect2 is x2,y2,w2,h2 the second rectangle
// Output: 1 if the rectangles overlap
//         0 if the rectances do not overlap
// Notes: x1 is rect1[0]  x2 is rect2[0]
//        y1 is rect1[1]  y2 is rect2[1]
//        w1 is rect1[2]  w2 is rect2[2]
//        h1 is rect1[3]  h2 is rect2[3]
// The input/output values will be displayed in the UART window
int32_t OverLap(int32_t rect1[4], int32_t rect2[4]){
// Replace this following line with your solution
	
	//determine top right corner for each rect
	int32_t maxw1 = rect1[0] + rect1[2] - 1; 
	int32_t maxh1 = rect1[1] - rect1[3] + 1; 
	int32_t maxw2 = rect2[0] + rect2[2] - 1; 
	int32_t maxh2 = rect2[1] - rect2[3] + 1; 
	
	// loop through entire rect1
	for (int32_t i = rect1[0]; i <= maxw1; i++)
	{
		for (int32_t j = rect1[1]; j >= maxh1; j--) 
		{
			// loop through entire rect2
			for (int32_t k = rect2[0]; k <= maxw2; k++)
			{
				for (int32_t l = rect2[1]; l >= maxh2; l--) 
				{
					//check overlap
					if ((i==k) && (j==l)) 
					{
						return 1; 
					}
				}
			}
		}
	}
	return 0; 
}
// do not edit this 2-D array
const char Hello[4][8] ={
   "Hello  ",    // language 0
   "\xADHola! ", // language 1
   "Ol\xA0    ", // language 2
   "All\x83   "  // language 3
};
// Hello[0][0] is 'H'
// Hello[0][1] is 'e'
// Hello[0][2] is 'l'
// Hello[0][3] is 'l'
// Hello[0][4] is 'o'
// Hello[1][0] is 0xAD
// Hello[1][1] is 'H'
// Hello[1][2] is 'o'
// Hello[1][3] is 'l'
// Hello[1][4] is 'a'
// Hello[1][5] is '!'
void LCD_OutChar(char letter);
// Print 7 characters of the hello message
// Inputs: language 0 to 3
// Output: none
// You should call LCD_OuChar exactly 7 times
void SayHello(uint32_t language){
// Replace this following line with your solution
	
	// loop through row 
	for (uint32_t i = 0; i <= 3; i++) {
		//loop through col
		for (uint32_t j = 0; j <= 6; j++) {
			// check if language = row
			if (i == language) {
				// print each char
				LCD_OutChar(Hello[i][j]); 
			}
		}
	}
}


