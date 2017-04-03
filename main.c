#include"headers.h"
#include<signal.h>

/* Each directed graph is encoded as a 12-bit word.  The least significant
   bit is 0 if 000 points to 001, 1 otherwise.  The second least significant
   bit is 0 if 010 points to 011, 1 otherwise.  The fifth least significant 
   bit is 0 if 000 points to 010, 1 otherwise.  The sixth least significant 
   is 0 if 001 points to 011, 1 otherwise, etc. */

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
