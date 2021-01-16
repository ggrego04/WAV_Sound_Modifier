/** @file  chop.c
 *  @author Gregory Gregoriades
 *	@date 21 Nov 2018
 *	@brief This .c file contains a function called ChopTrack
 *		   which is responsible to take a .wav file, as well
 *		   as the seconds of the starting and finishing chops,
 *		   separate the part within the start and finish and 
 *		   save it in a new .wav file
 *   
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

public int ChopTrack(char* filename,int s,int f){
	printf("in function\n");
	WAV *file=ConstructWav();
	int error=readFile(filename,file);
	if (error==1)
		return 1;
    //creation of the header
    struct HEADER *h = (struct HEADER*)malloc(sizeof(struct HEADER));
    if(file==NULL){
      printf("The file doesn't exist!");
      return 1;
    }
	
	int totalsec=(file->h->data_bytes)/(file->h->byte_rate); //calculation of the total seconds in the file
    if((s>f)||(s>totalsec)||(f>totalsec)){
		printf("Wrong input!\nTYPE: ./<executable> <-chop> <filename> <starting chop> <finishing chop>\nStarting    chop number must be lower than finishing and within audio input bounds!\n");
    	return 1;
  	}
	strcpy((char*)h->riff_header, (const char*)file->h->riff_header);
	
	s=s*(file->h->byte_rate);	//calculation of the starting and finishing chop point 
   	f=f*(file->h->byte_rate);	//by multiplying the seconds with the byte rate
    int newsize=f-s;			//the size of the new wav file is their difference
    
	
	strcpy((char*)h->wave_header, (const char*)file->h->wave_header);
    strcpy((char*)h->fmt_header, (const char*)file->h->fmt_header);
	h->fmt_chunk_size = file->h->fmt_chunk_size;
    h->audio_format = file->h->audio_format;
	h->num_channels=file->h->num_channels;
	h->sample_rate = file->h->sample_rate;
	h->byte_rate=file->h->byte_rate;
	h->sample_alignment = file->h->sample_alignment;
    h->bit_depth = file->h->bit_depth;
 
    strcpy((char*)h->data_header, (const char*)file->h->data_header);

    h->data_bytes = newsize;		//the new data bytes size is the newsize
    h->wav_size=(h->data_bytes)+36;
   
	byte *data = (byte*)malloc(h->data_bytes);	
   
	struct WAV *w = (struct WAV*)malloc(sizeof(struct WAV));	
	w->h=h;  
	
	
	int i;
    int j=0;
	//the following loop starts from the starting chop to the finishing
	//and transfers the bytes to the new wav file
	for(i=s;i<f;i+=2){
		data[j]=file->data[i];
        data[j+1]=file->data[i+1];
    	j+=2;
	}

	w->data=data;
  	PrintList(w);
	//creating the file name
  	char newfile[512];
	strcpy(newfile,"chopped-");
	strcat(newfile,filename);
	FILE* f1=fopen(newfile,"wb");
	fwrite(w->h,sizeof(struct HEADER),1,f1);
	fwrite(data,sizeof(w->h->data_bytes),w->h->data_bytes,f1);
	
			
	fclose(f1);
	free(file->h);
	free(file->data);
	free(h);
	free(data);	
	free(w);
	free(file);


    return 0;
}

