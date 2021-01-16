/**
*@file decryption.c
*@author Andreas Makris
*@date 21 Nov 2018
*@brief Contains the function that is responsible for the 
*		decryption of a text message from a wav file.
*
* Includes the function decodeText which is responsible
* open the wav file, create the permutation table, 
* decode the text message, and create a text file
* which contains the hidden message.
*
*
*/


#include "wave.h"



public int decodeText(char *wavfile,int msglength,char *filename){
	
	printf("destination file: %s\n",filename);
	FILE *fp2=fopen(filename,"w");
	if(fp2==NULL){
		printf("Can't open/create destination file.\n");
		return 1;
	}
	
	printf("%d\n",msglength);
	WAV *file=ConstructWav();
	int error =readFile(wavfile,file);
	if (error ==1)
		return 1;
//	PrintList(file);
	int *perm = createPermutationFunction(8*(msglength+1),25);
	
	int i=0;
	
	
	byte *num = (byte*)malloc(sizeof(byte)*msglength);
	
//	printf("HELLO\n");
	
	for(i=0;i<(msglength+1)*8;i++){
		num[i]=(file->data[perm[i]])&0x01;
	}
	/*
	for(i=0;i<(msglength+1)*8;i++){
		printf("%d: ",i);
		printf("%d\n",num[i]);
	}
	*/
	for(i=0;i<(msglength+1)*8;i+=8){
		
		int j=0;
		int c=0;
		for(j=0;j<8;j++){
			if(num[i+j]==1)
				c=c+pow(2,7-j);
		}
		
		//printf("%c",(char)c);
		
		fprintf(fp2,"%c",(byte)c);
	}
	free(num);
	free(perm);
	fclose(fp2);
	free(file->h);
	free(file->data);
	free(file);

	
	
	return 0;
}
