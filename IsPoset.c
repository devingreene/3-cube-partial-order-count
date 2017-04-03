#include"headers.h"

/* When one of the branches of the recursive call hits a loop,
   we want to tell the other instances of 'lookAhead' to return 
   zero.  We do this by setting 'flag' to one, which tells the 
   other instances to return zero immediately. */
extern int **potable;
int flag=0;
int card = CARD;

int lookAhead(int start,int *hot,int nhot){
	if(flag) return 0;
	int i,j,newhot[card],product=1;
	for(i=0;potable[start][i]!=-1;i++){
		for(j=0;j<nhot-1;j++){
			if(potable[start][i]==hot[j]){
				flag=1;
				return 0;
			}
		}
		memcpy(newhot,hot,nhot*sizeof(int));
		newhot[nhot]=potable[start][i];
		product &= lookAhead(potable[start][i],newhot,nhot+1);
	}
	if(i==0) return 1;
	return product;
}

int IsPoset(void){
	int start,hot[16];
	for(start=0;start<card;start++){
		flag=0;
		*hot=start;
		if(lookAhead(start,hot,1)) continue;
		else return 0;
	}
	return 1;
}
