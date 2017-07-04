#include"headers.h"
#include<assert.h>

#define GROUP_CARD 48

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

/* We count the number of acyclic directed graphs in 
   Q3.  

	Procedure :
		1. Allocate table of size 2^9 corresponding to graph with 000
		as the base.  
		2. For each entry: 
			a. Check off (set equal to 1) if contains cycles. 
		   	b. Take all 48 group transformations.  Of these,
				if any have 000 as base, and lie further down the table,
				check off that element of the table (set value to 1)
			c. Count how many group elements fix the current table 
			entry.  Number of distinct isomorphs is 48/<number fixed>
 */

#define BIGLOOP \
	for(tcycle=0;tcycle<3;tcycle++) \
	for(tau=0;tau<2;tau++) \
	for(xorop=0;xorop<8;xorop++) \


void filter (uch *checkbox)
{

	/* tgraph_i, graph_i == inflated to 12 bits */
	ui graph_i,tgraph_i,tgraph,nisomorphs,count;
	uch tcycle,tau,xorop;

#ifdef DYCK
	uch dyck = 1;
#endif

	count = 0;
	
	for(graph=START_Q3;graph<NQ3;graph++)
	{
start:
		if(checkbox[graph]) continue;
		graph_i = inflate9to12(graph);
		int2table(graph_i);
		if(IsPoset()){

#ifdef DYCK
			for(i=0;i<S(CARD);i++){
				if(IsCompat(graph_i,permblock[i]) 
						&& !dyckCheck(permblock[i]))
				{
					/* Flag for no counting if dyck */
					dyck = 0;
					break;
				}
			}
#endif

			nisomorphs = 0;
			BIGLOOP
			{
				/* tgraph_i = `transformed graph' */
				tgraph_i = symmetry(graph_i,tcycle,tau,xorop);

				if(IsBaseSource(tgraph_i)){

					/* remove "base" bits for table entry */
					tgraph = compress12to9(tgraph_i);

					/* check off is isomorphic to entries further down */
					if(tgraph > graph)
						checkbox[tgraph]=1;
				}

				nisomorphs += tgraph_i == graph_i;
			}		

			assert((GROUP_CARD % nisomorphs) == 0);

#ifdef DYCK
			if(dyck)
#endif
				count += GROUP_CARD/nisomorphs;
			
#ifdef DYCK
			/* Reset flag */
			dyck = 1;
#endif
		}
	}

	printf("%u\n",count);

}
