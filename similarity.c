/** @file  similarity.c
 *  @author Gregory Gregoriades
 *	@date 21 Nov 2018
 *	@brief This .c file contains three functions called min,
 *		   max, EuclideanDistance and LCSS. which are responsible 
 *		   to take at least 2 .wav files and calculate the LCSS
 *		   distance and the Euclidean distance and print them out
 */

/*
Copyright (C) 2018 Andreas Makris Gregory Gregoriades
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
Υou should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "wave.h"

/**
 *  This function calculates and returns the bigger of 2 integers
 *
 *  @param int a the first number
 *  @param int b the second number
 *  @return the bigger of the two numbers
 */
private int max(int a, int b);
/**
 *  This function calculates and returns the smaller of 2 integers
 *
 *  @param int a the first number
 *  @param int b the second number
 *  @return the smaller of the two numbers
 */
private int min(int a, int b);

public int EuclideanDistance(WAV* f1,WAV* f2){
	
	unsigned long sum=0;
	double distance;

	if((f1==NULL)||(f2==NULL))
		return 1;

	int size,i;


	size=min((f1->h->data_bytes),(f2->h->data_bytes));

	for(i=0;i<size;i++){
		sum=sum+pow(abs(f1->data[i]-f2->data[i]),2);
	}

	distance=sqrt(sum);
	printf("\nEuclidean distance : %.3f\n",distance);
	
	return 0;
}

private int max(int a, int b) {

	if(a>b)
		return a;
	else
		return b;  
}  
private int min(int a, int b) {

	if(a<b)
		return a;
	else
		return b;  
} 
  

public int LCSS(WAV *f1,WAV *f2) {
   
	double distance;
	int i,j;
	dword *C;
	dword *D;
	dword *temp;
	C=(dword*)calloc(f2->h->data_bytes+1,sizeof(dword));
	D=(dword*)calloc(f2->h->data_bytes+1,sizeof(dword));
	for (i=1;i<=f1->h->data_bytes;i++){
		for(j=1;j<=f2->h->data_bytes;j++){
			if(f1->data[i-1]==f2->data[j-1])
				C[j]=D[j-1]+1;
			else
				C[j]=max(D[j],C[j-1]);		
		}
		temp=D;
		D=C;
		C=temp;
	}

	distance=1.0-(((double)C[f2->h->data_bytes])/min((f1->h->data_bytes),(f2->h->data_bytes)));
	printf("LCSS : %.3f\n\n",distance);

	free(C);
	free(D);
    return 0;
} 
  

