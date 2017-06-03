#include"headers.h"

uch (*permblock)[CARD];
static uch basicperm[8]={0,1,2,3,4,5,6,7}; 

void fillPermBlock(uch *perm,int len)
	/* fill permblock with all permutations of basic perm defined above.  
	   (recursive)  */
{
	if(len==1) 
		/* then at end of current permutation, 
		   so copy to block */
	{
		memcpy(*permblock++,perm-CARD+1,CARD);
		return;
	}
	int i;
	uch s; // tmp storage for swap
	fillPermBlock(perm+1,len-1);
	for(i=1;i<len;i++)
	{
		s=perm[0];
		perm[0]=perm[i];
		perm[i]=s;
		/* recurse on remaining segment */
		fillPermBlock(perm+1,len-1);
		s=perm[0];
		perm[0]=perm[i];
		perm[i]=s;
	}
}	

void initializePermBlock(void){
	permblock = malloc(S(CARD)*sizeof(*permblock));
	fillPermBlock(basicperm,CARD);
	permblock -= S(CARD);
}
