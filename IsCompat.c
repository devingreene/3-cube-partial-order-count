#include"headers.h"

#define NBITS 3
#define MARGINS 4

/* Checks that graph (encoded by integer) is compatible with a given 
   linear order */
uch IsCompat(ui n,uch *perm){
	uch pos,sect,low,high,A,B;
	for(pos=0;pos<NBITS;pos++)
		for(sect=0;sect<MARGINS;sect++){
			A = sect&((1<<pos)-1);
			B = sect - A;
			B <<= 1;
			if(n&1){
				low = B+(1<<pos)+A;
				high = B+A;
			}
			else{
				low = B+A;
				high=B+(1<<pos)+A;
			}
			for(A=0;perm[A]!=low;A++){
				if(perm[A]==high) return 0;
			}
			n >>= 1;
		}
	return 1;
}
