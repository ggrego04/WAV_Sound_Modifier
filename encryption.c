/**
*@file encryption.c
*@author Andreas Makris
*@date 21 Nov 2018
*@brief Contains the functions that are responsible for the 
*		encryption of a text messages in a wav file.
*
*Includes 3 functions: encodeText, getBit and createPermutationFunction.
*
*
*/


#include "wave.h"

/** @brief Returns the nth bit of a string.
*
* This function is only called from the function encodeText.
* Its job is to print the nth bit of a given character array. 
*
* @param *m The array of characters which holds the characters from the text file.
* @param n The position of the bit that we want to get.
* @return int The n-th bit of a string.
*/
private int getBit(char *m,int n);



public int encodeText(char *wavfile,char *filename){
	WAV *file=ConstructWav();
	int error = readFile(wavfile,file);
	if (error==1)
		return 1;
	
//	PrintList(file);
	FILE *fp;
	fp=fopen(filename,"r");
	if (fp==NULL){
		printf("Cant open file\n");
		return 1;
	}
	int count=0;
	char line[512];
	int size =2;
	char *characters = (char*)malloc(sizeof(char)*size);//dynamic table holding the numbers of the file.
	if (characters == NULL){
		printf("Could not create dynamic table\n");
		return 1;
	}
	while(fgets(line,512,fp)){
	//	printf("line: %s\n",line);
		int i;
		for(i=0;i<strlen(line);i++){
			
			if(count == size-1){
				size=size*2;
				char *temp=(char*)realloc(characters,sizeof(char)*size);
				if (temp==NULL){
					printf("Could not expand dynamic table\n");
					return 1;
				}
				characters=temp;
			//	printf("size is now: %d\n",size);
			}
			
			characters[count]=line[i];

		//	printf("character %d: %c %d\n",count,characters[count],characters[count]);
			count++;
		//	printf("%d\n",count);
			
		}
		
	}
	characters[count]='\0';
	
//	printf("String: %s\n",characters);
	int i;
	int *perm = createPermutationFunction(8*(count+1),25);
	for(i=0;i<(8*(count+1));i++){
		int u=getBit(characters,i);
		//printf("BIT:%d DATA:%d\n",i,u);
		int x=perm[i];
	
		byte c;
		if (u==1)
			c=(file->data[x]) | 0x01;
		else
			c=(file->data[x]) & 0xFE;
		
		file->data[x]=c;		
	}
	 struct HEADER *h = (struct HEADER*)malloc(sizeof(struct HEADER));
	 h=file->h;
	 WAV *w=ConstructWav();
	 w->h=file->h;
	 byte *data = (byte*)malloc(h->data_bytes);	
	 data=file->data;
	 w->data=data;
	char newfile[512];
	strcpy(newfile,"new-");
	
	strcat(newfile,wavfile);
	FILE* f1=fopen(newfile,"wb");
	
	fwrite(w->h,sizeof(struct HEADER),1,f1);
	fwrite(data,sizeof(w->h->data_bytes),w->h->data_bytes,f1);
	
	
	printf("The message length for the decryption has to be: %d\n",count);
	
	free(perm);
	free(w);
	fclose(fp);
	fclose(f1);
	free(file);
	free(characters);
	free(h);
	free(data);
	
	
	return 0;
	
}

private int getBit(char *m,int n){
	
	
	
	if(n>8*(strlen(m)+1)){
		printf("N is out of range\n");
		return -1;
	}
	int num = n/8;
	int bit = 7-(n-num*8);
	
	char c= m[num];
	

	if (c&((int)(pow(2,bit))))
		return 1;
	else 
		return 0;
	
	
	
	
}

public int* createPermutationFunction(int N, unsigned int systemkey){
	srand(systemkey);
	int *table = (int*) malloc(sizeof(int)*N);
	
	int i=0;
	for(i=0;i<N;i++){
		table[i]=i;
		//printf("table[%d]: %d\n",i,table[i]);
	}
	srand(systemkey);
	for(i=0;i<N;i++){
		int first = (int)(rand()%N);
		//printf("%d ",first);
		int second = (int)(rand()%N);
		//printf("Swapped %d with %d\n",first, second);
		int temp = table[first];
		table[first]=table[second];
		table[second]=temp;
	}
	//for(i=0;i<N;i++){
		//printf("table[%d]: %d\n",i,table[i]);
	//}
	return table;
}
