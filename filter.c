#include"headers.h"
#include<signal.h>

extern int IsPoset(void);
extern uch (*permblock)[CARD];
extern void int2table(ui n);
uch IsCompat(ui n,uch *perm);
int dyckCheck(uch* perm);
ui symmetry(ui graph,uch tcycle,uch tau,uch xorop);
static ui graph;
#ifdef DYCK
ui i;
#endif


/* We loop over graphs with 000 as a source.  So we can encode our graphs
   with 12 bit words.  The following two functions convert back and forth 
   between the 9 bit representation and the that with 12 bits */

int IsBaseSource(ui graph){
	return !(0x111&graph);
}

ui inflate9to12(ui graph){
	/* For instance, changes 111111111 to
	   111011101110 */
	ui a,b;
	a=0x1c0&graph;
	b=0x38&graph;
	graph &= 0x7;
	a <<= 3;
	b <<= 2;
	graph <<= 1;
	return graph + a + b ;
}

ui compress12to9(ui graph){
	/* inverse of inflate9to12 */
	ui a,b;
	a=0xe00&graph;
	b=0x0e0&graph;
	graph &= 0x00e;
	a >>= 3;
	b >>= 2;
	graph >>= 1;
	return graph + a + b;
}

/* This routine marches through each directed graph on Q3.  If it is
   not a partial order, or if it is an isomorphic copy of a previous checked
   graph, we mark this in the 'checkbox' so we can skip it when we get to it 
   later.

   Since we are listing isomorphism classes, and since these are partial
   orders, we fix our search set to those graphs where 000 is a source node.  This
   reduces the number of iterations from 2**12 to 2**9. */

#define BIGLOOP \
	for(tcycle=0;tcycle<3;tcycle++) \
	for(tau=0;tau<2;tau++) \
	for(xorop=0;xorop<8;xorop++) \


void filter (uch *checkbox){
	/* See code in IsPoset.c for details about 'hot' */
	ui Graph,tgraph;
	// 0x1ff
	for(graph=0x0;graph<=0x1ff;graph++)
	{
		if(checkbox[graph]) continue;
		Graph = inflate9to12(graph);
		int2table(Graph);
		if(IsPoset()){
#ifdef DYCK
			for(i=0;i<S(CARD);i++){
				if(IsCompat(Graph,permblock[i]) 
						&& !dyckCheck(permblock[i]))
					/* Skip printing if incompatible */
					goto loc;
			}
#endif
			printf("%03x\n",Graph);
loc:;
		}

		/* flip through all symmetries */
		uch tcycle,tau,xorop;
		BIGLOOP
		{
			/* tgraph = `transformed graph' */
			tgraph = symmetry(Graph,tcycle,tau,xorop);
			if(IsBaseSource(tgraph)){
				tgraph = compress12to9(tgraph);
				checkbox[tgraph]=1;
			}
		}		
	}
}
