#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<error.h>
#include<errno.h>
#include<x86_64-linux-gnu/sys/cdefs.h>

#define uch unsigned char
#define ui unsigned int
#define ush unsigned short

#define CARD (8)
#define S(CARD) (8*7*6*5*4*3*2)
#define POS 3
#define MARGIN 4

#ifndef NQ3
#define NQ3 0x200
#endif

#ifndef START_Q3
#define START_Q3 0
#endif

