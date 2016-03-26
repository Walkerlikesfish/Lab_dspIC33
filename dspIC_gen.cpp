// dspIC_gen.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Datatypes.h"
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <time.h>

#define PI 3.1415926

using namespace std;

const int Ndft = 128;

// sin(x) = x - (1/3!)x^3 + (1/5!)x^5 - (1/7!)x^7 
INT8S fsin(INT8U m)
{
    INT8U m3,m5,m7;
    m3 = m*m*m
    = 
}

// cos(x) = x - (1/3!)x^3 + (1/5!)x^5 - (1/7!)x^7 
INT8S fcos

int _tmain(int argc, _TCHAR* argv[])
{
	INT8U i,j,m,*pt,x;
	INT16U tm;
	INT8S *pr,*pi;
	FP32 tcos,tsin;
	FILE *fp;
	fp = fopen("tableEx.h","w+");

	srand(time(NULL));
	

	INT8S *treal = new INT8S[Ndft+1]; // real part of coefficient
	INT8S *timage = new INT8S[Ndft+1]; // image part of coef
	INT8U *tablem = new INT8U[Ndft*Ndft]; // intermediate to store n*k/Ndft
	INT8U *tabletm = new INT8U[Ndft+1];  // +1 play a little trick in printing the table
	INT8U *xin = new INT8U[Ndft+1];

	pt = tablem;
	for(i=1;i<=Ndft;i++)
	{
		for(j=1;j<=Ndft;j++)
		{
			m = i*j/Ndft;  // round to the nearest integer
			tm=(2*50*m+128)>>4; //50=3.14159*16  => 2*PI*n*k/N
			tablem[i*Ndft+j]=m;
			*(tabletm+m) = tm;
		}
	}
	tablem= pt;

	pr = treal;
	pi = timage;
	for(i=0;i<Ndft;i++)
	{
		tm = *(tabletm+i);
		tcos = fcos(tm);
		tsin = fsin(tm);
		*(pr+i)=tcos; // <<6 
		*(pi+i)=tsin; // <<6
	}

	/*
	tcos = cos(double(tm)); // could be replaced by expansion
			tsin = sin(double(tm)); // could be replaced by expansion
			treal[i*Ndft+j]=(unsigned char)(tcos*16);
			timage[i*Ndft+j]=(unsigned char)(tsin*16);
	*/
	/*
	fprintf(fp,"INT8U tm[]={\n");
	for(i=0;i<Ndft;i++)
	{
		for(j=0;j<Ndft;j++)
		{
			fprintf(fp,"%d, ",*(tablem+i*Ndft+j));
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"};\n");
	
	// we don't need to print the m table since it is easy to calculate

	*/
	//--------------------------------------------//
	// Output to file as header

	fprintf(fp,"INT8U wreal[]={\n");
	for(i=0;i<Ndft;i++)
	{
		fprintf(fp,"%d, ",*(treal+i));
	}
	fprintf(fp,"0};\n");

	fprintf(fp,"INT8U wimage[]={\n");
	for(i=0;i<Ndft;i++)
	{
		fprintf(fp,"%d, ",*(timage+i));
	}
	fprintf(fp,"0};\n");

	//--------------------------------------------//
	//Generating input vector with random
	fprintf(fp,"INT8U xin[]={\n");
	for(i=0;i<Ndft;i++)
	{
		x = rand() % 255;
		fprintf(fp,"%d, ",x);
	}
	fprintf(fp,"0};\n");


	fclose(fp);

	system("pause");
	return 0;
}

