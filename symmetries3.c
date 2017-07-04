#include"headers.h"

/* We encode three cube graphs with unsigned 12-bit integers.  This
 * function performs symmetry operations on the three-cube at the
 * encoding level.  For a description of the encoding, look at the
 * comments in `main.c' */

ui reversemiddletwo(ui n,ui shift){
	ui a,b;
	n >>= shift;
	a = n&0x2;
	b = n&0x4;
	n &= 0x9;
	n += (a << 1) + (b >> 1);
	return (n << shift);
}

ui doubleflip(ui n,ui flip,ui shift){
	ui a;
	n >>= shift;
	switch(flip){
		case 1:
			a = n&0xa;
			n &= 0x5;
			n <<= 1;
			n += (a>>1);
			break;
		case 2:
			a = n&0xc;
			n &= 0x3;
			n <<= 2;
			n += (a >> 2);
			break;
		default:;
	}
	return (n << shift);
}

ui symmetry(ui graph,uch tcycle,uch tau,uch xorop){
	/* Elements: 3 cycles, single transposition, 
	   xoring by constant bit string */
	ui a,left,mid,right;
	/* powers of cyclic permutation (1 2 3) */
	for(a=0;a<tcycle;a++){
		left=graph&0xf00;
		mid=graph&0x0f0;
		graph &= 0xf; // right
		graph <<= 8;
		/* Orientation of first and third bit
		   reversed by three cycle, so need to 
		   adjust by reversing middle two bits 
		   of section used in encoding */
		left = reversemiddletwo(left,8);
		mid = reversemiddletwo(mid,4);
		graph += (left >> 4) + (mid >> 4);
	}
	/* (1 2) */
	if(tau){
		left=graph&0xf00;
		mid=graph&0xf0;
		graph &= 0xf; // right
		/* Switching first second bit in 3-bit
		   string reverses orientation in 3rd-bit
		   4-bit string in encoding */
		graph = reversemiddletwo(graph,0);
		graph += (left>>4) + (mid<<4);
	}	
	/* xor by constant */
	if(xorop&0x1){
		left = 0xf00&graph;
		mid = 0x0f0&graph;
		graph &= 0x00f; // right
		graph ^= 0x00f;
		/* Adjust orientation of left and mid parts*/
		left = doubleflip(left,1,8);
		mid = doubleflip(mid,1,4);
		graph += left + mid;
	}

	if(xorop&0x2){
		left = 0xf00&graph;
		right = 0x00f&graph;
		graph &= 0x0f0; // mid
		graph ^= 0x0f0;
		/* Adjust orientation of left and right parts*/
		left = doubleflip(left,2,8);
		right = doubleflip(right,1,0);
		graph += left + right;
	}

	if(xorop&0x4){
		mid = 0x0f0&graph;
		right = 0x00f&graph;
		graph &= 0xf00; // left
		graph ^= 0xf00;
		/* Adjust orientation of mid and right parts*/
		mid = doubleflip(mid,2,4);
		right = doubleflip(right,2,0);
		graph += mid + right;
	}

	return graph;
}
