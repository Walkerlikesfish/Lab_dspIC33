/*
dsPIC33 exercises
Team: Yu LIU, Hao QIN, Jie YOU, Michael
Date: March 2016

Carry out DFT by simply applying the definition algorithm

- input: xn size=N;  time domain samples
- output: Xk size=N; frequency domain coefficients

Requirement:

1. Number of sample points are fixed to N=128 circular buffer
2. exponential are stored as FIXED point complex numbers
3. every calculation should be FIXED point
 
*/

#include "DataTypes.h"
#include "tableEx.h"

const INT8U Ndft = 128;
// Here we preload the cos(m) and sin(m)
// both vectors are Nfft=128*1Bytes long, takes 256Bytes in total

void main(void)
{
    INT8U i,j,m;
    	INT8U first_sample,ind;
	INT8S treal,timage;
	INT16S *Xreal,*Ximage,txr,txi,*tr,*ti;
	INT32S sxr,sxi;
	Xreal = (INT16S*)malloc(Ndft+1);
	Ximage = (INT16S*)malloc(Ndft+1);
	tr=Xreal;
	ti=Ximage;

    for(i=0;i<Ndft;i++)
	{
        sxr=0; sxi=0;
		for(j=0;j<Ndft;j++)
		{
			ind = (j+first_sample)%Ndft; // make it a circular index
			m=i*ind/Ndft;  // rounded by requirement [not fix point]
			treal = *(wreal+m); //read from table
			timage = *(wimage+m); //read from table
			txr = (INT16S)treal*(INT16S)xin[ind]; //typecast before
			txi = -(INT16S)timage*(INT16S)xin[ind]; //typecast before
			sxr = sxr+txr; //[?] Do we need to deal with the overflow here
			sxi = sxi+txi;
		} 
		*(tr+i)=(sxr+16384)>>6;
		*(ti+i)=(sxi+16384)>>6;
	}
}
