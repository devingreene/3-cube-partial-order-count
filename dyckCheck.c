#include"headers.h"

static uch *table=(uch *)"\0\1\1\0\1\0\0\1";

int dyckCheck(uch* perm)
{
	/* Is the number evil or odious?
	 * ;-) */
	int sum=0;
	int i,sign=(table[(ui)perm[0]])?1:-1;
	for(i=0;i<8;i++)
	{
		sum+=sign*((table[(ui)*perm++])?1:-1);
		if(sum < 0)
			return 0; 
		/* more of the wrong one than
		 * the other
		 so fail
		 */
	}	
	/* else passes test */
	return 1;
}
