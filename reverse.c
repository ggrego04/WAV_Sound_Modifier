/** @file  reverse.c
 *  @author Gregory Gregoriades
 *	@date 21 Nov 2018
 *	@brief This .c file contains a function called ReverseTrack
 *		   which is responsible to take a .wav file, make it
 *  	   sound backwards and save it in a new .wav file
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

public int ReverseTrack(char* filename){
	
	WAV *file=ConstructWav();
	int error=readFile(filename,file);
	if (error==1)
		return 1;

	//creation of a new header
    struct HEADER *h = (struct HEADER*)malloc(sizeof(struct HEADER));
    if(file==NULL){
      printf("The file doesn't exist!");
      return 1;
    }
	
	strcpy((char*)h->riff_header, (const char*)file->h->riff_header);
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

    h->data_bytes = file->h->data_bytes;

   
   
    h->wav_size=file->h->wav_size;
   
	byte *data = (byte*)malloc(h->data_bytes);	

	//construction of a new wav file   
	struct WAV *w = (struct WAV*)malloc(sizeof(struct WAV));	
	w->h=h;  
	
	int i;
    int j=0;

	//the following loop takes the last 4 bytes of the wav file 
	//and places them at the beginning of the new one	
	for(i=(h->data_bytes)-1;i>0;i-=4){
		data[j]=file->data[i-3];
		data[j+1]=file->data[i-2];
		data[j+2]=file->data[i-1];
		data[j+3]=file->data[i];
		j=j+4;
	}
	
	
	
	w->data=data;
//	PrintList(w);
	
	//creating the file name
	char newfile[512];
	strcpy(newfile,"reverse-");
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

