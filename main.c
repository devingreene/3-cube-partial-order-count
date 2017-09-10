#include"headers.h"
#include<signal.h>

/* Each directed graph is encoded as a 12-bit word.  Enumerate three groups of
   four bits from right to left; 0,1, and 2.  Label each bit within a group
   from right to left with 0,1,2, and 3.  A 0 bit in the ith group represents
   an arrow from the genotype g_0...0...g_3 to g_0...1...g_3, where 0 is in the
   ith position (from the right).  The arrow is reversed if the same bit is 1.
   Traversing the arrow of a graph leaves two bits constant.  Removing the
   non-constant bit yields a bit string of length two, which can be given a
   value 0, 1, 2, or 3 in the usual way: 0 is 00, 1 is 01, etc.  This value
   corresponds to the position (right to left) of the bit within the four bit
   group.  

   For example, the directed graph represented by the bit string 110100110000
   would contain the following arrows, which correspond to the bits in the
   graph representation read from right to left.

       000 -> 001
	   010 -> 011
	   100 -> 101
	   110 -> 111
	   000 <- 010
	   001 <- 011
	   100 -> 110
	   101 -> 111
	   000 <- 100
	   001 -> 101
	   010 <- 011
	   110 <- 111
  
*/ 

extern int ** potable;
extern void initializePotable(void);
extern void initializePermBlock(void);
extern void filter (uch *checkbox);

int main(void){
	initializePotable();
#ifdef DYCK
	initializePermBlock();
#endif
	uch *checkbox=calloc(0x200,sizeof(char));
	filter(checkbox);
	return 0;
}
